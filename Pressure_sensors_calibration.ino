const int pressureSensorPins[] = {A1, A2, A3};


void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  float p1 = readPressureSensor(pressureSensorPins[0]);
  float p2 = readPressureSensor(pressureSensorPins[1]);
  float p3 = readPressureSensor(pressureSensorPins[2]);

  Serial.println("P1: " + String(p1) + " mmHg");
  Serial.println("P2: " + String(p2) + " mmHg");
  Serial.println("P3: " + String(p3) + " mmHg");
  delay(1000); // Wait for 1 second before reading again
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
    psi = (voltage - 0.5) * 30.0 / (4.5 - 0.5); // Map voltage to PSI
  }

  return psi * psi_to_mmHg; // Convert PSI to mmHg and return
}

