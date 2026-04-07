Project Title:  Gas Detection System
Group Name: Group 5

Dwira, Nhyira Ewuradwoa.....7343023
Nkrumah Samuel..............7343623
Dontwi, Bismark Appiah......7342923
Koduah Hammond Paita........1872922
Nsagnan Richmond............7343723
Alfred Amuzu................1871722

Project Description:
This project is an gas leakage detection and alert system built using ESP32. The system reads gas concentration from a gas sensor and performs safety actions depending on the detected gas level.

Functional Overview:
1. Displays gas concentration on an LCD.
2. Sends gas readings to Blynk cloud.
3. Indicates system condition using LEDs.
4. Activates a buzzer during warning and hazard states.
5. Controls a fan for ventilation.
6. Controls a relay valve during critical gas leakage.


Pin Assignments:
- Gas Sensor: GPIO 32
- Relay Valve: GPIO 14
- Fan PWM: GPIO 13
- Buzzer: GPIO 27
- Green LED: GPIO 25
- Yellow LED: GPIO 26
- Red LED: GPIO 33
- Purple LED: GPIO 15

Libraries Used:
- WiFi.h
- WiFiClient.h
- BlynkSimpleEsp32.h
- Wire.h
- LiquidCrystal_I2C.h

Folder Description:
- src/main.c : Main source code
- docs/READMe.txt : Project documentation
- libs/dependencies : Additional external libraries if required

System States:
- Safe: gas level below 40 ppm
- Warning: gas level between 41 and 44 ppm
- Hazard: gas level 45 ppm and above
