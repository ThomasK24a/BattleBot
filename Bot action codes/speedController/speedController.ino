char controlInput;
int forwardSpeed;
int backwardSpeed;
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
  switch(controlInput)
  {
    case 'q':
      forwardSpeed = 255;
      backwardSpeed = 0;
      break;
    case 'w':
      forwardSpeed = 100;
      backwardSpeed = 0;
      break;
    case 'e':
      forwardSpeed = 0;
      backwardSpeed = 0;
      break;
    case 'a':
      forwardSpeed = 0;
      backwardSpeed = 255;
      break;
    case 's':
      forwardSpeed = 0;
      backwardSpeed = 100;
      break;    
  }
  analogWrite(pinLeftWheelBackward, backwardSpeed);
  analogWrite(pinLeftWheelForward, forwardSpeed);
  analogWrite(pinRightWheelBackward, backwardSpeed);
  analogWrite(pinRightWheelForward, forwardSpeed);

  delay(500);
}
