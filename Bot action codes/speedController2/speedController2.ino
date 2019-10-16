int controlInput;
int robotSpeed;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(38400);
  BlueTooth.begin(38400);
}

void loop() 
{
  if(BlueTooth.available())
  {
    controlInput=BlueTooth.read();
    
  }
  if(controlInput != NULL)
  {
    robotSpeed = controlInput;
  }
  analogWrite(pinLeftWheelBackward, 0);
  analogWrite(pinLeftWheelForward, robotSpeed);
  analogWrite(pinRightWheelBackward, 0);
  analogWrite(pinRightWheelForward, 200);

  delay(500);
}
