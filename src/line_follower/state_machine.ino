// Global variables for state machine
int machine_state = 0;

// Function to run solo demo
void run_solo(int lane) {
  // rerun websocket to keep communication alive
  ensureWiFi();
  ensureWebSocket();
  handleWebSocketMessages();
  
  // color calibration
  color_calibration();

  // variable i used for one time actions during states
  int i = 0;

  // Check battery health and IR sensor
  button_check(5);
  base = ambientlight_store();
  analogWrite(ledPin, 255);
  battery_health();

  // Show battery health and start machine 
  button_check(6);
  digitalWrite(battery1_charge, LOW);
  digitalWrite(battery2_charge, LOW);
  while (machine_state == 0) {  // State 0 = collision avoidance
    bot_forward(50);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 1) {  // State 1 = move towards red or blue lane
    if (i == 0) {
      bot_clockwise();
      delay(1400);
      i++;
    }
    bot_forward(50);
    if (color_sense(lane)) {
      bot_stop();
      machine_state++;
    }
  }

  while (machine_state == 2) {  // State 2 = turn right to red or blue lane lane to 
    bot_backwards(50);
    delay(200);
    bot_turnLeft();
    delay(1000);
    bot_backwards(50);
    delay(200);
    bot_turnLeft();
    delay(1000);
    bot_stop();
    delay(200);
    machine_state++;
  }

  while (machine_state == 3) {  // Bot follow red or blue lane until at wall
    follow_lane(lane);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 4) {  // Bot turn to yellow lane
    bot_backwards(50);
    delay(600);
    bot_turnLeft();
    delay(2100);
    bot_forward(50);
    while (!color_sense(lane)) {
      bot_forward(50);
    }
    bot_stop();
    machine_state++;
  }
  while (machine_state == 5) {  // Orient bot onto yellow lane
    bot_backwards(50);
    delay(400);
    bot_counterclockwise();
    delay(750);
    bot_stop();
    machine_state++;
  }

  while (machine_state == 6) {  // Follow yellow lane
    follow_lane(2);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 7) {  // turn to return spot
    bot_backwards(50);
    delay(400);
    bot_counterclockwise();
    delay(650);
    bot_stop();
    machine_state++;
  }

  while (machine_state == 8) {  // Bot follow yellow lane
    bot_forward(50);
    if (check_wall(base)) {
      machine_state++;
    }    
  }

  bot_stop();
}


// Joint demo as bot 1
void run_partner_bot1() {
  // Keep websocket communication
  ensureWiFi();
  ensureWebSocket();
  handleWebSocketMessages();

  // Calibrate lanes
  color_calibration();

  // variable for one time actions in states and messages
  int i = 0;
  String message;

  // Check battery health and IR sensor
  button_check(5);
  battery_health();
  base = ambientlight_store();
  analogWrite(ledPin, 255);

  // Show battery health and start
  button_check(6);
  digitalWrite(battery1_charge, LOW);
  digitalWrite(battery2_charge, LOW);
  while (machine_state == 0) {  // State 0 = collision avoidance
    message = "828BD9E1B7C7.bot start";
    sendMessage(message);
    bot_forward(50);
    delay(3500);
    machine_state++;
  }

  while (machine_state == 1) {  // State 1 = reverse until on red lane
    if (i == 0) {
      bot_clockwise();
      delay(1300);
      i++;
    }
    bot_forward(50);
    if (color_sense(1)) {
      message = "828BD9E1B7C7.red lane found";
      sendMessage(message);
      machine_state++;
    }
  }

  while (machine_state == 2) {  // State 2 = turn right to red lane
    bot_backwards(50);
    delay(1200);
    bot_turnLeft();
    delay(1000);
    bot_backwards(50);
    delay(200);
    machine_state++;
  }

  while (machine_state == 3) {  // Bot follow red lane
    follow_lane(1);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 4) {  // Bot turn to yellow lane
    if (i == 1) {
      bot_counterclockwise();
      delay(900);
    } 
    bot_forward(50);
    if (color_sense(2)) {
      bot_stop();
      machine_state++;
    }
  }
  while (machine_state == 5) {  // Bot on yellow lane
    if (i == 2) {
      bot_backwards(50);
      delay(400);
      bot_counterclockwise();
      delay(800);
      bot_stop();
    }
    handleWebSocketMessages();
    if (partner_state == 1) {
      machine_state++;
    }
  }

  while (machine_state == 6) {  // State 2 = turn right to yellow lane
    follow_lane(2);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 7) {  // Bot follow yellow lane
    bot_backwards(50);
    delay(400);
    bot_counterclockwise();
    delay(700);
    bot_stop();
    machine_state++;
  }

  while (machine_state == 8) {  // Bot follow yellow lane
    bot_forward(50);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  bot_stop();
  message = "828BD9E1B7C7.returned";
  sendMessage(message);
}


// Joint demo as bot 2
void run_partner_bot2() {
  // Keep websocket communication
  ensureWiFi();
  ensureWebSocket();
  handleWebSocketMessages();

  // Calibrate lanes
  color_calibration();

  // variable for one time actions in states and messages
  int i = 0;
  String message;

  // Check battery health and IR sensor
  button_check(5);
  battery_health();
  base = ambientlight_store();
  analogWrite(ledPin, 255);

  // Show battery health and start
  button_check(6);
  digitalWrite(battery1_charge, LOW);
  digitalWrite(battery2_charge, LOW);
  while (machine_state == 0) {  // State 0 = collision avoidance
    handleWebSocketMessages();
    if (partner_state == 2) {
      message = "828BD9E1B7C7.bot start";
      sendMessage(message);
      while (!check_wall(base)) {
        bot_forward(50);
      }
      machine_state++;
    }
  }

  while (machine_state == 1) {  // State 1 = reverse until on red lane
    if (i == 0) {
      bot_clockwise();
      delay(1300);
      i++;
    }
    bot_forward(50);
    if (color_sense(3)) {
      message = "828BD9E1B7C7.blue lane found";
      sendMessage(message);
      machine_state++;
    }
  }

  while (machine_state == 2) {  // State 2 = turn right to red lane
    bot_backwards(50);
    delay(1200);
    bot_turnRight();
    delay(1000);
    bot_backwards(50);
    delay(200);
    machine_state++;
  }

  while (machine_state == 3) {  // Bot follow blue lane
    follow_lane(3);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 4) {  // Bot turn to yellow lane
    if (i == 1) {
      bot_clockwise();
      delay(900);
    } 
    bot_forward(50);
    if (color_sense(2)) {
      bot_stop();
      machine_state++;
    }
  }
  while (machine_state == 5) {  // Bot on yellow lane
    if (i == 2) {
      bot_backwards(50);
      delay(400);
      bot_counterclockwise();
      delay(800);
      bot_stop();
    }
    handleWebSocketMessages();
    if (partner_state == 3) {
      machine_state++;
    }
  }

  while (machine_state == 6) {  // State 2 = turn right to yellow lane
    follow_lane(2);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  while (machine_state == 7) {  // Bot follow yellow lane
    bot_backwards(50);
    delay(400);
    bot_clockwise();
    delay(700);
    bot_stop();
    machine_state++;
  }

  while (machine_state == 8) {  // Bot follow yellow lane
    bot_forward(50);
    if (check_wall(base)) {
      machine_state++;
    }
  }

  bot_stop();
  message = "returned";
  sendMessage(message);
}