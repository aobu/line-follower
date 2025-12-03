void setup() {
  Serial.begin(9600);
  //setState(STOP);

  // Arduino LED
  pinMode(LED_BUILTIN, OUTPUT);

  //IR LED Setup
  // pinMode(ledPin, OUTPUT);
  // analogWrite(ledPin, 255);   // 0-255 (128 ≈ 50%)
  // base = ambientlight_store();

  //Motor Setup
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor1_en12_pin, OUTPUT);
  pinMode(motor2_en34_pin, OUTPUT);

  digitalWrite(motor1_en12_pin, HIGH); // turns on enable for motor 1
  digitalWrite(motor2_en34_pin, HIGH); // turns on enable for motor 2

  // Color Sensor Setup
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(blue1, OUTPUT);
  pinMode(blue2, OUTPUT);

  //Websocket Setup
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // pinMode(LED_PIN, OUTPUT);

  // delay(100);

  // ensureWiFi();
  // ensureWebSocket();
}

void loop() {
  delay(1000);
  color_calibration();
  follow_lane(1);
  // ensureWiFi();
  // ensureWebSocket();

  // ensureWiFi();
  // ensureWebSocket();

  // handleWebSocketMessages();
  // handleButton();

}
