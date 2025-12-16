int motor1_en12_pin = 4;
int motor2_en34_pin = 8;

int motor1_in1 = 5;
int motor1_in2 = 6;
int motor2_in1 = 9;
int motor2_in2 = 10;

void bot_stop() {
  // Motor 1 
  analogWrite(motor1_in1, 0);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 0);
}

void bot_forward(int speed) {
  // Motor 1 
  analogWrite(motor1_in1, speed);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, speed);
}

void bot_backwards(int speed) {
  // Motor 1 
  analogWrite(motor1_in2, speed);
  analogWrite(motor1_in1, 0);
  // Motor 2
  analogWrite(motor2_in1, speed);
  analogWrite(motor2_in2, 0);
}

void bot_clockwise() {
  // Motor 1 
  analogWrite(motor1_in1, 127);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 0);
}

void bot_counterclockwise() {
  // Motor 1 
  analogWrite(motor1_in1, 0);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 127);
}

void bot_turnLeft() {  
  analogWrite(motor1_in1, 50);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 30);
}

void bot_turnRight() {
  analogWrite(motor1_in1, 30);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 50);
}


void bot_lane_right() {
  bot_turnRight();
  delay(100);
  bot_forward(255);
  delay(200);
  bot_stop();
  delay(1000);
}

void bot_lane_left() {
  bot_turnLeft();
  delay(200);
  bot_forward(255);
  delay(200);
  bot_stop();
  delay(1000);
}

void bot_clockwise_90() {
  bot_clockwise();
  delay(700);
  bot_stop();
}