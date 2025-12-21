// Bot motion pin definitions
int motor1_en12_pin = 4;
int motor2_en34_pin = 8;
int motor1_in1 = 5;
int motor1_in2 = 6;
int motor2_in1 = 9;
int motor2_in2 = 10;

// Function to stop bot
void bot_stop() {
  // Motor 1 
  analogWrite(motor1_in1, 0);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 0);
}

// Function to move bot forward at set speed
void bot_forward(int speed) {
  // Motor 1 
  analogWrite(motor1_in1, speed);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, speed + 8);
}

// Function to move bot backwards at set speed
void bot_backwards(int speed) {
  // Motor 1 
  analogWrite(motor1_in2, speed);
  analogWrite(motor1_in1, 0);
  // Motor 2
  analogWrite(motor2_in1, speed + 8);
  analogWrite(motor2_in2, 0);
}

// Function to move bot counter-clockwise
void bot_counterclockwise() {
  // Motor 1 
  analogWrite(motor1_in1, 120);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 0);
}

// Function to move bot clockwise
void bot_clockwise() {
  // Motor 1 
  analogWrite(motor1_in1, 0);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 127);
}

// Function to turn bot left
void bot_turnLeft() {  
  analogWrite(motor1_in1, 65);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 30);
}

// Function to turn bot right
void bot_turnRight() {
  analogWrite(motor1_in1, 35);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 50);
}

// Function to move left while lane following
void bot_turnLeftLane() {  
  analogWrite(motor1_in1, 55);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 30);
}

// Function to move right while lane following
void bot_turnRightLane() {
  analogWrite(motor1_in1, 35);
  analogWrite(motor1_in2, 0);
  // Motor 2
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 55);
}