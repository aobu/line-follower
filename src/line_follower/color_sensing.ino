int red = 1;
int blue = 2;
int pr1 = A4;
int pr2 = A5;

void color_sensing() {
  int blue_reading1 = 0;
  int red_reading1 = 0;
  int blue_reading2 = 0;
  int red_reading2 = 0;
  
  // Read Red
  digitalWrite(blue, LOW);
  digitalWrite(red, HIGH);
  red_reading1 = analogRead(pr1);
  red_reading2 = analogRead(pr2);

  // Print Red 
  Serial.print("resistor2 red: ");
  Serial.println(red_reading1);

  delay(50);

  // Read Blue 
  digitalWrite(red, LOW);
  digitalWrite(blue, HIGH);
  
  blue_reading1 = analogRead(pr1);
  blue_reading2 = analogRead(pr2);
  // Print Blue
  Serial.print("resistor2 blue: ");
  Serial.println(blue_reading);
  delay(50);

  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);

  // Only print reading 1
  lande_decider(blue_reading1, read_reading1);
}

void color_sensor_1()

void lane_decider(int blue_reading, int red_reading) {
  if (red_reading >  5 && blue_reading > 355 && blue_reading < 395) {
    Serial.println("On Red Lane");
  } else if (red_reading > 8 && blue_reading > 395) {
    Serial.println("On Yellow Lane");
  } else if (red_reading < 5 && blue_reading < 285 && blue_reading > 260) {
    Serial.println("On Blue Lane");
  } else if (red_reading < 8 && blue_reading < 265) {
    Serial.println("On Black");
  }
}
