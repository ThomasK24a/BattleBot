int controlInput;
int leftSpeed;
int rightSpeed = 100;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;
int isOn = 0;

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
    leftSpeed = controlInput;
  }

  if(controlInput == 0)
  {
    rightSpeed = 0;
  }
  else
  {
    rightSpeed = 100;
  }
  
  analogWrite(pinLeftWheelBackward, 0);
  analogWrite(pinLeftWheelForward, leftSpeed);
  analogWrite(pinRightWheelBackward, 0);
  analogWrite(pinRightWheelForward, rightSpeed);
//  BlueTooth.println("left wheel: ");
//  BlueTooth.println(leftSpeed);
//  BlueTooth.println(" right wheel: ");
//  BlueTooth.println(rightSpeed);
  BlueTooth.println(controlInput);
  delay(500);
}
