#ifndef BattleBotSetup_H
#define BattleBotSetup_H


class BattleBotSetup
{
	public:
		BattleBotSetup();
		
		void adjustSpeed(int leftSpeed, int rightSpeed);
		
		//will put the speed from leftSpeed and rightSpeed into the motors
		void setSpeed();
		
		int getLeftSpeed();
		int getRightSpeed();


	private:
		int _pinLeftWheelBackward;
		int _pinRightWheelBackward;
		int _pinLeftWheelForward;
		int _pinRightWheelForward;
};

#endif
