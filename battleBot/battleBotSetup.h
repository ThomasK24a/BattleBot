#ifndef BattleBotSetup_H
#define BattleBotSetup_H


class BattleBotSetup
{
public:
    BattleBotSetup();
	
	void adjustSpeed(int leftSpeed, int rightSpeed);
	
	//will put the speed from leftSpeed and rightSpeed into the motors
	void setSpeed();
	
	//will turn the bot for the set amount of degrees and the set speed, degrees is clockwise and minus will turn it countclockwise
	void turn(int speed, int degrees);
    
	//returns the amount of degrees turned
	void getAngle();
    
	void setup();
	
	void blueToothPrint();
	
	int _pinLeftWheelBackward;
	int _pinRightWheelBackward;
	int _pinLeftWheelForward;
	int _pinRightWheelForward;
	int _pinSensorLeft;
	int _pinSensorRight;
	int _pinTrigger;
	int _pinEcho;
	
private:
    
};

#endif
