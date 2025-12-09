// int machine_state = 0;

// void run_solo() {
//   while (machine_state == 0) { // State 0 = collision avoidance
//     bot_forward(255);
//     if (check_wall(base)) {
//       state++;
//     }
//   }

//   while (machine_state == 1) { // State 1 = reverse until on red lane
//     bot_backwards(255);
//     if (color_sense(1)) {
//       machine_state++;
//     }
//   }

//   while (machine_state == 2) { // State 2 = turn right to red lane
//     bot_turnRight();
//     if(color_sense(1)) {
//       machine_state++;
//     }
//   }

//   while (machine_state== 3) { // Bot follow red lane
//     follow_lane(1);
//     if (check_wall(base)) {
//       machine_state++;
//     };
//   }

//   while (machine_state== 4) { // Bot turn to yellow lane
//     bot_turnLeft();
//     // possible magnetic encoder code?
//   }

//   while (machine_state== 5) { // Bot on yellow lane
//     bot_forward(255);
//     if (color_sense(2)) {
//       machine_state++;
//     }
//   }

//   while (machine_state== 6) { // State 2 = turn right to yellow lane
//     bot_turnRight();
//     if(color_sense(2)) {
//       machine_state++;
//     }
//   }

//   while (machine_state== 7) { // Bot follow yellow lane
//     follow_lane(1);
//     if (check_wall(base)) {
//       machine_state++;
//     };
//   }

//   while (machine_state== 8) {
//     bot_turnLeft();
//     if (check_wall(base)) {
//       machine_state++;
//     };
//   }

// } 