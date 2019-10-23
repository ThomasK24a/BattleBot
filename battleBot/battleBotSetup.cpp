#include "Arduino.h"
#include "BattleBotSetup.h"

//Set all the pins
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;

//For setting the speed of the motors
int leftSpeed;
int rightSpeed;
int leftSpeedInput;
int rightSpeedInput;

BattleBotSetup::BattleBotSetup()
{
	_pinLeftWheelBackward = pinLeftWheelBackward;
	_pinRightWheelBackward = pinRightWheelBackward;
	_pinLeftWheelForward = pinLeftWheelForward;
	_pinRightWheelForward = pinRightWheelForward;   
}


void BattleBotSetup::adjustSpeed(int newLeftSpeed, int newRightSpeed)
{
	leftSpeed = newLeftSpeed;
	rightSpeed = newRightSpeed;
	setSpeed();
}


//will put the speed from leftSpeed and rightSpeed into the motors
void BattleBotSetup::setSpeed()
{
  if (leftSpeed >= 0)
  {
    leftSpeedInput = leftSpeed * 10;
    analogWrite(pinLeftWheelBackward, 0);
    analogWrite(pinLeftWheelForward, leftSpeedInput);
  }
  else
  {
    leftSpeedInput = 255;
    analogWrite(pinLeftWheelBackward, leftSpeedInput);
    analogWrite(pinLeftWheelForward, 0);
  }

  if (rightSpeed >= 0)
  {
    rightSpeedInput = rightSpeed * 25;
    analogWrite(pinRightWheelBackward, 0);
    analogWrite(pinRightWheelForward, rightSpeedInput);
  }
  else
  {
    rightSpeedInput = 255;
    analogWrite(pinRightWheelBackward, rightSpeedInput);
    analogWrite(pinRightWheelForward, 0);
  }
}

int BattleBotSetup::getLeftSpeed()
{
	return leftSpeed;
}

int BattleBotSetup::getRightSpeed()
{
	return rightSpeed;
}