#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= LED PINS =================
#define RED_A 19
#define YELLOW_A 18
#define GREEN_A 5

#define RED_B 23
#define YELLOW_B 32
#define GREEN_B 17

// ================= ULTRASONIC =================
#define TRIG_A 4
#define ECHO_A 2
#define TRIG_B 15
#define ECHO_B 16

// ================= 7-SEGMENT =================
int segPins[7] = {13,12,14,27,26,25,33};

// digits (common cathode)
byte digits[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};

// ================= GLOBAL =================
String priority = "";

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(RED_A, OUTPUT);
  pinMode(YELLOW_A, OUTPUT);
  pinMode(GREEN_A, OUTPUT);

  pinMode(RED_B, OUTPUT);
  pinMode(YELLOW_B, OUTPUT);
  pinMode(GREEN_B, OUTPUT);

  pinMode(TRIG_A, OUTPUT);
  pinMode(ECHO_A, INPUT);
  pinMode(TRIG_B, OUTPUT);
  pinMode(ECHO_B, INPUT);

  for(int i=0;i<7;i++){
    pinMode(segPins[i], OUTPUT);
  }

  lcd.init();
  lcd.backlight();
}

// ================= ULTRASONIC =================
long readDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

// ================= 7-SEGMENT =================
void displayDigit(int num){
  for(int i=0;i<7;i++){
    digitalWrite(segPins[i], digits[num][i]);
  }
}

// ================= COUNTDOWN =================
void countdown(int t){
  for(int i=t; i>=0; i--){
    displayDigit(i % 10);
    delay(1000);
  }
}

// ================= ROAD CONTROL =================
void roadA_Green(int time){

  digitalWrite(GREEN_A, HIGH);
  digitalWrite(RED_B, HIGH);

  for(int i=time; i>=0; i--){
    displayDigit(i % 10);

    lcd.setCursor(0,0);
    lcd.print("Road A: GO     ");

    lcd.setCursor(0,1);
    lcd.print(priority + "   ");

    delay(1000);
  }

  digitalWrite(GREEN_A, LOW);
  digitalWrite(YELLOW_A, HIGH);
  delay(2000);
  digitalWrite(YELLOW_A, LOW);
  digitalWrite(RED_B, LOW);
}

void roadB_Green(int time){

  digitalWrite(GREEN_B, HIGH);
  digitalWrite(RED_A, HIGH);

  for(int i=time; i>=0; i--){
    displayDigit(i % 10);

    lcd.setCursor(0,0);
    lcd.print("Road B: GO     ");

    lcd.setCursor(0,1);
    lcd.print(priority + "   ");

    delay(1000);
  }

  digitalWrite(GREEN_B, LOW);
  digitalWrite(YELLOW_B, HIGH);
  delay(2000);
  digitalWrite(YELLOW_B, LOW);
  digitalWrite(RED_A, LOW);
}

// ================= MAIN LOOP =================
void loop() {

  long distA = readDistance(TRIG_A, ECHO_A);
  long distB = readDistance(TRIG_B, ECHO_B);

  Serial.print("A: "); Serial.print(distA);
  Serial.print(" | B: "); Serial.println(distB);

  // ===== DETERMINE PRIORITY =====
  if(abs(distA - distB) < 5){
    priority = "Equal Priority";

    roadA_Green(10);
    digitalWrite(RED_A, HIGH);

    roadB_Green(10);
    digitalWrite(RED_B, HIGH);
  }

  else if(distA < distB){
    priority = "Priority: A";

    roadA_Green(10);  // A gets longer time
    digitalWrite(RED_A, HIGH);

    roadB_Green(5);  // B gets shorter time
    digitalWrite(RED_B, HIGH);
  }

  else{
    priority = "Priority: B";

    roadB_Green(10);  // B gets longer time
    digitalWrite(RED_B, HIGH);

    roadA_Green(5);  // A gets shorter time
    digitalWrite(RED_A, HIGH);
  }
}