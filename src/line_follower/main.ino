void setup() {
  Serial.begin(9600);
  setState(STOP);

  //IR LED Setup
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 255);  // 0-255 (128 ≈ 50%)

  //Motor Setup
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor1_en12_pin, OUTPUT);
  pinMode(motor2_en34_pin, OUTPUT);

  digitalWrite(motor1_en12_pin, HIGH);  // turns on enable for motor 1
  digitalWrite(motor2_en34_pin, HIGH);  // turns on enable for motor 2

  // Color Sensor Setup
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);

  //Websocket Setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  delay(100);

<<<<<<< Updated upstream
  ensureWiFi();
  ensureWebSocket();
=======
  // ensureWiFi();
  // ensureWebSocket();


>>>>>>> Stashed changes
}

void loop() {
  // ensureWiFi();
  // ensureWebSocket();

<<<<<<< Updated upstream
  // ========================== WE ARE BOT 1


  // // // Kick off the sequence as Bot 1:
  // if (!sequenceStarted && client.connected()) {
  //   flashLED(3, 120, 120);  // Bot 1 flashes LED
  //   sendToPartner("bot 2 can go from bot 1");     // ask Bot 2 to go FORWARD (state=2) for 5s
  //   sequenceStarted = true;
  // }

  // // If Bot 2 tells us to go forward, run for 5 seconds then stop.
  // if (wsCommandJustSet) {
  //   wsCommandJustSet = false;
  //   if (lastReceivedCommand == FORWARD) {
  //     selfMoveUntil = millis() + 5000UL;
  //   }
  // }

  // // Enforce the 5s local move window for Bot 1
  // if (selfMoveUntil && millis() > selfMoveUntil) {
  //   setState(STOP);
  //   selfMoveUntil = 0;
  // }



  // ========================== WE ARE BOT 2



  handleWebSocketMessages();
  runStateMachine();

=======
  // handleWebSocketMessages();
  // runStateMachine(); 
  //ir led test
  // if (read_sensor() < 800){
  //   bot_forward(255);

  // }
  // else {
  //   bot_stop();
  // }

  //color_sensing();

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

  check_wall();
>>>>>>> Stashed changes
}
