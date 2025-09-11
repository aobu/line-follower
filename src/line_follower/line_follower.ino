int motor1_en12_pin;
int motor2_en34_pin;

int motor1_in1 = 3;
int motor1_in2 = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_in1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(motor1_in1_pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  analogWrite(motor1_in1, 127);
  analogWrite(motor1_in2, 0);
  delay(5000);
  analogWrite(motor1_in2, 127);
  analogWrite(motor1_in1, 0);
  delay(5000);
  // delay(10);                      // wait for a second
  // digitalWrite(motor1_in1_pin, LOW);   // turn the LED off by making the voltage LOW
  // delay(1);
}
