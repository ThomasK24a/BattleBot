#ifndef BattleBotTurn_H
#define BattleBotTurn_H


class BattleBotTurn
{
public:
    BattleBotTurn();
	
	//will put the speed from leftSpeed and rightSpeed into the motors
	void setSpeed();
	
	//will turn the bot for the set amount of degrees and the set speed, degrees is clockwise and minus will turn it countclockwise
	void turn(int speed, int degrees);
    
	//returns the amount of degrees turned
	void getAngle();
    
	void setup();
	
private:
    
};

#endif
