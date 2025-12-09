int red1 = 11;
int blue1 = 2;
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
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  baseline1 = analogRead(pr1);
  baseline2 = analogRead(pr2);
  delay(10);

  // Read Red
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  red_reading1 = analogRead(pr1);
  red_reading2 = analogRead(pr2);

  // Read Blue 
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  delay(10);
  
  blue_reading1 = analogRead(pr1);
  blue_reading2 = analogRead(pr2);

  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);

  // Only print reading 1
  blue_1 = blue_reading1 - baseline1;
  red_1 = red_reading1 - baseline1;
  blue_2 = blue_reading2 - baseline2;
  red_2 = red_reading2 - baseline2;
  int lane_number1 = lane_decider1(blue_1, red_1);
  int lane_number2 = lane_decider2(blue_2, red_2);

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
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  baseline1 = analogRead(pr1);
  baseline2 = analogRead(pr2);
  delay(10);

  // Read Red
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  red_reading1 = analogRead(pr1);
  red_reading2 = analogRead(pr2);

  // Read Blue 
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  delay(10);
  
  blue_reading1 = analogRead(pr1);
  blue_reading2 = analogRead(pr2);

  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);

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
  if(lane_number1 == 0 &&
   lane_number2 == 0) {
    bot_stop();
    return;
  }

  if (lane_number1 == desired_lane && lane_number1 == lane_number2) {
    bot_forward(255);
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
  calibrate_red();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(4000);
  calibrate_yellow();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(4000);
  calibrate_blue();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(4000);
  calibrate_black();
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(5000);
  Serial.print("Red Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(red_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(red_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(red_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(red_calibration_b2);

  Serial.print("Blue Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(blue_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(blue_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(blue_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(blue_calibration_b2);

  Serial.print("Yellow Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(yellow_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(yellow_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(yellow_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(yellow_calibration_b2);

  Serial.print("Black Color Calibration Value: \n");
  Serial.print("  Red LED 1: ");
  Serial.println(black_calibration_r1);
  Serial.print("  Red LED 2: ");
  Serial.println(black_calibration_r2);
  Serial.print("  Blue LED 1: ");
  Serial.println(black_calibration_b1);
  Serial.print("  Blue LED 2: ");
  Serial.println(black_calibration_b2);
}

void calibrate_red() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);

  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  red_calibration_r1 = analogRead(pr1);
  red_calibration_r2 = analogRead(pr2);

  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(10);
  red_calibration_b1 = analogRead(pr1);
  red_calibration_b2 = analogRead(pr2);
}

void calibrate_yellow() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);

  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  yellow_calibration_r1 = analogRead(pr1);
  yellow_calibration_r2 = analogRead(pr2);

  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(10);
  yellow_calibration_b1 = analogRead(pr1);
  yellow_calibration_b2 = analogRead(pr2);
}

void calibrate_blue() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);

  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  blue_calibration_r1 = analogRead(pr1);
  blue_calibration_r2 = analogRead(pr2);

  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(10);
  blue_calibration_b1 = analogRead(pr1);
  blue_calibration_b2 = analogRead(pr2);
}

void calibrate_black() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);

  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(10);
  black_calibration_r1 = analogRead(pr1);
  black_calibration_r2 = analogRead(pr2);

  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(10);
  black_calibration_b1 = analogRead(pr1);
  black_calibration_b2 = analogRead(pr2);
}