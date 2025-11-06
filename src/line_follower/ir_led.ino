const int ledPin = 3;      // IR LED anode (through resistor)
const int sensorPin = A0;  // Phototransistor collector


int read_sensor() {
  // Read sensor voltage (0–1023 corresponds to 0–5 V)
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  return sensorValue;
  // Print result

}

void check_wall() {
  Serial.println(read_sensor());
  if (read_sensor() > 610) {
    bot_forward(200);
    delay(200);
  }
  else {
    bot_stop();
    delay(200);
  }
}
