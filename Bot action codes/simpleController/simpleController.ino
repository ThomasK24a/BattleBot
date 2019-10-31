char controlInput;
int robotSpeed = 120;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;
boolean isOn = false;


void driveForward()
  {
    if(isOn)
    {
      analogWrite(pinLeftWheelBackward, 0);
      analogWrite(pinLeftWheelForward, robotSpeed);
      analogWrite(pinRightWheelBackward, 0);
      analogWrite(pinRightWheelForward, robotSpeed);
    }
    
    
  }

  void driveBackward()
  {
    if(isOn)
    {
      analogWrite(pinLeftWheelBackward, robotSpeed);
      analogWrite(pinLeftWheelForward, 0);
      analogWrite(pinRightWheelBackward, robotSpeed);
      analogWrite(pinRightWheelForward, 0);
    }
    
  }

  void stopRobot()
  {
      analogWrite(pinLeftWheelBackward, 0);
      analogWrite(pinLeftWheelForward, 0);
      analogWrite(pinRightWheelBackward, 0);
      analogWrite(pinRightWheelForward, 0);
  }

  void turnLeft()
  {
    if(isOn)
    {
      analogWrite(pinLeftWheelBackward, robotSpeed);
      analogWrite(pinLeftWheelForward, 0);
      analogWrite(pinRightWheelBackward, 0);
      analogWrite(pinRightWheelForward, robotSpeed);
    }
  }
  
  void turnRight()
  {
    if(isOn)
    {
      analogWrite(pinLeftWheelBackward, 0);
      analogWrite(pinLeftWheelForward, robotSpeed);
      analogWrite(pinRightWheelBackward, robotSpeed);
      analogWrite(pinRightWheelForward, 0);
    }
  }

  

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(38400);
  BlueTooth.begin(38400);
  
  Serial.begin (9600);
}

void loop() 
{
  if(BlueTooth.available())
  {
    controlInput=BlueTooth.read();
    
  }

  switch(controlInput)
  {
    case 'q':
      isOn ^= true;
      if(isOn)
      {
        BlueTooth.println("Bot is on");
        controlInput = NULL;
      }
      else
      {
        BlueTooth.println("Bot is off");
        stopRobot();
        controlInput = NULL;
      }
      break;
    case 'w':
      driveForward();
      BlueTooth.println("Going forward");
      break;
    case 'a':
      turnLeft();
      break;
    case 's':
      driveBackward();
      BlueTooth.println("Going backwards");
      break;
    case 'd':
      turnRight();
      break;
    case 'e':
      robotSpeed = 120;
      break;
    case 'f': 
      robotSpeed = 140;
      break;
  }  
}
