#include <string.h>

// Pin definitions
int red1 = 2;
int blue1 = 11;
int red2 = 12;
int blue2 = 13;
int pr1 = A4;
int pr2 = A5;
int button = 1;
int button_press = 0;

// Global variable definitipns for color sensing
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
int avg_r1;
int avg_r2;
int avg_b1;
int avg_b2;
int tolerance = 30;

// Function to follow lane 
// lane 1 is red, lane 2 is yellow, lane 3 is blue, and lane 4 is black
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

  color_sensor(lane_number1, lane_number2, desired_lane);
}

// function to determines if the bot is on the lane given
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

// function to determine the direction the bot should move
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
    bot_forward(40);
  } else if (lane_number1 == desired_lane && lane_number2 != desired_lane) {
    bot_turnLeftLane();
  } else if (lane_number2 == desired_lane && lane_number1 != desired_lane) {
    bot_turnRightLane();
  }
}


// function that determines which lane the left sensor (sensor 1) is on
int lane_decider1(int blue_reading, int red_reading) {
  if (red_reading <= (red_calibration_r1 + tolerance) && red_reading >= (red_calibration_r1 - tolerance) && blue_reading >= (red_calibration_b1 - tolerance) && blue_reading <= (red_calibration_b1 + tolerance)) {
    Serial.println("Sensor 1 On Red Lane");
    return 1;
  } else if (red_reading <= (yellow_calibration_r1 + tolerance) && red_reading >= (yellow_calibration_r1 - tolerance) && blue_reading >= (yellow_calibration_b1 - tolerance) && blue_reading <= (yellow_calibration_b1 + tolerance)) {
    Serial.println("Sensor 1 On Yellow Lane");
    return 2;
  } else if (red_reading >= (blue_calibration_r1 - tolerance) && red_reading <= (blue_calibration_r1 + tolerance) && blue_reading <= (blue_calibration_b1 + tolerance) && blue_reading >= (blue_calibration_b1 - tolerance)) {
    Serial.println("Sensor 1 On Blue Lane");
    return 3;
  } else if (red_reading >= (black_calibration_r1 - tolerance) && red_reading <= (black_calibration_r1 + tolerance) && blue_reading <= (black_calibration_b1 + tolerance) && blue_reading >= (black_calibration_b1 - tolerance)) {
    Serial.println("Sensor 1 On Black");
    return 4;
  } else {
    return 0;
  }
}

// function that determines which lane the right sensor (sensor 2) is on
int lane_decider2(int blue_reading, int red_reading) {
  if (red_reading <= (red_calibration_r2 + tolerance) && red_reading >= (red_calibration_r2 - tolerance) && blue_reading >= (red_calibration_b2 - tolerance) && blue_reading <= (red_calibration_b2 + tolerance)) {
    Serial.println("Sensor 2 On Red Lane");
    return 1;
  } else if (red_reading <= (yellow_calibration_r2 + tolerance) && red_reading >= (yellow_calibration_r2 - tolerance) && blue_reading >= (yellow_calibration_b2 - tolerance) && blue_reading <= (yellow_calibration_b2 + tolerance)) {
    Serial.println("Sensor 2 On Yellow Lane");
    return 2;
  } else if (red_reading >= (blue_calibration_r2 - tolerance) && red_reading <= (blue_calibration_r2 + tolerance) && blue_reading <= (blue_calibration_b2 + tolerance) && blue_reading >= (blue_calibration_b2 - tolerance)) {
    Serial.println("Sensor 2 On Blue Lane");
    return 3;
  } else if (red_reading >= (black_calibration_r2 - tolerance) && red_reading <= (black_calibration_r2 + tolerance) && blue_reading <= (black_calibration_b2 + tolerance) && blue_reading >= (black_calibration_b2 - tolerance)) {
    Serial.println("Sensor 2 On Black");
    return 4;
  } else {
    return 0;
  }
}

// Function that calibrates the lanes
// Calibration order is red, yellow, blue, then black
// Press button to calibrate each lane
void color_calibration() {
  button_press = 0;
  turnoffLEDs();
  baseline_calibration_r1 = analogRead(pr1);
  baseline_calibration_b1 = analogRead(pr1);
  baseline_calibration_r2 = analogRead(pr2);
  baseline_calibration_b2 = analogRead(pr2);

  button_check(1);
  calibrate_red();

  turnoffLEDs();
  button_check(2);
  calibrate_yellow();

  turnoffLEDs();
  button_check(3);
  calibrate_blue();

  turnoffLEDs();
  button_check(4);
  calibrate_black();

  // Color adjustment to adjust for real time values
  red_calibration_r1 = red_calibration_r1 - 35;
  red_calibration_r2 = red_calibration_r2 - 45;
  red_calibration_b1 = red_calibration_b1 - 45;
  red_calibration_b2 = red_calibration_b2 - 35;

  yellow_calibration_r1 = yellow_calibration_r1 - 80;
  yellow_calibration_r2 = yellow_calibration_r2 - 60;
  yellow_calibration_b1 = yellow_calibration_b1 - 80;
  yellow_calibration_b2 = yellow_calibration_b2 - 60;

  blue_calibration_r1 = blue_calibration_r1 - 70;
  blue_calibration_r2 = blue_calibration_r2 - 53;
  blue_calibration_b1 = blue_calibration_b1 - 70;
  blue_calibration_b2 = blue_calibration_b2 - 53;

  black_calibration_r1 = black_calibration_r1 - 80;
  black_calibration_r2 = black_calibration_r2 - 60;
  black_calibration_b1 = black_calibration_b1 - 80;
  black_calibration_b2 = black_calibration_b2 - 60;
}

