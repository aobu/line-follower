void setup() {
  Serial.begin(9600);
  //setState(STOP);

  // Arduino LED
  pinMode(LED_BUILTIN, OUTPUT);

  //IR LED Setup
  pinMode(ledPin, OUTPUT);

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
  pinMode(signal_LED, OUTPUT);

  // Battery Health
  pinMode(battery1_pin, OUTPUT);
  pinMode(battery2_pin, OUTPUT);

  // WIFI and Websocket
  ensureWiFi();
  ensureWebSocket();
  handleWebSocketMessages();
  delay(10);
}

void loop() {
  // run run_solo function to run solo demo (lane 1 means red, while lane 3 means blue)

  // run run_partner_bot1 function to run joint demo as bot 1
  // run run_partner_bot2 function to run joint demo as bot 2
  run_partner_bot2();
}
