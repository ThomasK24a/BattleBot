char controlInput;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;

void driveForward()
  {
    digitalWrite(pinLeftWheelBackward, LOW);
    digitalWrite(pinLeftWheelForward, HIGH);
    digitalWrite(pinRightWheelBackward, LOW);
    digitalWrite(pinRightWheelForward, HIGH);
    
  }

  void driveBackward()
  {
    digitalWrite(pinLeftWheelBackward, HIGH);
    digitalWrite(pinLeftWheelForward, LOW);
    digitalWrite(pinRightWheelBackward, HIGH);
    digitalWrite(pinRightWheelForward, LOW);
    
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
    digitalWrite(pinLeftWheelBackward, HIGH);
    digitalWrite(pinLeftWheelForward, LOW);
    digitalWrite(pinRightWheelBackward, LOW);
    digitalWrite(pinRightWheelForward, HIGH);
  }
  
  void turnRight()
  {
    digitalWrite(pinLeftWheelBackward, LOW);
    digitalWrite(pinLeftWheelForward, HIGH);
    digitalWrite(pinRightWheelBackward, HIGH);
    digitalWrite(pinRightWheelForward, LOW);
  }

void setup() 
{
  // put your setup code here, to run once:
  pinMode(pinLeftWheelForward, OUTPUT);
  Serial.begin(38400);
  BlueTooth.begin(38400);

  
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

  
  delay(100);
}
