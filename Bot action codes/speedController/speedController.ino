char controlInput;
int speed;
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
      speed = 255;
      break;
    case 'w':
      speed = 100;
      break;
    case 'e':
      speed = 0;
      break;
    
  }
  analogWrite(pinLeftWheelBackward, 0);
  analogWrite(pinLeftWheelForward, speed);
  analogWrite(pinRightWheelBackward, 0);
  analogWrite(pinRightWheelForward, speed);

  delay(500);
}
