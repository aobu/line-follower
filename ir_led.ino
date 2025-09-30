const int ledPin = 3;      // IR LED anode (through resistor)
const int sensorPin = A0;  // Phototransistor collector
bool 

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Turn on IR LED with ~50% brightness
  analogWrite(ledPin, 255);   // 0-255 (128 ≈ 50%)
  delayMicroseconds(200);     // let sensor settle a little
}

void loop() {

  // Read sensor voltage (0–1023 corresponds to 0–5 V)
  int sensorValue = analogRead(sensorPin);

  // Print result
  Serial.println(sensorValue);
  if(sensorValue < 800) {
    bot_stop();
  }


  delay(500);  // small delay between reads
}
