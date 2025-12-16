const int ledPin = 3;      // IR LED anode (through resistor)
const int sensorPin = A0;  // Phototransistor collector
int base = 0;

int read_sensor() {
  // Read sensor voltage (0–1023 corresponds to 0–5 V)
  int sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  return sensorValue;
  // Print result

}

void check_wall(int ambient) {

  //int values[15];
  int avg=0;
  for (int i = 0; i < 15; i++) {
    avg += analogRead(sensorPin);
  }
  avg = avg/15;


  int adj_avg = avg-ambient;
  Serial.println(String(adj_avg)+ ", " + String(ambient));

  if (adj_avg > -40) {
    //bot_forward(200);
  }
  else {
    bot_stop();
    //delay(1000);
    //machine_state++;
  }
}

int ambientlight_store() {
  analogWrite(ledPin, 0);  // 0-255 (128 ≈ 50%)
  int ambientSensorValue = analogRead(sensorPin);
  analogWrite(ledPin, 255);
  return ambientSensorValue;
}
