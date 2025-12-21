# line-follower
2025 Junior Design Robot
Created by Brian Liau, Patrick Johnson, and Alexis Obu

Source code in src/line_follower/

The algorithms detect walls and follow the different colored lanes as according to the Junior Design Spec, either as a Solo robot, or with a partner robot with communication over websocket.

main.ino:
  - Contains the setup() which initializes the motors, color sensor, websocket, and collision detector
  - Contains the loop() where we must pick what algorithm to run:
      run_solo() - Solo demo algorithm
      run_partner_bot1() - Partner bot demo algorithm as "bot 1"
      run_partner_bot2() - Partner bot demo algortihm as "bot 2"

color_sensing.ino:
  - Color detecting and lane following code
  - Detects red, blue, and yellow lanes, as well as black
  - Includes a calibration sequence that is run at the start of the algorithms which calibrate the robot to the different colors on the track and account for ambient light

line_follower.ino
  - Contains all of the websocket functionality for sending and receiving messages

PartnerWebSocket.ino
  - Contains two functions: sendPartner1Websocket() and sendPartner2Websocket() which are used specifically for the partner bot demos

state_machine.ino
  - Defines the 3 algorithms run_solo(), run_partner_bot1(), and run_partner_bot2(), each with their own set of states
  - Within an algorithm, the bot progresses through the states when certain conditions are met or code is run. For example, in run_solo the bot progresses from state 1 to 2 when it detects the
    red lane

bot_motions.ino:
  - Contains all of the bot movement functions (ie. bot_forward(), bot_backwards(), bot_stop(), etc.)
  - Some functions allow for speed to be controlled
    
ir_led.ino:
  - Reads the IR Transistor value and determines whether the bot has detected a wall, if so it increment's the robot's state
  - Takes into account ambient IR light

battery_monitor.ino:
  - Check's the Arduno and Motor's 9V batteries for their voltage level and turns a Red LED on if they go below 3.7V


  

    
