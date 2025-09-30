int motor1_en12_pin = 4;
int motor2_en34_pin = 8;

int motor1_in1 = 5;
int motor1_in2 = 6;
int motor2_in1 = 9;
int motor2_in2 = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);
  pinMode(motor1_en12_pin, OUTPUT);
  pinMode(motor2_en34_pin, OUTPUT);
}

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

void bot_turnRight(int turn_radius) {
  int time_run = turn_radius * 100;
  int timer = 0;
  
  while(timer != time_run) {
    analogWrite(motor1_in1, 255);
    analogWrite(motor1_in2, 0);
    // Motor 2
    analogWrite(motor2_in1, 0);
    analogWrite(motor2_in2, 127);
    timer++;
  }
}

void bot_turnLeft(int turn_radius) {
  int time_run = turn_radius * 100;
  int timer = 0;
  
  while(timer != time_run) {
    analogWrite(motor1_in1, 127);
    analogWrite(motor1_in2, 0);
    // Motor 2
    analogWrite(motor2_in1, 0);
    analogWrite(motor2_in2, 255);
    timer++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor1_en12_pin, HIGH); // turns on enable for motor 1
  digitalWrite(motor2_en34_pin, HIGH); // turns on enable for motor 2

  // Call other functions to move bot
  bot_forward(200);
  delay(2000);
  bot_stop();
  delay(2000);
  bot_backwards(200);
  delay(2000);
  bot_stop();
  delay(2000);
  bot_clockwise();
  delay(2000);
  bot_stop();
  delay(2000);
  bot_counterclockwise();
  delay(2000);
  bot_stop();
  delay(2000);
  bot_turnRight(10);
  delay(2000);
  bot_stop();
  delay(2000);
  bot_turnLeft(10);
  delay(2000);
  bot_stop();
}