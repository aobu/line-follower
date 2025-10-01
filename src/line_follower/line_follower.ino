int motor1_en12_pin;
int motor2_en34_pin;

int motor1_in1 = 3;
int motor1_in2 = 5;

const int BUTTON_PIN = 2;
int state = 1;
int prev_button_reading = HIGH;
int reading = HIGH;

#include <ArduinoHttpClient.h>
#include <WiFi.h>

/////// WiFi Settings ///////
char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";

char serverAddress[] = "34.28.153.91";  // server address
int port = 80;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
String clientID = "YOUR_ID_HERE";
int status = WL_IDLE_STATUS;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  // pinMode(motor1_in1, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {

  // start Websocket Client
  Serial.println("starting WebSocket client");
  client.begin();
  client.beginMessage(TYPE_TEXT);
  client.print(clientID);
  client.endMessage();

  while (client.connected()) {
    // what do you want to do while connected to the client?
  }

  Serial.println("disconnected");

  reading = digitalRead(BUTTON_PIN);

  if (prev_button_reading == HIGH && reading == LOW) { // if its resting and the reading changes then increment the state:
    state++;
    state = state % 7;

    // flash led stat times
    for (int i = 1; i < state + 1; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
    delay(500); // wait a little between presses
  }
  prev_button_reading = reading;

  // put your main code here, to run repeatedly:
  //digitalWrite(motor1_in1_pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  // analogWrite(motor1_in1, 127);
  // analogWrite(motor1_in2, 0);
  // delay(5000);
  // analogWrite(motor1_in2, 127);
  // analogWrite(motor1_in1, 0);
  // delay(5000);
  // delay(10);                      // wait for a second
  // digitalWrite(motor1_in1_pin, LOW);   // turn the LED off by making the voltage LOW
  // delay(1);
}
