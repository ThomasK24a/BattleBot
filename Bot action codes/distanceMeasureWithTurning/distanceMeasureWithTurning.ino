char controlInput;
int robotSpeed;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;
boolean isOn = false;

#define trigPin 13
#define echoPin 12

int duration;
int distance;
  

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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
//  if(controlInput == 'q')
//  {
//    //switches the isOn state from true to false or from false to true
//    isOn ^= true;
//    if(isOn)
//    {
//      BlueTooth.println("Bot is on");
//    }
//    else
//    {
//      BlueTooth.println("Bot is off");
//      stopRobot();
//    }
//  }
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = (duration/2) / 29.1;
//
//  if (distance >= 200 || distance <= 0)
//  {
//    BlueTooth.println("Out of range \r\n");
//    //BlueTooth.println(distance);
//    //BlueTooth.println(" cm \r\n");
//  }
//  else
//  {
//    BlueTooth.println(distance);
//    BlueTooth.println(" cm \r\n");
//  }
//
//  if (distance >= 25)
//  {
//    driveForward();
//  }
//  else
//  {
//    turnLeft();
//  }
  
  delay(100);
}
