const int ledPin = 3;      // IR LED anode (through resistor)
const int sensorPin = A0;  // Phototransistor collector

void read_sensor() {
  // Read sensor voltage (0–1023 corresponds to 0–5 V)
  int sensorValue = analogRead(sensorPin);

  // Print result
  Serial.println(sensorValue);
}
