#include <Wire.h>
#include <SoftwareSerial.h>
#include <battleBotSetup.h>

SoftwareSerial BlueTooth(A0, A1);
BattleBotSetup bb;

int sensorValueLeft;
int sensorValueRight;

int pinSensorLeft = 10;
int pinSensorRight = 11;
int pinTrigger = 13;
int pinEcho = 12;

char controlInput;
String currentChallenge = "Maze";
int robotSpeed = 7;

//Used by turning
unsigned long previousTime = 0;
unsigned long currentTime;
float degreesTurnedTotal = 0.0;
float degreesTurned = 0;

//Used by the gyroscope
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void turn(int speed, int degrees)
{
  bb.adjustSpeed(0,0);
  delay(100);
  BlueTooth.println("Degrees about to turn: ");
  BlueTooth.println(degrees);
  degreesTurnedTotal = 0;
  degreesTurned = 0;
  //decides whether it has to turn clockwise or counterclockwise
  if (degrees > 0)
  {
  bb.adjustSpeed(speed,0);
    degrees = -degrees;
    //will keep turning until degreesTurnedTotal is higher than the amount of degrees it has to turn
    while (degreesTurnedTotal > degrees)
    {
      currentTime = millis();
      //will add to amount of degrees measured from the getAngle method to degreesTurnedTotal in a set interval
      if ((currentTime - previousTime) > 50)
      {
        degreesTurnedTotal += degreesTurned;
        previousTime = currentTime;
      }
      getAngle();

      BlueTooth.println("Degrees turned: ");
      BlueTooth.println(degreesTurnedTotal);

      delay(10);

    }
  }
  else
  {
    //same as above but counterclockwise
    bb.adjustSpeed(0,speed);
    degrees = -degrees;
    while (degreesTurnedTotal < degrees)
    {
      currentTime = millis();
      
      if ((currentTime - previousTime) > 50)
      {
        degreesTurnedTotal += degreesTurned;
        previousTime = currentTime;
      }
      
      getAngle();
      BlueTooth.println("Degrees turned: ");
      BlueTooth.println(degreesTurnedTotal);
      delay(10);

    }
  }
  BlueTooth.println("Finished turning");
  bb.adjustSpeed(0,0);
  delay(500);

}

void getAngle()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers

  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //gets the amount of degrees turned
  degreesTurned = GyZ / 1800;
}



void setup() 
{
  Serial.begin(9600); //sets serial port for communication
  BlueTooth.begin(38400);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() 
{
  if(BlueTooth.available())
  {
    controlInput=BlueTooth.read();
    
  }

  while(currentChallenge == "none")
  {

    if(BlueTooth.available())
    {
      controlInput=BlueTooth.read();    
    }
    
    switch(controlInput)
    {
      case 'y':
        currentChallenge = "Navigate";
        BlueTooth.println("Challenge changed to navigate to next challenge");
        break;
      case 'u':
        currentChallenge = "Tape";
        BlueTooth.println("Challenge changed to follow the tape");
        break;
      case 'i':
        currentChallenge = "Maze";
        BlueTooth.println("Challenge changed to navigate out the maze");
        break;
      case 'o':
        currentChallenge = "Balloon";
        BlueTooth.println("Challenge changed to pop the balloon");
        break;
    }
    BlueTooth.println("Currently no challenge selected");
    delay(100);

  }
  if(controlInput == 'p')
  {
    currentChallenge = "none";
    bb.adjustSpeed(0,0);
    BlueTooth.println("Challenge changed to none");
  }

  if(currentChallenge == "Navigate")
  {
    sensorValueLeft = digitalRead(pinSensorLeft); // read the value from the sensor
    sensorValueRight = digitalRead(pinSensorRight); // read the value from the sensor
    
    while(!(sensorValueLeft == 1 && sensorValueRight == 1))
    {
      sensorValueLeft = digitalRead(pinSensorLeft); // read the value from the sensor
      sensorValueRight = digitalRead(pinSensorRight); // read the value from the sensor
      bb.adjustSpeed(4,4);
    }
    bb.adjustSpeed(0,0);
    currentChallenge = "none";
    BlueTooth.println("Reached destination");
  }
  
  if(currentChallenge == "Tape")
  {
    sensorValueLeft = digitalRead(pinSensorLeft); // read the value from the sensor
    sensorValueRight = digitalRead(pinSensorRight); // read the value from the sensor
    BlueTooth.println(sensorValueLeft);
    BlueTooth.println(sensorValueRight);
    
    if(sensorValueLeft == 1 && sensorValueRight == 1)
    {
      bb.adjustSpeed(-4,-4);
      delay(50);
      bb.adjustSpeed(0,0);
      delay(50);
    }
    else if(sensorValueLeft == 1)
    {
      //go right
      turn(4, 10);
      delay(100);
      bb.adjustSpeed(-4,-4);
      delay(150);
    }
    else if(sensorValueRight == 1)
    {
      //go left
      turn(6, -10);
      delay(100);
      bb.adjustSpeed(-4,-4);
      delay(150);
    }
    else
    {
      //go straight
      bb.adjustSpeed(3,3);
      delay(10);
  
    }  
  }

  if(currentChallenge == "Maze")
  {
    sensorValueLeft = digitalRead(pinSensorLeft); // read the value from the sensor
    sensorValueRight = digitalRead(pinSensorRight); // read the value from the sensor
    BlueTooth.println(sensorValueLeft);
    BlueTooth.println(sensorValueRight);
    
    if(sensorValueLeft == 1 && sensorValueRight == 1)
    {
      bb.adjustSpeed(-6,-6);
      delay(400);
      turn(6, 90);
      
    }
    else if(sensorValueLeft == 1)
    {
      bb.adjustSpeed(-6,-6);
      delay(250);
      turn(6, -15);
      
    }
    else if(sensorValueRight == 1)
    {
      bb.adjustSpeed(-6,-6);
      delay(250);
      turn(6, 15);
      
    }
    else
    {
      //go straight
      bb.adjustSpeed(4,4);
      delay(50);
  
    }  
  }

  if(currentChallenge == "Balloon")
  {
    
    switch(controlInput)
    {        
      case 'F':
        bb.adjustSpeed(robotSpeed , robotSpeed);
        Serial.println("Going forward");
        break;
      case 'R':
        bb.adjustSpeed(robotSpeed, -robotSpeed);
        Serial.println("Going right");
        break;
      case 'B':
        bb.adjustSpeed(-robotSpeed, -robotSpeed);
        Serial.println("Going backwards");
        break;
      case 'L':
        bb.adjustSpeed(-robotSpeed, robotSpeed);
        Serial.println("Going left");
        break;
      case 'S':
        bb.adjustSpeed(0,0);
        Serial.println("Stopping");
        break;
    }
    delay(50);
  }
  
}
