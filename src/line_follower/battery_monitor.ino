// Battery monitoring pin definitions
int battery1_pin = A3; // Motor
int battery2_pin = 7; // Arduino

// battey monitoring global variables
float battery1_charge; // Battery charge of motor 
float battery2_charge; // Battery health of Arduino

// Function to show battery health of the bot
void battery_health() {
  // Read battery charge in analog
  int battery1_analog = analogRead(A1);
  int battery2_analog = analogRead(A2);
  Serial.print("battery 1 analog read: ");
  Serial.println(battery1_analog);
  Serial.print("battery 2 analog read: ");
  Serial.println(battery2_analog);

  // Convert to Voltage
  battery1_charge = (battery1_analog / 1023.0) * 4.5;
  battery2_charge = (battery2_analog / 1023.0) * 4.5;
  Serial.print("battery 1 float read: ");
  Serial.println(battery1_charge);
  Serial.print("battery 2 float read: ");
  Serial.println(battery2_charge);

  // Turn on LED if battery low
  motor_battery_LED(battery1_charge, battery1_pin);
  Arduino_battery_LED(battery2_charge, battery2_pin);
}

// Function that turn on the LED when battery charge is low
void Arduino_battery_LED(float charge, int pin) {
  if (charge < 3.7) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

// Function that turn on the LED when battery charge is low (had to be analog due to insufficient digital pins)
void motor_battery_LED(float charge, int pin) {
  if (charge < 3.7) {
    analogWrite(pin, 255);
  } else {
    analogWrite(pin, 0);
  }
}