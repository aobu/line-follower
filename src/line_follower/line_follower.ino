#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <string.h>

// Pin Definitions
const int BUTTON_PIN = 0;
const int LED_PIN = LED_BUILTIN;
int signal_LED = 0;

// Wifi and Websocket
char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";
char serverAddress[] = "35.239.140.61"; //"10.5.15.226"; 
int port = 8080; //8765; // Updated to match your Python server

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
String clientID = "F79721857DC5"; // "828BD9E1B7C7"; 
unsigned long lastWSRetry = 0;
const unsigned long wsRetryInterval = 3000; // ms

int partner_state = 0;
int prev_button_reading = HIGH;

// Function to make sure Wifi is Connected
bool ensureWiFi() {
  if (WiFi.status() == WL_CONNECTED) return true;

  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
     delay(500);
     Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected.");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("\nWiFi Failed.");
    return false;
  }
}

// Function to make sure websocket is connected
void ensureWebSocket() {
  if (client.connected()) return;

  unsigned long now = millis();
  if (now - lastWSRetry < wsRetryInterval) return;
  lastWSRetry = now;

  Serial.println("Attempting WebSocket connect...");
  client.begin();
  client.beginMessage(TYPE_TEXT);
  client.print(clientID);
  client.endMessage();
}


// Send client ID to websocket to activate
void handleWebSocketMessages() {
  static bool sentID = false; 

  if (client.connected() && !sentID) {
      String message = "CLIENTID:" + clientID;
      sendMessage(message);
      sentID = true;
      Serial.println("ID sent");
    } 

  String raw;

  String message;

  if(client.connected()){
    int msgSize = client.parseMessage();
    if (msgSize <= 0) return;
    raw = client.readString();
    raw.trim();
    
    Serial.print("RX: ");
    Serial.println(raw);
    int period = raw.indexOf('.');
    String parse_client = raw.substring(0,period);
    Serial.println("client: " + parse_client);
    String parse_data = raw.substring(period + 1);
    if (parse_data.startsWith(clientID)){
      int period1 = parse_data.indexOf('.');
      String data = parse_data.substring(period1 + 1);
      handle_message(data);
    }
  }
}

// Handle messages for instructions
void handle_message(String data){
  if (data == "bot start") {
    messageLED();
    Serial.print("start");
    partner_state = 1;
  } else if(data == "red lane found"){
    Serial.print("red");
    messageLED();
    partner_state = 2;
  }else if(data == "blue lane found"){
    Serial.print("blue");
    messageLED();
    partner_state = 1;
  }else if(data == "returned"){
    Serial.print("return");
    messageLED();
    partner_state = 3;
  }else{
    Serial.print("Message not recognized");
  }
}

// Function to send messages to the websocket
void sendMessage(String message) {

  if (client.connected()) {
    client.beginMessage(TYPE_TEXT); 
    client.print(message);
    client.endMessage(); 
    Serial.println("Sent message to WebSocket server.");
  }
  // messageLED();
}

// Function to show external signal for websocket communication
void messageLED() {
  digitalWrite(signal_LED, HIGH);
  delay(500);
  digitalWrite(signal_LED, LOW);
}