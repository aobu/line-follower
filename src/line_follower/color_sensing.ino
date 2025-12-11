int red1 = 2;
int blue1 = 11;
int red2 = 12;
int blue2 = 13;
int pr1 = A4;
int pr2 = A5;
int red_calibration_r1;
int red_calibration_b1;
int blue_calibration_r1;
int blue_calibration_b1;
int black_calibration_r1;
int black_calibration_b1;
int yellow_calibration_r1;
int yellow_calibration_b1;
int red_calibration_r2;
int red_calibration_b2;
int blue_calibration_r2;
int blue_calibration_b2;
int black_calibration_r2;
int black_calibration_b2;
int yellow_calibration_r2;
int yellow_calibration_b2;
int baseline_calibration_r1;
int baseline_calibration_r2;
int baseline_calibration_b1;
int baseline_calibration_b2;

void follow_lane(int desired_lane) {
  int baseline1 = 0;
  int baseline2 = 0;
  int blue_reading1 = 0;
  int red_reading1 = 0;
  int blue_reading2 = 0;
  int blue_1 = 0;
  int red_1 = 0;
  int blue_2 = 0;
  int red_2 = 0;
  int red_reading2 = 0;
  
  // Baseline calibration
  turnoffLEDs();
  baseline1 = analogRead(pr1);
  baseline2 = analogRead(pr2);
  delay(10);

  // Read Red
  turnonRed();
  delay(10);
  red_reading1 = analogRead(pr1);
  red_reading2 = analogRead(pr2);

  // Read Blue 
  turnonBlue();
  delay(10);
  
  blue_reading1 = analogRead(pr1);
  blue_reading2 = analogRead(pr2);

  turnoffLEDs();

  // Only print reading 1
  blue_1 = blue_reading1 - baseline1;
  red_1 = red_reading1 - baseline1;
  blue_2 = blue_reading2 - baseline2;
  red_2 = red_reading2 - baseline2;
  int lane_number1 = lane_decider1(blue_1, red_1);
  int lane_number2 = lane_decider2(blue_2, red_2);

  Serial.print("Red1: ");
  Serial.println(red_1);
  Serial.print("Blue1: ");
  Serial.println(blue_1);
  Serial.print("Red2: ");
  Serial.println(red_2);
  Serial.print("Blue2: ");
  Serial.println(blue_2);

  color_sensor(lane_number1, lane_number2, desired_lane);
}

bool color_sense(int desired_lane) {
  int baseline1 = 0;
  int baseline2 = 0;
  int blue_reading1 = 0;
  int red_reading1 = 0;
  int blue_reading2 = 0;
  int blue_1 = 0;
  int red_1 = 0;
  int blue_2 = 0;
  int red_2 = 0;
  int red_reading2 = 0;
  
  // Baseline calibration
  turnoffLEDs();
  baseline1 = analogRead(pr1);
  baseline2 = analogRead(pr2);
  delay(10);

  // Read Red
  turnonRed();
  delay(10);
  red_reading1 = analogRead(pr1);
  red_reading2 = analogRead(pr2);

  // Read Blue 
  turnonBlue();
  delay(10);
  
  blue_reading1 = analogRead(pr1);
  blue_reading2 = analogRead(pr2);

  turnoffLEDs();

  // Only print reading 1
  blue_1 = blue_reading1 - baseline1;
  red_1 = red_reading1 - baseline1;
  blue_2 = blue_reading2 - baseline2;
  red_2 = red_reading2 - baseline2;
  int lane_number1 = lane_decider1(blue_1, red_1);
  int lane_number2 = lane_decider2(blue_2, red_2);

  if (lane_number1 == lane_number2 && lane_number1 == desired_lane) {
    return true;
  } else {
    return false;
  }
}

