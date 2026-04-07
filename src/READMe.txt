 SMART HOME LIGHTING SYSTEM
 Motion Sensor (PIR) + Serial Control (1=ON, 0=OFF)

 Pin definitions
const int PIR_PIN = 33;
const int LED_PIN = 14;

 Variables
int motionState = 0;
int lastMotionState = 0;
bool lightOn = false;
unsigned long lastMotionTime = 0;
const unsigned long lightDuration = 5000;

 Serial command
char serialCommand = ' ';

void setup() {
  Serial.begin(115200);
  
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  
  Serial.println(System Ready);
  Serial.println(Press 1 to turn ON, 0 to turn OFF);
}

void loop() {
   Check serial input
  if (Serial.available()  0) {
    serialCommand = Serial.read();
    
    if (serialCommand == '1') {
      digitalWrite(LED_PIN, HIGH);
      lightOn = true;
      lastMotionTime = millis();
      Serial.println(Light ON);
    }
    else if (serialCommand == '0') {
      digitalWrite(LED_PIN, LOW);
      lightOn = false;
      Serial.println(Light OFF);
    }
  }
  
   Check motion sensor
  motionState = digitalRead(PIR_PIN);
  
  if (motionState == HIGH && lastMotionState == LOW) {
    Serial.println(Motion Detected);
    
    if (!lightOn) {
      digitalWrite(LED_PIN, HIGH);
      lightOn = true;
      Serial.println(Light ON by motion);
    }
    
    lastMotionTime = millis();
  }
  
  lastMotionState = motionState;
  
   Auto-off timer
  if (lightOn == true && (millis() - lastMotionTime)  lightDuration) {
    digitalWrite(LED_PIN, LOW);
    lightOn = false;
    Serial.println(Auto-off Light OFF);
  }
  
  delay(100);
}
