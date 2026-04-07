//Calling the Libraries to be used
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

// Setting up my LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// The Servo Motor
Servo myServo;

// setting up Buzzer
#define BUZZER 13

// setting up the Keypad, telling the console that its a 4x4 
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'}, //how the keypads input looks like
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6,7,8,9};
byte colPins[COLS] = {A0,A1,A2,A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// setting up Pin
String correctPIN = "8182"; // Correct pin
String enteredPIN = "";

void setup() {
  myServo.attach(10);
  myServo.write(0);  // Locked

  pinMode(BUZZER, OUTPUT);

  lcd.begin(16,2);
  lcd.print("Enter PIN:");
}

void loop() {
  char key = keypad.getKey();
  if(key){
    lcd.setCursor(enteredPIN.length(),1);
    lcd.print("*");
    enteredPIN += key;

    if(enteredPIN.length() == 4){
      lcd.clear();
      
// if the pin entered is correct, the lcd will display access granted
      if(enteredPIN == correctPIN){
        lcd.print("Access Granted"); 
        myServo.write(90); 
        delay(1000);

        // Lcd will display the countdown of when the door closes
        for(int i = 10; i >= 0; i--){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Door locks in:");
          lcd.setCursor(0,1);
          lcd.print(i);
          delay(1000);
        }

        myServo.write(0); 
      } 
      else {
        lcd.print("Wrong PIN");

        // buzzer sounds 3 times for a wrong password
        for(int i = 0; i < 3; i++){
          digitalWrite(BUZZER, HIGH);
          delay(200);
          digitalWrite(BUZZER, LOW);
          delay(200);
        }
      }

      delay(2000);
      enteredPIN = "";
      lcd.clear();
      lcd.print("Enter PIN:");
    }
  }
}