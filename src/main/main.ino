#include <EEPROM.h>
#include <LiquidCrystal.h>

// Pin definitions
#define MoistureSensorPin A0
#define bt_set            A3
#define bt_up             A4
#define bt_down           A5
#define motorRelay        9

// LCD setup (pins: rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float setL_moisture = 30.0;   // Low moisture threshold (%)
float setH_moisture = 70.0;   // High moisture threshold (%)
float moisture = 0.0;

int Set = 0;        // 0 = Normal mode, 1 = Set Low, 2 = Set High
int flag = 0;       // For SET button debounce
int flash = 0;      // For blinking in setting mode

unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 200;  // milliseconds

void setup() {
  pinMode(MoistureSensorPin, INPUT);
  pinMode(bt_set,  INPUT_PULLUP);
  pinMode(bt_up,   INPUT_PULLUP);
  pinMode(bt_down, INPUT_PULLUP);
  pinMode(motorRelay, OUTPUT);
  
  digitalWrite(motorRelay, LOW);  // Start with pump OFF

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome To ");
  lcd.setCursor(0, 1);
  lcd.print("Plant Watering ");
  delay(2000);
  lcd.clear();

  // Load saved settings from EEPROM
  EEPROM.get(10, setL_moisture);
  EEPROM.get(15, setH_moisture);

  // Safety check in case EEPROM is corrupted
  if (setL_moisture < 0 || setL_moisture > 100) setL_moisture = 30.0;
  if (setH_moisture < 0 || setH_moisture > 100) setH_moisture = 70.0;
  if (setL_moisture >= setH_moisture) {
    setL_moisture = 30.0;
    setH_moisture = 70.0;
  }

  // Initial motor control
  int moistureValue = analogRead(MoistureSensorPin);
  moisture = map(moistureValue, 0, 1023, 0, 100);
  
  if (moisture < setL_moisture) {
    digitalWrite(motorRelay, HIGH);
  }
}

void loop() {
  // Read moisture sensor
  int moistureValue = analogRead(MoistureSensorPin);
  moisture = map(moistureValue, 0, 1023, 0, 100.0);

  // Automatic motor control (with hysteresis)
  if (moisture < setL_moisture) {
    digitalWrite(motorRelay, HIGH);   // Pump ON - soil too dry
  } 
  else if (moisture > setH_moisture) {
    digitalWrite(motorRelay, LOW);    // Pump OFF - soil wet enough
  }

  // ==================== BUTTON HANDLING ====================
  unsigned long currentTime = millis();

  // SET button - cycle through modes
  if (digitalRead(bt_set) == LOW && (currentTime - lastButtonTime > debounceDelay)) {
    flag = 1;
    Set = Set + 1;
    if (Set > 2) Set = 0;
    lastButtonTime = currentTime;
    flash = 0;
    delay(50);  // extra short debounce
  }

  // UP button
  if (digitalRead(bt_up) == LOW && (currentTime - lastButtonTime > debounceDelay)) {
    if (Set == 1) {
      setL_moisture += 1.0;
      if (setL_moisture > 99) setL_moisture = 99;
      if (setL_moisture >= setH_moisture) setL_moisture = setH_moisture - 1;
      EEPROM.put(10, setL_moisture);
    }
    if (Set == 2) {
      setH_moisture += 1.0;
      if (setH_moisture > 100) setH_moisture = 100;
      EEPROM.put(15, setH_moisture);
    }
    lastButtonTime = currentTime;
    delay(50);
  }

  // DOWN button
  if (digitalRead(bt_down) == LOW && (currentTime - lastButtonTime > debounceDelay)) {
    if (Set == 1) {
      setL_moisture -= 1.0;
      if (setL_moisture < 0) setL_moisture = 0;
      EEPROM.put(10, setL_moisture);
    }
    if (Set == 2) {
      setH_moisture -= 1.0;
      if (setH_moisture < 1) setH_moisture = 1;
      if (setH_moisture <= setL_moisture) setH_moisture = setL_moisture + 1;
      EEPROM.put(15, setH_moisture);
    }
    lastButtonTime = currentTime;
    delay(50);
  }

  // ==================== LCD DISPLAY ====================
  lcd.clear();

  if (Set == 0) {
    // Normal operating mode
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.print(moisture, 1);
    lcd.print("%  ");

    lcd.setCursor(0, 1);
    lcd.print("Motor: ");
    if (digitalRead(motorRelay) == HIGH) {
      lcd.print("ON ");
    } else {
      lcd.print("OFF");
    }
  } 
  else {
    // Setting mode
    lcd.setCursor(0, 0);
    lcd.print("  Setting Mode  ");

    lcd.setCursor(0, 1);
    lcd.print("L:");
    if (Set == 1 && flash == 1) {
      lcd.print("    ");        // blink effect
    } else {
      lcd.print(setL_moisture, 1);
      lcd.print("%");
    }

    lcd.print("  H:");
    if (Set == 2 && flash == 1) {
      lcd.print("    ");
    } else {
      lcd.print(setH_moisture, 1);
      lcd.print("%");
    }
  }

  // Flash effect for setting mode
  if (Set > 0) {
    flash = !flash;
  }

  delay(300);   // Update rate - prevents LCD flicker and gives responsive feel
}