void color_sensor(int lane_number1, int lane_number2, int desired_lane) {
  Serial.print("lane_number1: ");
  Serial.println(lane_number1);
  Serial.print("lane_number2: ");
  Serial.println(lane_number2);
  Serial.print("desired lane: ");
  Serial.println(desired_lane);
  if((lane_number1 == 0 &&
   lane_number2 == 0) || (lane_number1 == 4 && lane_number2 == 4)) {
    bot_stop();
    return;
  }

  if (lane_number1 == desired_lane && lane_number1 == lane_number2) {
    bot_forward(50);
  } else if (lane_number1 == desired_lane && lane_number2 != desired_lane) {
    bot_turnLeft();
  } else if (lane_number2 == desired_lane && lane_number1 != desired_lane) {
    bot_turnRight();
  }
}

int lane_decider1(int blue_reading, int red_reading) {
  if (red_reading <= (red_calibration_r1 + 10) && red_reading >= (red_calibration_r1 - 10) && blue_reading >= (red_calibration_b1 - 10) && blue_reading <= (red_calibration_b1 + 10)) {
    Serial.println("Sensor 1 On Red Lane");
    return 1;
  } else if (red_reading <= (yellow_calibration_r1 + 10) && red_reading >= (yellow_calibration_r1 - 10) && blue_reading >= (yellow_calibration_b1 - 10) && blue_reading <= (yellow_calibration_b1 + 10)) {
    Serial.println("Sensor 1 On Yellow Lane");
    return 2;
  } else if (red_reading >= (blue_calibration_r1 - 10) && red_reading <= (blue_calibration_r1 + 10) && blue_reading <= (blue_calibration_b1 + 10) && blue_reading >= (blue_calibration_b1 - 10)) {
    Serial.println("Sensor 1 On Blue Lane");
    return 3;
  } else if (red_reading >= (black_calibration_r1 - 10) && red_reading <= (black_calibration_r1 + 10) && blue_reading <= (black_calibration_b1 + 10) && blue_reading >= (black_calibration_b1 - 10)) {
    Serial.println("Sensor 1 On Black");
    return 4;
  } else {
    return 0;
  }
}

int lane_decider2(int blue_reading, int red_reading) {
  if (red_reading <= (red_calibration_r2 + 10) && red_reading >= (red_calibration_r2 - 10) && blue_reading >= (red_calibration_b2 - 10) && blue_reading <= (red_calibration_b2 + 10)) {
    Serial.println("Sensor 2 On Red Lane");
    return 1;
  } else if (red_reading <= (yellow_calibration_r2 + 10) && red_reading >= (yellow_calibration_r2 - 10) && blue_reading >= (yellow_calibration_b2 - 10) && blue_reading <= (yellow_calibration_b2 + 10)) {
    Serial.println("Sensor 2 On Yellow Lane");
    return 2;
  } else if (red_reading >= (blue_calibration_r2 - 10) && red_reading <= (blue_calibration_r2 + 10) && blue_reading <= (blue_calibration_b2 + 10) && blue_reading >= (blue_calibration_b2 - 10)) {
    Serial.println("Sensor 2 On Blue Lane");
    return 3;
  } else if (red_reading >= (black_calibration_r2 - 10) && red_reading <= (black_calibration_r2 + 10) && blue_reading <= (black_calibration_b2 + 10) && blue_reading >= (black_calibration_b2 - 10)) {
    Serial.println("Sensor 2 On Black");
    return 4;
  } else {
    return 0;
  }
}

