#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <string.h>

// PINES/STATE ===========================================================
const int BUTTON_PIN = 0;
const int LED_PIN = LED_BUILTIN;

int prev_button_reading = HIGH;

// WIFI/WEBSOCKET ========================================================
char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";

// IMPORTANT: Replace this with your computer's local IP address (e.g., 192.168.1.15)
// Do not use "localhost" here.
char serverAddress[] = "10.5.15.226"; 
int port = 8765; // Updated to match your Python server

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);

String clientID = "828BD9E1B7C7"; 
unsigned long lastWSRetry = 0;
const unsigned long wsRetryInterval = 3000; // ms

// BOT-MOTIONS STATE MACHINE =================================================
enum MotionState : uint8_t {
  STOP = 1,
  FORWARD  = 2,
  BACKWARD = 3,
  CLOCKWISE = 4,
  COUNTERCLOCKWISE = 5,
  ARC_RIGHT = 6,
  ARC_LEFT  = 7
};

MotionState state = STOP;  

const uint8_t SPEED_FAST = 200;   // 0..255
const uint8_t SPEED_SLOW = 120;   // 0..255
const unsigned long TURN_MS = 900; // ms; arc duration for states 6/7

// time current state
unsigned long stateStartMs = 0;


void runStateMachine() {
  unsigned long now = millis();
  switch (state) {
    case STOP: bot_stop(); break;
    case FORWARD: bot_forward(SPEED_FAST); break;
    case BACKWARD: bot_backwards(SPEED_FAST); break;
    case CLOCKWISE: bot_clockwise(); break;
    case COUNTERCLOCKWISE: bot_counterclockwise(); break;
    case ARC_RIGHT: 
      bot_turnRight();
      if (now - stateStartMs >= TURN_MS) setState(STOP);
      break;
    case ARC_LEFT: 
      bot_turnLeft();
      if (now - stateStartMs >= TURN_MS) setState(STOP);
      break;
  }
}

// HELPERS ===============================================================
void flashLED(int times, int onMs = 120, int offMs = 120) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(onMs);
    digitalWrite(LED_PIN, LOW);
    delay(offMs);
  }
}

void setState(int newState) {
  if (newState < 1) newState = 1;
  if (newState > 7) newState = 7;
  
  state = static_cast<MotionState>(newState);
  stateStartMs = millis();
  
  Serial.print("State Changed to: ");
  Serial.println(newState);

  // WRITE TO WEBSOCKET SERVER
  // We send the state number to the server every time it changes
  if (client.connected()) {
    client.beginMessage(TYPE_TEXT);
    client.print(newState);
    client.endMessage();
  }
}

void bumpState() {
  int next = (static_cast<int>(state) % 7) + 1; // 1..7 wrap
  setState(next);
}

bool ensureWiFi() {
  if (WiFi.status() == WL_CONNECTED) return true;

  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  // Simple timeout loop
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

bool ensureWebSocket() {
  if (client.connected()) return true;

  unsigned long now = millis();
  if (now - lastWSRetry < wsRetryInterval) return false;
  lastWSRetry = now;

  Serial.print("Connecting to WebSocket at ");
  Serial.print(serverAddress);
  Serial.print(":");
  Serial.println(port);
  
  client.begin();

  if (client.connected()) {
    flashLED(2, 60, 60);
    Serial.println("WebSocket connected.");
    
    // Send initial greeting
    client.beginMessage(TYPE_TEXT);
    client.print("ARDUINO_CONNECTED");
    client.endMessage();
    return true;
  } else {
    Serial.println("WebSocket connect failed.");
    return false;
  }
}

// SERVER COMMANDS ===================================================
void handleWebSocketMessages() {
  int msgSize = client.parseMessage();
  if (msgSize <= 0) return;

  String raw = client.readString();
  raw.trim();
  
  Serial.print("RX: ");
  Serial.println(raw);

  // 1. Filter out the Echo from the server
  // Since the server sends back "Echo: 1", we don't want to parse that as an error
  if (raw.startsWith("Echo:")) {
    return; // Ignore echoes
  }

  // 2. Clean up message
  if (raw.startsWith(String("WebClient_"))) {
    // Remove prefix if you have one, logic depends on your specific protocol
    // For now we just look for numbers
  }
  
  // Remove leading dots if present
  if (raw.length() > 0 && raw[0] == '.') {
    raw.remove(0, 1); 
  }

  // 3. Parse Number
  bool allDigits = true;
  if (raw.length() == 0) allDigits = false;
  
  for (int i = 0; i < raw.length(); i++) {
    if (!isDigit(raw[i])) {
      allDigits = false;
      break;
    }
  }

  if (allDigits) {
    int n = raw.toInt();
    // Only update state if it's a valid movement command
    if (n >= 1 && n <= 7) {
      // We call setState, which will SEND the message back to the server.
      // This creates a loop if we aren't careful, but since we filter 
      // "Echo:" at the top, it should be fine.
      setState(n);
      return;
    }
  }

  // Debugging info (optional to send back to server)
  // client.beginMessage(TYPE_TEXT);
  // client.print("ERR: ");
  // client.print(raw);
  // client.endMessage();
}

// BUTTON HANDLING  ======================================================
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (prev_button_reading == HIGH && reading == LOW) {
    bumpState();      
    delay(150);       
  }
  prev_button_reading = reading;
}

void readWebSocket() {
  int msgSize = client.parseMessage();
  if (msgSize <= 0) return;

  String m = client.readString();

  Serial.print("WS message: ");
  Serial.println(m);
}

void sendMessage(String message) {
  if (client.connected()) {
    client.beginMessage(TYPE_TEXT); 
    client.print(message);
    client.endMessage(); 
    Serial.println("Sent message to WebSocket server.");
  }
}