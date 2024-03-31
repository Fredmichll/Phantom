/*
  Variables and objects initialization 
  The servo motors are connected PWM pins
  servo1 (PV) simulates variations in PVR and is connected to D3
  servo2 (CR1) simulates constant resistance in the pulmonary pathway and is connected to D5
  servo3 (CR2) simulates constant resistance in the systemic pathway and is connected to D6

  The pressure sensors are connected to digital pins
  Pressure Sensor 1 (P1) is connected to A0
  Pressure Sensor 2 (P2) is connected to A1
  Pressure Sensor 3 (P3) is connected to A2
  
  The flow sensors are connected to analog pins
  Flow Sensor 1 (FL1) is connected to D2
  Flow Sensor 2 (FL2) is connected to D4
  Flow Sensor 3 (FL3) is connected to D8
*/

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int flowSensorPins[] = {2, 4, 8};
const int pressureSensorPins[] = {A0, A1, A2};

// Initialize Global pulse counters for the flow sensors
volatile int pulseCount[3] = {0, 0, 0}; // {FL1,FL2,FL3}

void pulseCounterFL1() {pulseCount[0]++; }
void pulseCounterFL2() {pulseCount[1]++; }
void pulseCounterFL3() {pulseCount[2]++; }

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);

  // Initialize the flow sensor pins as inputs
  pinMode(flowSensorPins[0], INPUT_PULLUP); }
  pinMode(flowSensorPins[1], INPUT_PULLUP); }
  pinMode(flowSensorPins[2], INPUT_PULLUP); }
  
  // Attach the interrupt service routines for the flow sensors
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[0]), pulseCounterFL1, RISING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[1]), pulseCounterFL2, RISING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[2]), pulseCounterFL3, RISING);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "READ") {
      readAndSendSensorData();
    } else {
      adjustServosAndConditions(command);
    }
  }
}

void readAndSendSensorData() {
  // Reset pulse counters
  pulseCount[3] = {0, 0, 0};
  
  // Start the measurement period of 1 sec to calculate flow rates
  interrupts();
  delay(1000);
  noInterrupts();

  // Send the data over Serial
  Serial.print(readFlowSensor(pulseCount[0])); Serial.print(",");
  Serial.print(readFlowSensor(pulseCount[1])); Serial.print(",");
  Serial.print(readFlowSensor(pulseCount[2])); Serial.print(",");
  Serial.print(readPressureSensor(pressureSensorPins[0])); Serial.print(",");
  Serial.print(readPressureSensor(pressureSensorPins[1])); Serial.print(",");
  Serial.println(readPressureSensor(pressureSensorPins[2]));
}

  /*
  The readFlowSensor will convert the frequency readings to Flow Rates to L/min.
  For the SEN0216 Digital Water Flow Sensor 1L = 5880 pulses, thus the equation
  x = number of pulses recorded by flow sensor
  for the flow rate is Q = x/5880 (L/s) which gives Q = x/98 (L/min)
  */

float readFlowSensor(int pulseCount) {
  // Read and record the sensors readings 
  return pulseCount/98.0;
} 

float readPressureSensor(int pin) {
  const float Vcc = 5.0; // Power supply voltage
  const float psi_to_mmHg = 51.715; // Conversion factor from PSI to mmHg 

  int sensorValue = analogRead(pin); // Read the sensor value
  float voltage = sensorValue * (Vcc / 1023.0); // Convert the value to voltage

  // Assuming a 0.5-4.5V output range for 0-30 PSI
  float psi;
  if (voltage <= 0.5) {
    psi = 0.0; // Handle error condition or below range
  } else if (voltage >= 4.5) {
    psi = 30.0; // Handle error condition or above range
  } else {
    psi = (voltage - 0.5) * 30.0 / 4.0; // Map voltage to PSI
  }

  return psi * psi_to_mmHg; // Convert PSI to mmHg and return
}

void adjustServosAndConditions(String conditions) {

  // Parse the conditions string
  int firstComma = conditions.indexOf(',');
  int secondComma = conditions.indexOf(',', firstComma + 1);
  int thirdComma = conditions.indexOf(',', secondComma + 1);

  // Assuming the string format is: servo1,servo2,servo3,*,*,*,*,*
  int servo1Pos = conditions.substring(0, firstComma).toInt();
  int servo2Pos = conditions.substring(firstComma + 1, secondComma).toInt();
  int servo3Pos = conditions.substring(secondComma + 1, thirdComma).toInt();

  // Convert percentage to servo angle (0-100% -> 0-90 degrees for full range, adjust as necessary)
  // technically each 1% change in input corresponds to a 0.9-degree change but all the values are 
  // int they are rounded to nearest integer
  servo1.write(map(servo1Pos, 0, 100, 0, 90));
  servo2.write(map(servo2Pos, 0, 100, 0, 90));
  servo3.write(map(servo3Pos, 0, 100, 0, 90));
}