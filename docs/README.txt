# Arduino Automatic Plant Watering System

## Project Overview
This is an Arduino-based automatic soil moisture monitoring and plant watering system. 
The system continuously measures soil moisture levels using a capacitive soil moisture sensor and 
automatically activates a water pump when the soil becomes too dry. It also provides visual 
feedback through three LEDs (Red, Yellow, Blue) indicating the current moisture status.

The project is designed for the microprocessors group 1 project

## Features
- Real-time soil moisture monitoring using a capacitive soil moisture sensor
- Automatic water pump activation when soil is dry
- Visual status indication with RGB-style LED feedback:
  - **Red LED**: Soil is too dry → Pump turns ON
  - **Yellow LED**: Soil moisture is in optimal range
  - **Blue LED**: Soil is too wet
- Sensor power is only enabled briefly during readings to reduce corrosion and extend sensor life
- Serial monitor output for debugging and calibration
- Low power consumption design

## Hardware Components
- Arduino Uno
- Breadboard
- Capacitive Soil Moisture Sensor (with power control)
- 3x LEDs (Red, Yellow, Blue)
- 3x 220Ω resistors (for LEDs)
- Water pump (or relay module + pump)
- 9V or USB power supply for Arduino
- Jumper wires

## Circuit Connections

**Soil Moisture Sensor:**
- VCC → Arduino Digital Pin 8 (controlled power)
- GND → Arduino GND
- A0 (Analog) → Arduino Analog Pin A0

**LED Indicators:**
- Red LED (Dry) → Arduino Digital Pin 2 (with 220Ω resistor)
- Yellow LED (Optimal) → Arduino Digital Pin 3 (with 220Ω resistor)
- Blue LED (Wet) → Arduino Digital Pin 4 (with 220Ω resistor)

**Water Pump:**
- Pump control → Arduino Digital Pin 11

**Power:**
- Arduino powered via USB cable (or external 9V supply)

## Software (Arduino Sketch)

The provided code:
- Reads the soil moisture sensor every ~1ms (adjustable)
- Powers the sensor only during measurement to prevent electrolysis/corrosion
- Compares the analog reading against user-defined thresholds:
  - `wet = 800`   → Soil is wet (Blue LED ON)
  - `dry = 500`   → Soil is dry (Red LED + Pump ON)
  - Between 501–799 → Optimal (Yellow LED ON)
- Outputs raw sensor value to Serial Monitor (9600 baud) for calibration

**Important:** The `wet` and `dry` threshold values **must be calibrated** for your specific sensor and soil type.

## How to Calibrate Thresholds
1. Upload the code to your Arduino
2. Open the Serial Monitor (Tools → Serial Monitor, 9600 baud)
3. Test with completely dry soil → note the reading (this will be your `dry` value)
4. Test with fully saturated/wet soil → note the reading (this will be your `wet` value)
5. Update the `wet` and `dry` variables in the code accordingly

## Installation & Usage
1. Connect the circuit as shown in the provided diagrams
2. Install the Arduino IDE
3. Copy the provided sketch into a new Arduino project
4. Verify and upload the code to your Arduino Uno
5. Open Serial Monitor to observe readings
6. Insert the soil moisture sensor probes into the soil of your plant
7. Power the system — it will begin monitoring automatically

## Future Improvements
- Add OLED/LCD display for moisture percentage
- Implement hysteresis to prevent pump rapid cycling
- Add WiFi (ESP8266/ESP32) for remote monitoring via Blynk or MQTT
- Include a real-time clock for scheduled watering
- Add water level sensor for the reservoir
- Make thresholds adjustable via potentiometer or buttons

## License
This project is open-source. Feel free to modify and improve it.

---
**Project maintained by:** MICROPROCESSORS KNUST OBUASI GROUP 1  
**Created:** April 2026