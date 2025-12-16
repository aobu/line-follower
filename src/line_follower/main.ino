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
  pinMode(button, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  delay(100);

  ensureWiFi();
  ensureWebSocket();
  delay(10);
  color_calibration();

  // while 
  // bot_clockwise_90();
  // bot_forward(255);
  // delay(100);
  // bot_clockwise_90();
  // base = ambientlight_store();
  // run_solo();
}

void loop() {
  // readWebSocket();
  follow_lane(1);
  // bot_forward(50);
  // delay(1000);
  // bot_turnLeft();
  // delay(1000);
  // bot_turnRight();
  // delay(1000);
  // delay(1000);
  //bot_forward(255);
  //check_wall(base);
  //follow_lane(1);
  // ensureWiFi();
  // ensureWebSocket();

  // ensureWiFi();
  // ensureWebSocket();

  // handleWebSocketMessages();
  // handleButton();

}
