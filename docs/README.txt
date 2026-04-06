# Arduino Automatic Plant Watering System

## Project Overview
This is an Arduino-based automatic soil moisture monitoring and plant watering system. 
The system continuously measures soil moisture levels using a capacitive soil moisture sensor and 
automatically activates a water pump when the soil becomes too dry. It also provides visual 
feedback through LCD display indicating the current moisture status and pump on/off status.

The project is designed for the microprocessors group 1 project

## Features
- Real-time soil moisture monitoring using a capacitive soil moisture sensor
- Automatic water pump activation when soil is dry
- Solar powered water pump controlled by the microprocessor
- Visual status indication with LCD feedback:
  - **Moisture: x.x%**: x.x in the range of 0.0 to 70.0 → Pump is ON
  - **Moisture: x.x%**: x.x in the range of 71.0 to 100.0 → Pump goes OFF
  - **Motor: ON**: motor is on, is pumping water
  - **Motor: OFF**: motor is off, not pumping water
- Serial monitor output for debugging and calibration

## Hardware Components
- Arduino Uno
- Capacitive Soil Moisture Sensor (with power control)
- 16X2 LCD 
- 220Ω resistors (for LCD)
- Water pump (relay module + pump)
- 9V or USB power supply for Arduino
- Jumper wires

## Circuit Connections

**Soil Moisture Sensor:**
- VCC → Arduino 5V pin
- GND → Arduino GND
- A0 (Analog) → Arduino Analog Pin A0

RS (Register Select) → Arduino Digital Pin 7
E (Enable) → Arduino Digital Pin 6
D4 (Data 4) → Arduino Digital Pin 5
D5 (Data 5) → Arduino Digital Pin 4
D6 (Data 6) → Arduino Digital Pin 3
D7 (Data 7) → Arduino Digital Pin 2
VSS (Ground) → Arduino GND
VDD (Power) → Arduino 5V
V0 (Contrast) → Potentiometer Center Pin (for brightness control)
A/K (Backlight) → Arduino 5V/GND (via 220Ω resistor)

**Water Pump:**
- Pump control → Arduino Analogue Pin 9

**Power:**
- Pump powered by solar panel
- Arduino powered via USB cable (or external 9V supply)

## Software (Arduino Sketch)

The provided code:
- Reads the soil moisture sensor continuously using analog input (A0) and converts it to a percentage (0–100%)
- Maps raw sensor values (0–1023) to moisture percentage using:
	0 → 0% (completely dry)
	1023 → 100% (fully wet)
- Uses two user-adjustable thresholds for control:
  	setL_moisture → Lower limit (default: 30%) → triggers watering
	setH_moisture → Upper limit (default: 70%) → stops watering
- Implements hysteresis control to avoid rapid ON/OFF switching:
	Moisture < Low threshold → Pump ON
	Moisture > High threshold → Pump OFF
	Between thresholds → No change (stable operation)
- Controls a water pump via a relay connected to pin 9:
	HIGH → Pump ON
	LOW → Pump OFF
- Provides a 16x2 LCD interface (pins 2–7) for real-time display:
     Normal mode:
	Line 1 → Current moisture (%)
	Line 2 → Pump status (ON/OFF)
     Setting mode:
	Displays adjustable low (L) and high (H) thresholds
- Includes a 3-button interface for user control:
     SET button → cycles modes:
	Mode 0 → Normal operation
	Mode 1 → Adjust Low threshold
	Mode 2 → Adjust High threshold
      UP button → increases selected value
      DOWN button → decreases selected value
- Stores threshold values in EEPROM memory:
	Low threshold saved at address 10
	High threshold saved at address 15
	Ensures settings persist after power loss
- Performs EEPROM validation at startup:
	Resets values if out of range (0–100%)
	Ensures Low < High to maintain proper control logic

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
- Add WiFi (ESP8266/ESP32) for remote monitoring via Blynk or MQTT
- Include a real-time clock for scheduled watering
- Add water level sensor for the reservoir
- Make thresholds adjustable via potentiometer or buttons

## License
This project is open-source. Feel free to modify and improve it.

---
**Project maintained by:** MICROPROCESSORS KNUST OBUASI GROUP 1  
**Created:** April 2026