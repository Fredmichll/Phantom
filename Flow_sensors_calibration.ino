// Define the flow sensor pins
const int flowSensorPins[] = {8, 7, 5}; // Example pins, adjust according to your setup

// Initialize Global pulse counters for the flow sensors
volatile unsigned long pulseCountFL1 = 0;
volatile unsigned long pulseCountFL2 = 0;
volatile unsigned long pulseCountFL3 = 0;

// Interrupt service routines for counting pulses
void pulseCounterFL1() { pulseCountFL1++; }
void pulseCounterFL2() { pulseCountFL2++; }
void pulseCounterFL3() { pulseCountFL3++; }

void setup() {
  Serial.begin(9600);
  
  // Initialize the flow sensor pins as inputs
  pinMode(flowSensorPins[0], INPUT_PULLUP);
  pinMode(flowSensorPins[1], INPUT_PULLUP);
  pinMode(flowSensorPins[2], INPUT_PULLUP);

  // Attach the interrupt service routines for the flow sensors
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[0]), pulseCounterFL1, RISING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[1]), pulseCounterFL2, RISING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPins[2]), pulseCounterFL3, RISING);
}

void loop() {
  // Reset pulse counters
  pulseCountFL1 = 0;
  pulseCountFL2 = 0;
  pulseCountFL3 = 0;
  
  // Start the measurement period
  interrupts();
  delay(1000); // Measure for 1 second
  noInterrupts();

  // Calculate flow rates in L/min
  float flowRateFL1 = (pulseCountFL1 / 1); // Example conversion, adjust based on your sensor's specifications
  float flowRateFL2 = (pulseCountFL2 / 1);
  float flowRateFL3 = (pulseCountFL3 / 1);

  // Send the flow rates over Serial
  Serial.print("Flow Sensor 1: "); Serial.print(flowRateFL1); Serial.println(" L/min");
  Serial.print("Flow Sensor 2: "); Serial.print(flowRateFL2); Serial.println(" L/min");
  Serial.print("Flow Sensor 3: "); Serial.print(flowRateFL3); Serial.println(" L/min");

  delay(1000); // Wait for 5 seconds before measuring again
}
