# Phantom
Developing an Arduino-Enabled Dynamic Ventricular Phantom for Evaluating Microvascular Lung Hydraulic Resistance

## Servo Motor Control with Sensor Data Recording and Tabulation Project

## Overview
This project is designed to facilitate the precise control of servo motors connected to an Arduino, along with the recording and tabulation of data from flow and pressure sensors. It features an interactive Python interface that allows users to adjust servo positions and record sensor data into a txt file, critical for applications that require the real-time tracking and analysis of physical parameters.

## Requirements

### Hardware
- **Arduino Uno**
- **3 Servo Motors**: For simulating variations in physical parameters, connected to PWM pins D3 (Servo 1), D5 (Servo 2), and D6 (Servo 3).
  Specs : FR5311M Digital Servo / Operating Voltage: 4.8V-8.4V / 13.8 kg-cm (7.4V)
  Link : https://abra-electronics.com/sensors/sensors-liquid-flow/sen0216-gravity-digital-water-flow-sensor-for-arduino-1-8.html
- **Flow Sensors**: Connected to digital pins D2, D4, and D8 for flow rate monitoring.
  Specs : YF-S401 / 0.3-6 L/min / ±5% FS / 5880 pulses/L 
  Link : https://abra-electronics.com/sensors/sensors-liquid-flow/sen0216-gravity-digital-water-flow-sensor-for-arduino-1-8.html
- **Pressure Sensors**: Connected to analog pins A0, A1, and A2 for pressure measurement.
  Specs : 0-10 PSI range and 5V DC Input / 0.5% FS / 0.5 V - 4.5 V Optimal Range
  Link : https://snapklik.com/en-ca/product/pressure-transducer-stainless-pressure-transducer-5-psi-pressure-transducer-sensor-10-psi-steel-pressure-sender-sensor-g1-4-for-oil-tank-gas-tank-and-tank-0-10psi-0-10psi/0P2P4PL7318L5


![image](https://github.com/Fredmichll/Phantom/assets/149977886/30a690c8-44f3-48f7-9bd7-45958f9fdedb)

### Software
- **Arduino IDE**: For compiling and uploading the Arduino sketch.
- **Python 3.x**: The programming environment for the interface.
- **pyserial**: A Python package that enables serial communication with the Arduino.
  
## Installation Instructions

### Hydraulic Setup
- **Pulsative-Pumps** : 2 Pulsatile Pumps P-120 from TRANDOMED for the left side and rigth side of the heart.
- **1/4 Tubes**
- **1/4" Y Fittings**
- **1/4" Female Three Way Tee Joint and 1/4" Male to Male Straight Hex** : To fix the pressure sensors to the hydraulic system.

  
![image](https://github.com/Fredmichll/Phantom/assets/149977886/ca6718d9-69b5-4a1f-8225-fc4590b9d5d3)

### Arduino Setup
1. Ensure the <Servo.h> library is available in your Arduino IDE. This library is typically included by default, but if it's missing, you can download it via the Library Manager in the Arduino IDE.
2. Connect the servo motors and sensors to their designated pins on the Arduino as specified.
3. Open the Phantom.ino sketch in the Arduino IDE.
4. Compile and upload the sketch to your Arduino board.
   
### Python Environment Setup
1. Confirm that Python 3.x is installed on your computer.
2. Install the pyserial package at the same location at VSC folder using the command: `pip install pyserial`.

## Usage

### Running the Python Script
- Launch a terminal or command prompt.
- Navigate to the directory containing `Phantom_UI.py`.
- Start the script by typing `python Phantom_UI.py` into the terminal.
- Use the on-screen prompts to select the Arduino's COM port, modify servo motor positions, and trigger the simulated sensor data recording and tabulation.

## Features
- **Adjustable Servo Motor Control**: Offers the capability for users to input preferred servo positions, altering the system's physical configuration on demand.
- **Sensor Data Recording**: Automatically records and tabulates data from flow and pressure sensors, vital for the real-time observation and analysis of the system's operation.
- **User-Friendly Interface**: The Python script provides a simple menu-driven interface for system control and sensor data recording.
- **Comprehensive Data Logging**: The system logs all user inputs, the COM port used for communication, and outputs, including timestamps, servo positions, and simulated sensor readings, into a tabulated format       in a text file. This detailed logging, which includes the specific COM port utilized for the session, continues until the user exits the code, facilitating thorough post-execution review and analysis.
  
## Troubleshooting
- Verify that the Arduino is connected to the chosen COM port as indicated in the Python script.
- Ensure all physical connections are secure, particularly the sensors and servos to their corresponding pins.
- Check that the `pyserial` library is correctly installed in your Python environment and is accessible.

## License
This project is shared under the MIT License. Refer to the LICENSE file for more detailed information.

---
