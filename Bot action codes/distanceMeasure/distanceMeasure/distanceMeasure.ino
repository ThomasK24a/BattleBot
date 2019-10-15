char controlInput;
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
      digitalWrite(pinLeftWheelBackward, LOW);
      digitalWrite(pinLeftWheelForward, HIGH);
      digitalWrite(pinRightWheelBackward, LOW);
      digitalWrite(pinRightWheelForward, HIGH);
    }
    
    
  }

  void driveBackward()
  {
    if(isOn)
    {
      digitalWrite(pinLeftWheelBackward, HIGH);
      digitalWrite(pinLeftWheelForward, LOW);
      digitalWrite(pinRightWheelBackward, HIGH);
      digitalWrite(pinRightWheelForward, LOW);
    }
    
  }

  void stopRobot()
  {
    digitalWrite(pinLeftWheelBackward, LOW);
    digitalWrite(pinLeftWheelForward, LOW);
    digitalWrite(pinRightWheelBackward, LOW);
    digitalWrite(pinRightWheelForward, LOW);
  }

  void turnLeft()
  {
    if(isOn)
    {
      digitalWrite(pinLeftWheelBackward, LOW);
      digitalWrite(pinLeftWheelForward, HIGH);
      digitalWrite(pinRightWheelBackward, HIGH);
      digitalWrite(pinRightWheelForward, LOW);
    }
  }
  
  void turnRight()
  {
    if(isOn)
    {
      digitalWrite(pinLeftWheelBackward, HIGH);
      digitalWrite(pinLeftWheelForward, LOW);
      digitalWrite(pinRightWheelBackward, HIGH);
      digitalWrite(pinRightWheelForward, LOW);
    }
  }

  void turnRight()
  {
    if(isOn)
    {
      digitalWrite(pinLeftWheelBackward, HIGH);
      digitalWrite(pinLeftWheelForward, HIGH);
      digitalWrite(pinRightWheelBackward, HIGH);
      digitalWrite(pinRightWheelForward, HIGH);
    }
  }

void setup() 
{
  // put your setup code here, to run once:
  pinMode(pinLeftWheelForward, OUTPUT);
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
  if(controlInput == 'w')
  {
      
      //drive forward
      driveForward();
      
  }
  else if(controlInput == 's')
  {
      driveBackward();
  }
  else if(controlInput == 'e')
  {
    stopRobot();
    
  }
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 200 || distance <= 0)
  {
    BlueTooth.println("Out of range \r\n");
    //BlueTooth.println(distance);
    //BlueTooth.println(" cm \r\n");
  }
  else
  {
    BlueTooth.println(distance);
    BlueTooth.println(" cm \r\n");
  }

  if (distance >= 25)
  {
    driveForward();
  }
  else
  {
    turnLeft();
  }
  
  delay(100);
}
