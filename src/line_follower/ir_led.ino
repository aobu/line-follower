// Pin definition for collision detection
const int ledPin = 3;      // IR LED anode (through resistor)
const int sensorPin = A0;  // Phototransistor collector
int base = 0;
int collide;

// Function to read analog value from sensor
int read_sensor() {
  int sensorValue = analogRead(sensorPin);
  return sensorValue;
}

// Function to tell check wall distance. True is wall close by and false is wall not in collision distane
bool check_wall(int ambient) {
  //int values[15];
  int avg=0;
  for (int i = 0; i < 15; i++) {
    avg += analogRead(sensorPin);
  }
  avg = avg/15;


  int adj_avg = avg-ambient;
  adj_avg -= collide;
  Serial.println(String(adj_avg)+ ", " + String(ambient));
  sendMessage(String(adj_avg));

  if (adj_avg < 10) {
    //bot_forward(200);
    return false;
  }
  else {
    bot_stop();
    //delay(1000);
    return true;
  }
}

// Function to store ambient light
int ambientlight_store() {
  analogWrite(ledPin, 0);  // 0-255 (128 ≈ 50%)
  int ambientSensorValue = analogRead(sensorPin);
  analogWrite(ledPin, 255);
  return ambientSensorValue;
}
