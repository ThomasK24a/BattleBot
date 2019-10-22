#include <battleBotSetup.h>

int sensorValueLeft;
int sensorValueRight;
boolean firstTime = true;

BattleBotSetup bb;

//#include <SoftwareSerial.h>
//SoftwareSerial BlueTooth(A0, A1);

void setup() 
{
  //BlueTooth.begin(38400);
  // put your setup code here, to run once:
  Serial.begin(9600); //sets serial port for communication
}

void loop() 
{
  
//  sensorValueLeft = digitalRead(bb._pinSensorLeft); // read the value from the sensor
//  sensorValueRight = digitalRead(bb._pinSensorRight); // read the value from the sensor
//  Serial.println(sensorValueLeft);
//  Serial.println(sensorValueRight);
//
//  if(sensorValueLeft && sensorValueLeft)
//  {
//    
//  }
//  else if(sensorValueLeft)
//  {
//    //go left
//    bb.turn(4, 15);
//  }
//  else if(sensorValueRight)
//  {
//    //go right
//    bb.turn(4, -15);
//  }
//  else
//  {
//    //go straight
//    bb.adjustSpeed(4,4);
//    
//
//  }
//  delay(50);
//  bb.adjustSpeed(5,5);
//  if(firstTime)
//  {
//    bb.turn(4,15);
//    firstTime = false;
//  }
  
  bb.blueToothPrint();
  
}
