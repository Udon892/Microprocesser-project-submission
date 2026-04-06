#define BLYNK_TEMPLATE_ID "TMPL2CdP7ubya"
#define BLYNK_TEMPLATE_NAME "LPG Detection"
#define BLYNK_AUTH_TOKEN "agbCJ71p4zKseHKzegbzK4_pgg4yYDbn"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// --- Pin Definitions ---
#define GAS_SENSOR_PIN 32
#define RELAY_VALVE_PIN 14
#define FAN_PWM_PIN 13
#define BUZZER_PIN 27
#define LED_GREEN 25
#define LED_YELLOW 26
#define LED_RED 33
#define LED_PURPLE 15  


//  Precision Smoothing & Calibration
const int numReadings = 10;
int readings[numReadings]; 
int readIndex = 0;
int total = 0;
int averagePPM = 0;
int zeroOffset = 0; 

//  PWM Settings 
const int freq = 5000;
const int resolution = 8; 

bool hazardAlertSent = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  
  pinMode(RELAY_VALVE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_PURPLE, OUTPUT); // Initialize Purple LED

  for (int i = 0; i < numReadings; i++) readings[i] = 0;
  ledcAttach(FAN_PWM_PIN, freq, resolution);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  runCalibration();

  lcd.clear();
  lcd.print("System Online!");
  delay(1000);
  
  // High-speed 5Hz sampling (200ms) for better responsiveness
  timer.setInterval(200L, processGasLogic); 
}

void loop() {
  Blynk.run();
  timer.run();
}

void runCalibration() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CALIBRATING...");
  long calibrationTotal = 0;
  for (int i = 0; i < 30; i++) { // Reduced to 3 seconds for faster startup
    calibrationTotal += analogRead(GAS_SENSOR_PIN);
    delay(100);
  }
  zeroOffset = calibrationTotal / 30;
  Serial.print("Baseline Set: ");
  Serial.println(zeroOffset);
}

void processGasLogic() {
  total = total - readings[readIndex];
  int rawValue = analogRead(GAS_SENSOR_PIN);
  int correctedValue = rawValue - zeroOffset;
  if (correctedValue < 0) correctedValue = 0;

  readings[readIndex] = map(correctedValue, 0, 4095, 0, 100);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  averagePPM = total / numReadings;

  lcd.setCursor(0, 0);
  lcd.print("LPG Level: ");
  lcd.print(averagePPM);
  lcd.print("ppm  ");
  Blynk.virtualWrite(V0, averagePPM);

  if (averagePPM < 40) {
    updateSystem(LOW, 0, HIGH, LOW, LOW, LOW, "SAFE: Normal   ", 0);
    Blynk.virtualWrite(V1, "SAFE");
    hazardAlertSent = false;
  } 
  else if (averagePPM >= 41 && averagePPM <= 44) {
    updateSystem(LOW, 77, LOW, HIGH, LOW, LOW, "WARN: Minor Leak", 1); 
    Blynk.virtualWrite(V1, "WARNING");
  } 
  else if (averagePPM >= 45) {
    updateSystem(HIGH, 255, LOW, LOW, HIGH, HIGH, "CRITICAL LEAK!", 2);
    Blynk.virtualWrite(V1, "HAZARD");

    if (!hazardAlertSent) {
      Serial.println("!!! HAZARD LOGGED TO CLOUD !!!");
      Blynk.logEvent("lpg_hazard", "CRITICAL: LPG Leak! Solenoid Shut.");
      hazardAlertSent = true; 
    }
  }
}

// Added 'p' parameter for Purple LED control
void updateSystem(int valve, int fan, int g, int y, int r, int p, String msg, int alert) {
  digitalWrite(RELAY_VALVE_PIN, valve);
  ledcWrite(FAN_PWM_PIN, fan);
  digitalWrite(LED_GREEN, g);
  digitalWrite(LED_YELLOW, y);
  digitalWrite(LED_RED, r);
  digitalWrite(LED_PURPLE, p); // Controls the new solenoid status light
  
  lcd.setCursor(0, 1);
  lcd.print(msg);

  if (alert == 1) { digitalWrite(BUZZER_PIN, HIGH); delay(50); digitalWrite(BUZZER_PIN, LOW); }
  else if (alert == 2) { digitalWrite(BUZZER_PIN, HIGH); }
  else { digitalWrite(BUZZER_PIN, LOW); }
}
