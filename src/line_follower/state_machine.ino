int machine_state = 0;

void run_solo() {
  // color_calibration();
  button_check(5);
  base = ambientlight_store();
  Serial.print("Machine State: ");
  Serial.println(machine_state);
  
  button_check(6);
  while (machine_state == 0) { // State 0 = collision avoidance
    delay(500);
    bot_forward(50);
    check_wall(base);
  }
  Serial.print("Machine State: ");
  Serial.println(machine_state);

  while (machine_state == 1) { // State 1 = reverse until on red lane
    bot_backwards(50);
    if (color_sense(1)) {
      machine_state++;
    }
  }

  while (machine_state == 2) { // State 2 = turn right to red lane
    bot_turnRight();
    if(color_sense(1)) {
      machine_state++;
    }
  }

  while (machine_state== 3) { // Bot follow red lane
    follow_lane(1);
    check_wall(base);
  }

  while (machine_state== 4) { // Bot turn to yellow lane
    bot_lane_left();
  }

  while (machine_state== 5) { // Bot on yellow lane
    bot_forward(255);
    if (color_sense(2)) {
      machine_state++;
    }
  }

  while (machine_state== 6) { // State 2 = turn right to yellow lane
    bot_turnRight();
    if(color_sense(2)) {
      machine_state++;
    }
  }

  while (machine_state== 7) { // Bot follow yellow lane
    follow_lane(1);
    check_wall(base);
  }

  while (machine_state== 8) {
    bot_clockwise_90();
    check_wall(base);
  }

} 