// Calibrate red lane
void calibrate_red() {
  turnoffLEDs();
  avg_r1 = 0;
  avg_r2 = 0;
  avg_b1 = 0;
  avg_b2 = 0;

  for (int i = 0; i < 5; i++) {
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

    avg_r1 += red_calibration_r1;
    avg_r2 += red_calibration_r2;
    avg_b1 += red_calibration_b1;
    avg_b2 += red_calibration_b2;
  }
  red_calibration_r1 = avg_r1/5;
  red_calibration_r2 = avg_r2/5;
  red_calibration_b1 = avg_b1/5;
  red_calibration_b2 = avg_b2/5;
}

// calibrate yellow lane
void calibrate_yellow() {
  turnoffLEDs();
  baseline_calibration_r1 = analogRead(pr1);
  baseline_calibration_b1 = analogRead(pr1);
  baseline_calibration_r2 = analogRead(pr2);
  baseline_calibration_b2 = analogRead(pr2);
  avg_r1 = 0;
  avg_r2 = 0;
  avg_b1 = 0;
  avg_b2 = 0;

  for (int i = 0; i < 5; i++) {
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

    avg_r1 += yellow_calibration_r1;
    avg_r2 += yellow_calibration_r2;
    avg_b1 += yellow_calibration_b1;
    avg_b2 += yellow_calibration_b2;
  }
  yellow_calibration_r1 = avg_r1/5;
  yellow_calibration_r2 = avg_r2/5;
  yellow_calibration_b1 = avg_b1/5;
  yellow_calibration_b2 = avg_b2/5;
}

// calibrate blue lane
void calibrate_blue() {
  turnoffLEDs();
  baseline_calibration_r1 = analogRead(pr1);
  baseline_calibration_b1 = analogRead(pr1);
  baseline_calibration_r2 = analogRead(pr2);
  baseline_calibration_b2 = analogRead(pr2);
  avg_r1 = 0;
  avg_r2 = 0;
  avg_b1 = 0;
  avg_b2 = 0;

  for (int i = 0; i < 5; i++){
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

    avg_r1 += blue_calibration_r1;
    avg_r2 += blue_calibration_r2;
    avg_b1 += blue_calibration_b1;
    avg_b2 += blue_calibration_b2;
  }
  blue_calibration_r1 = avg_r1/5;
  blue_calibration_r2 = avg_r2/5;
  blue_calibration_b1 = avg_b1/5;
  blue_calibration_b2 = avg_b2/5;
}

// calibrate black lane
void calibrate_black() {
  turnoffLEDs();
  baseline_calibration_r1 = analogRead(pr1);
  baseline_calibration_b1 = analogRead(pr1);
  baseline_calibration_r2 = analogRead(pr2);
  baseline_calibration_b2 = analogRead(pr2);
  avg_r1 = 0;
  avg_r2 = 0;
  avg_b1 = 0;
  avg_b2 = 0;

  for (int i = 0; i < 5; i++) {
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

    avg_r1 += black_calibration_r1;
    avg_r2 += black_calibration_r2;
    avg_b1 += black_calibration_b1;
    avg_b2 += black_calibration_b2;
  }
  black_calibration_r1 = avg_r1/5;
  black_calibration_r2 = avg_r2/5;
  black_calibration_b1 = avg_b1/5;
  black_calibration_b2 = avg_b2/5;
}

// Functions that keep color sensing standarized 

// function to turn off all LEDs
void turnoffLEDs() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(25);
}

// function to turn on red LEDs
void turnonRed() {
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(50);
}

// function to turn on blue LEDS
void turnonBlue() {
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(50);
}

// Function to check if the button is pressed 
void button_check(int desired_value) {
  Serial.print("Button press: ");
  Serial.println(button_press);
  while (button_press != desired_value) {
    int reading = digitalRead(button);

    if (prev_button_reading == HIGH && reading == LOW) {
      button_press++;      
      delay(10);       
    }
    prev_button_reading = reading;
  }
  
}
