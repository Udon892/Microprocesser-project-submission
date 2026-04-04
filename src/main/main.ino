
// declare variables for pins
const int sensorpin = A0;
const int sensorpower = 8;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int pumppin = 11;

// variable for sensor reading
int sensor;

// delay time between sensor readings (milliseconds)
const int delayTime = 1; 

// "wet" and "dry" thresholds - these require calibration
int wet = 800;
int dry = 500;


void setup(){ // code that only runs once
  // set pins as outputs
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(sensorpower,OUTPUT);
  pinMode(pumppin,OUTPUT);
  
  // initialize serial communication
  Serial.begin(9600);
}

void loop(){ // code that loops forever
  // power on sensor and wait briefly
  digitalWrite(sensorpower,HIGH);
  delay(10);
  // take reading from sensor
  sensor = analogRead(sensorpin);
  // turn sensor off to help prevent corrosion
  digitalWrite(sensorpower,LOW);
  
  // print sensor reading
  Serial.println(sensor);
  
  // If sensor reading is greater than "wet" threshold,
  // turn on the blue LED. If it is less than the "dry"
  // threshold, turn on the red LED and the pump. 
  // If it is in between the two values, turn on 
  // the yellow LED.
  if(sensor>wet){
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    digitalWrite(pumppin,LOW);
  }
  else if(sensor<dry){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(pumppin,HIGH);
  }
  else{
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(pumppin,LOW);
  }
  
  // wait before taking next reading
  delay(delayTime);
  
}