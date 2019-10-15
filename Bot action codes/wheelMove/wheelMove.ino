#include <ArduinoRobot.h>
#include <Wire.h>

void setup(){
  Robot.begin();
}
void loop(){
  Robot.motorsWrite(50,50); //Make the robot go forward, full speed

  
}
