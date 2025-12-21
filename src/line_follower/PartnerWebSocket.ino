#include <string.h>

// Function to send values of partner 1 websocket using buttons
void sendPartner1Websocket() {
  button_check(1);
  String message = "bot starts";
  sendMessage(message);

  button_check(2);
  message = "828BD9E1B7C7.red lane found";
  sendMessage(message);

  button_check(3);
  message = "returned";
  sendMessage(message);
}

// Function to send values of partner 2 websocket using buttons
void sendPartner2Websocket() {
  button_check(1);
  String message = "828BD9E1B7C7.blue lane found"; // follows yellow
  sendMessage(message);

  button_check(2);
  message = "returned";
  sendMessage(message);
}