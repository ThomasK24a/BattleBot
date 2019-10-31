#include<Wire.h>
#include <SoftwareSerial.h>
#include <battleBotSetup.h>

SoftwareSerial BlueTooth(A0, A1);
BattleBotSetup bb;

int sensorValueLeft;
int sensorValueRight;

int pinSensorLeft = 10;
int pinSensorRight = 11;

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

void driveForward()
{  
  float divergence = 0.0;
  while(true)
  {  
    bb.adjustSpeed(4,4);
    
    currentTime = millis();
    if ((currentTime - previousTime) > 50)
    {
      divergence += degreesTurned;
      previousTime = currentTime;
    }
    getAngle();


    BlueTooth.println("Degrees turned: ");
    BlueTooth.println(divergence);
    

    
    if (divergence > 15)
    {
      BlueTooth.println("disruption detected, turning left this amount of degrees:");
      BlueTooth.println(divergence);
      turn(6, -divergence);
      divergence = 0;
    }
    else if (divergence < -15)
    {
      BlueTooth.println("disruption detected, turning right this amount of degrees:");
      BlueTooth.println(divergence);
      turn(6, divergence);
      divergence = 0;
    }
    delay(10);
  }
  


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
  degreesTurned = GyZ / 1800;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(38400);
  BlueTooth.begin(38400);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop()
{
  driveForward();
//  if (BlueTooth.available())
//  {
//    controlInput = BlueTooth.read();
//  
//  }
//  if(controlInput == 'c')
//  {
//    
//    driveForward();
//    
//  }
// if(controlInput == 'd')
//  {
//    BlueTooth.println("sup");
//    //turn(4, -15);
//    controlInput = 'b';
//  }
  delay(500);
}
