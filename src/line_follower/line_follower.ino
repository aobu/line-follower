#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <string.h>

// PINES/STATE ===========================================================
const int BUTTON_PIN = 2;
const int LED_PIN = LED_BUILTIN;

//int state = 1;                 // valid range: 1..7
int prev_button_reading = HIGH;

// WIFI/WEBSOCKET ========================================================
char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";

char serverAddress[] = "34.28.153.91";
int port = 80;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);

String clientID = "828BD9E1B7C7"; // ON CANVAS
int wifiStatus = WL_IDLE_STATUS;
unsigned long lastWSRetry = 0;
const unsigned long wsRetryInterval = 3000; // ms

// BOT-MOPTIONS STATE MACHINE =================================================
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
    case STOP:
      bot_stop();
      break;

    case FORWARD:
      bot_forward(SPEED_FAST);
      break;

    case BACKWARD:
      bot_backwards(SPEED_FAST);
      break;

    case CLOCKWISE:
      bot_clockwise();
      break;

    case COUNTERCLOCKWISE:
      bot_counterclockwise();
      break;

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
}

void bumpState() {
  int next = (static_cast<int>(state) % 7) + 1; // 1..7 wrap
  setState(next);
}

bool ensureWiFi() {
  if (WiFi.status() == WL_CONNECTED) return true;

  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    unsigned long start = millis();
    while (millis() - start < 2500) {
      delay(10);
      if (WiFi.status() == WL_CONNECTED) break;
    }
  }

  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());
  return true;
}

bool ensureWebSocket() {
  if (client.connected()) return true;

  unsigned long now = millis();
  if (now - lastWSRetry < wsRetryInterval) return false;
  lastWSRetry = now;

  Serial.println("Opening WebSocket...");
  client.begin();

  // identify this client
  client.beginMessage(TYPE_TEXT);
  client.print(clientID);
  client.endMessage();

  if (client.connected()) {
    flashLED(2, 60, 60);
    Serial.println("WebSocket connected.");
    return true;
  } else {
    Serial.println("WebSocket connect failed.");
    return false;
  }
}

// SERVER COMMANDS: ONLY ACCEPT SPECIFIC 1..7 ======================
void handleWebSocketMessages() {
  int msgSize = client.parseMessage();
  if (msgSize <= 0) return;

  String raw = client.readString();
  raw.trim();
  if (raw.startsWith(String("WebClient_828BD9E1B7C7"))) {
    raw.remove(0, String("WebClient_828BD9E1B7C7").length());
  }

  if (raw.length() > 0 && raw[0] == '.') {
    raw.remove(0, 1); // remove .
  }

  bool allDigits = true;
  for (int i = 0; i < raw.len gth(); i++) {
    if (!isDigit(raw[i])) {
      allDigits = false;
      break;
    }
  }

  if (allDigits) {
    int n = raw.toInt();
    if (n >= 1 && n <= 7) {
      setState(n);
      return;
    }
  }

  // Reject everything else
  client.beginMessage(TYPE_TEXT);
  client.print("ERR expected a number 1-7, got: ");
  client.print(raw);
  client.endMessage();
}

// BUTTON HANDLING  ======================================================
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (prev_button_reading == HIGH && reading == LOW) {
    bumpState();      // only physical button increments
    delay(150);       // simple debounce
  }
  prev_button_reading = reading;
}