void color_calibration() {
  turnoffLEDs();
  baseline_calibration_r1 = analogRead(pr1);
  baseline_calibration_b1 = analogRead(pr1);
  baseline_calibration_r2 = analogRead(pr2);
  baseline_calibration_b2 = analogRead(pr2);

  calibrate_red();
  
  Serial.print("Red Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(red_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(red_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(red_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(red_calibration_b2);

  delay(5000);
  turnoffLEDs();
  calibrate_yellow();

  Serial.print("Yellow Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(yellow_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(yellow_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(yellow_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(yellow_calibration_b2);

  delay(5000);
  turnoffLEDs();
  calibrate_blue();

  Serial.print("Blue Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(blue_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(blue_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(blue_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(blue_calibration_b2);

  delay(5000);
  turnoffLEDs();
  calibrate_black();

  Serial.print("Black Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(black_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(black_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(black_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(black_calibration_b2);

  turnoffLEDs();
  delay(5000);
  red_calibration_r1 = red_calibration_r1 - 25;
  red_calibration_r2 = red_calibration_r2 - 25;
  red_calibration_b1 = red_calibration_b1 - 25;
  red_calibration_b2 = red_calibration_b2 - 25;

  yellow_calibration_r1 = yellow_calibration_r1 - 30;
  yellow_calibration_r2 = yellow_calibration_r2 - 30;
  yellow_calibration_b1 = yellow_calibration_b1 - 30;
  yellow_calibration_b2 = yellow_calibration_b2 - 30;

  blue_calibration_r1 = blue_calibration_r1 - 20;
  blue_calibration_r2 = blue_calibration_r2 - 20;
  blue_calibration_b1 = blue_calibration_b1 - 20;
  blue_calibration_b2 = blue_calibration_b2 - 20;

  black_calibration_r1 = black_calibration_r1 - 20;
  black_calibration_r2 = black_calibration_r2 - 20;
  black_calibration_b1 = black_calibration_b1 - 20;
  black_calibration_b2 = black_calibration_b2 - 20;
}

void calibrate_red() {
  turnoffLEDs();

  turnonRed();
  red_calibration_r1 = analogRead(pr1);
  red_calibration_r1 = red_calibration_r1 - baseline_calibration_r1;
  red_calibration_r2 = analogRead(pr2);
  red_calibration_r2 = red_calibration_r2 - baseline_calibration_r2;

  turnonBlue();
  red_calibration_b1 = analogRead(pr1);
  red_calibration_b1 = red_calibration_b1 - baseline_calibration_b1;
  red_calibration_b2 = analogRead(pr2);
  red_calibration_b2 = red_calibration_b2 - baseline_calibration_b2;
}

void calibrate_yellow() {
  turnoffLEDs();

  turnonRed();
  yellow_calibration_r1 = analogRead(pr1);
  yellow_calibration_r1 = yellow_calibration_r1 - baseline_calibration_r1;
  yellow_calibration_r2 = analogRead(pr2);
  yellow_calibration_r2 = yellow_calibration_r2 - baseline_calibration_r2;

  turnonBlue();
  yellow_calibration_b1 = analogRead(pr1);
  yellow_calibration_b1 = yellow_calibration_b1 - baseline_calibration_b1;
  yellow_calibration_b2 = analogRead(pr2);
  yellow_calibration_b2 = yellow_calibration_b2 - baseline_calibration_b2;
}

void calibrate_blue() {
  turnoffLEDs();

  turnonRed();
  blue_calibration_r1 = analogRead(pr1);
  blue_calibration_r1 = blue_calibration_r1 - baseline_calibration_r1;
  blue_calibration_r2 = analogRead(pr2);
  blue_calibration_r2 = blue_calibration_r2 - baseline_calibration_r2;

  turnonBlue();
  blue_calibration_b1 = analogRead(pr1);
  blue_calibration_b1 = blue_calibration_b1 - baseline_calibration_b1;
  blue_calibration_b2 = analogRead(pr2);
  blue_calibration_b2 = blue_calibration_b2 - baseline_calibration_b2;
}

void calibrate_black() {
  turnoffLEDs();

  turnonRed();
  black_calibration_r1 = analogRead(pr1);
  black_calibration_r1 = black_calibration_r1 - baseline_calibration_r1;
  black_calibration_r2 = analogRead(pr2);
  black_calibration_r2 = black_calibration_r2 - baseline_calibration_r2;

  turnonBlue();
  black_calibration_b1 = analogRead(pr1);
  black_calibration_b1 = black_calibration_b1 - baseline_calibration_b1;
  black_calibration_b2 = analogRead(pr2);
  black_calibration_b2 = black_calibration_b2 - baseline_calibration_b2;
}

void turnoffLEDs() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);
}

void turnonRed() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(100);
}

void turnonBlue() {
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);
}