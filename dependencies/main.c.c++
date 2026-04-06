#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // RS, E, D4, D5, D6, D7
Adafruit_BMP085 bmp;

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  if (!bmp.begin()) {
    lcd.clear();
    lcd.print("BMP180 error");
    while (1);
  }

  lcd.print("Temp:      ");
  lcd.setCursor(0, 1);
  lcd.print("Hum:       ");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bmp.readPressure() / 100.0F;   // hPa

  // Display temperature on first line
  lcd.setCursor(6, 0);
  lcd.print(temperature, 1);
  lcd.print("C");

  // Display humidity and pressure on second line
  lcd.setCursor(4, 1);
  lcd.print(humidity, 1);
  lcd.print("% ");

  lcd.setCursor(10, 1);
  lcd.print(pressure, 0);   // integer pressure
  lcd.print("hPa");

  delay(2000);
}