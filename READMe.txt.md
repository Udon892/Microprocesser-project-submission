



====================================================================

PROJECT: Weather Station – Temperature, Humidity \& Pressure

GROUP: Group 3

DATE: April 2026

====================================================================



1\. PROJECT OVERVIEW

This weather station measures three environmental parameters:

\- Temperature (°C)

\- Relative Humidity (%)

\- Atmospheric Pressure (hPa)



The project consists of two parts:

A) Schematic design in EasyEDA (Arduino Nano + BME280 + LCD 1602 Green-Yellow)

B) Functional simulation in Wokwi (Arduino Uno + DHT22 + BMP180 + same LCD)



Because Wokwi does not have a BME280 model, the simulation uses DHT22 (temp/humidity) and BMP180 (pressure). The wiring and code are **equivalent**.



2\. HARDWARE COMPONENTS (for simulation \& physical build)

\- Arduino Nano (schematic) / Arduino Uno (simulation)

\- DHT22 (temperature \& humidity)

\- BMP180 (pressure, I2C)

\- BME280 (only in schematic – not used in simulation)

\- 16x2 LCD Green-Yellow (parallel, 16 pins)



3\. CIRCUIT WIRING – EXACT PIN MAPPING (as used in the Wokwi simulation)



3.1 DHT22 to Arduino Uno (simulation) – same for Nano

\- VCC  → 5V

\- GND  → GND

\- DATA → Digital Pin 2



3.2 BMP180 to Arduino (I2C)

\- VCC  → 5V

\- GND  → GND

\- SCL  → A5

\- SDA  → A4

\- 3.3V → leave unconnected



3.3 16x2 LCD Green-Yellow (parallel, 4-bit mode) to Arduino

\- VSS (pin 1)  → GND

\- VDD (pin 2)  → 5V

\- VO  (pin 3)  → GND

\- RS  (pin 4)  → D12

\- RW  (pin 5)  → GND

\- E   (pin 6)  → D11

\- D4  (pin 11) → D10

\- D5  (pin 12) → D9

\- D6  (pin 13) → D8

\- D7  (pin 14) → D7

\- BLA (pin 15) → 5V

\- BLK (pin 16) → GND 



Pins DB0, DB1, DB2, DB3 (pins 7-10) are not connected.



3.4 BME280 (only in EasyEDA schematic) – same I2C pins as BMP180

\- VDD   → 5V

\- GND   → GND

\- VDIO  → 5V (tie to VDD)

\- CSB   → 5V (enables I2C mode)

\- SDI   → A4 (SDA)

\- SCK   → A5 (SCL)

\- SDO   → unconnected



4\. REQUIRED ARDUINO LIBRARIES (for simulation and physical build)

Install via Arduino Library Manager or Wokwi Library Manager:

\- DHT sensor library (by Adafruit)

\- Adafruit Unified Sensor

\- Adafruit BMP085 Library (works for BMP180)

\- LiquidCrystal (built-in)



For the EasyEDA schematic (BME280), you would also need Adafruit BME280 Library.



5\. CODE (**main.c**)

The code reads DHT22 and BMP180 every 2 seconds and displays:

\- Line 0: "Temp: xx.xC"

\- Line 1: "Hum: xx.x%  xxxhPa"



Full code is in **src/main.c** 



6\. HOW TO RUN THE SIMULATION (Wokwi)

\- Go to wokwi.com and create a new Arduino Uno project.

\- Add components: DHT22, BMP180, 16x2 LCD Green-Yellow.

\- Wire exactly as described in section 3 (DHT22 to D2, BMP180 to A4/A5, LCD to D12,D11,D10,D9,D8,D7).

\- In the code editor, delete default code and paste the content from src/weather\_station.ino.

\- Click "Start Simulation". The LCD will show temperature, humidity, and pressure updating every 2 seconds.

\- Take screenshots for submission.



7\. EASYEDA SCHEMATIC (Design)

\- The schematic includes Arduino Nano, BME280, and the same LCD Green-Yellow.

\- BME280 wired as in section 3.4 (I2C on A4/A5).

\- LCD wired exactly as in section 3.3 (same pins).

\- No simulation in EasyEDA – it is only for schematic capture.



8\. TROUBLESHOOTING

\- LCD blank: Check VDD, VSS, and backlight (pins 15,16). Adjust VO pin (pin 3) – for simulation, connect to GND works.

\- "BMP180 not found": Verify SDA→A4, SCL→A5, VCC→5V, GND→GND.

\- DHT22 reads "nan": Ensure DATA pin is connected to D2 and a 10kΩ pull-up resistor from DATA to 5V (optional in simulation but helps).

\- In Wokwi, ensure all libraries are added via Library Manager (DHT, Adafruit BMP085, LiquidCrystal).







9. GROUP MEMBERS

&#x20; 1.Agyei Jedidiah Afia Fosuah - 7341623

&#x20; 2.Augustine Arhinful – 7342423

&#x20; 3.Martin Ennin – 7343123

&#x20; 4.Atta-Kay Joshua Kusi – 7343423

&#x20; 5.Amankwah Gordon – 7342023

&#x20; 6.Yakubu Kabir - 1874822



====================================================================



====================================================================

