#include <Wire.h>
#include <SoftwareSerial.h>
#include <battleBotSetup.h>


int sensorValueLeft;
int sensorValueRight;
boolean firstTime = true;

BattleBotSetup bb;

void setup() 
{
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
  bb.adjustSpeed(4,4);
  Serial.println(bb.getLeftSpeed());
  delay(500);
  bb.adjustSpeed(6,6);
  Serial.println(bb.getLeftSpeed());
  delay(500);
}
