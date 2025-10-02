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

void bot_turnRight() {  
  analogWrite(motor1_in1, 255);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 127);
}

void bot_turnLeft() {
  analogWrite(motor1_in1, 127);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 255);
}
