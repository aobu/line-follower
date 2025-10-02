void setup() {
  Serial.begin(9600);
  setState(STOP);

  //IR LED Setup
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 255);   // 0-255 (128 ≈ 50%)

  //Motor Setup
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor1_en12_pin, OUTPUT);
  pinMode(motor2_en34_pin, OUTPUT);

  digitalWrite(motor1_en12_pin, HIGH); // turns on enable for motor 1
  digitalWrite(motor2_en34_pin, HIGH); // turns on enable for motor 2


  //Websocket Setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  delay(100);

  ensureWiFi();
  ensureWebSocket();


}

void loop() {
  ensureWiFi();
  ensureWebSocket();

  handleWebSocketMessages();
  runStateMachine(); 
  //ir led test
  if (read_sensor() < 800){
    bot_forward(255);

  }
  else {
    bot_stop();
  }

  // // put your main code here, to run repeatedly:
  // bot_forward(200);
  // delay(2000);
  // bot_stop();
  // delay(2000);
  // bot_backwards(200);
  // delay(2000);
  // bot_stop();
  // delay(2000);
  // bot_clockwise();
  // delay(2000);
  // bot_stop();
  // delay(2000);
  // bot_counterclockwise();
  // delay(2000);
  // bot_stop();
  // delay(2000);
  // bot_turnRight(10);
  // delay(2000);
  // bot_stop();
  // delay(2000);
  // bot_turnLeft(10);
  // delay(2000);
  // bot_stop();

  // ensureWiFi();
  // ensureWebSocket();

  // handleWebSocketMessages();
  // handleButton();

  // delay(2);
}
