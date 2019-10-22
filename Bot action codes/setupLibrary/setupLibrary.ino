//include libraries
#include <SoftwareSerial.h>
#include<Wire.h>

//Setup connection
SoftwareSerial BlueTooth(A0, A1);

//Set all the pins
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;
int pinSensorLeft = 10;
int pinSensorRight = 11;
int pinTrigger = 13;
int pinEcho = 12;

//For setting the speed of the motors
int leftSpeed;
int rightSpeed;
int leftSpeedInput;
int rightSpeedInput;

//Variables used for turning
unsigned long previousTime = 0;
unsigned long currentTime;
float degreesTurnedTotal = 0.0;
float degreesTurned = 0;

//Used by the gyroscope

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

//will put the speed from leftSpeed and rightSpeed into the motors
void setSpeed()
{
  BlueTooth.println("Setting speed");
  if (leftSpeed > 0)
  {
    leftSpeedInput = leftSpeed * 25;
    //leftSpeedInput = 119;
    BlueTooth.println(leftSpeedInput);
    analogWrite(pinLeftWheelBackward, 0);
    analogWrite(pinLeftWheelForward, leftSpeedInput);
  }
  else
  {
    leftSpeedInput = leftSpeed * -25;
    BlueTooth.println(leftSpeedInput);
    analogWrite(pinLeftWheelBackward, leftSpeedInput);
    analogWrite(pinLeftWheelForward, 0);
  }

  if (rightSpeed > 0)
  {
    rightSpeedInput = rightSpeed * 23;
    //rightSpeedInput = 110;
    BlueTooth.println(rightSpeedInput);
    analogWrite(pinRightWheelBackward, 0);
    analogWrite(pinRightWheelForward, rightSpeedInput);
  }
  else
  {
    rightSpeedInput = rightSpeed * -23;
    BlueTooth.println(rightSpeedInput);
    analogWrite(pinRightWheelBackward, rightSpeedInput);
    analogWrite(pinRightWheelForward, 0);
  }
}

//will turn the bot for the set amount of degrees and the set speed, degrees is clockwise and minus will turn it countclockwise
void turn(int speed, int degrees)
{
  leftSpeed = 0;
  rightSpeed = 0;
  setSpeed();
  delay(100);
  BlueTooth.println("Degrees about to turn: ");
  BlueTooth.println(degrees);
  
  
  //decides whether it has to turn clockwise or counterclockwise
  if (degrees > 0)
  {
    leftSpeed = speed;
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
      setSpeed();

      delay(10);

    }
  }
  else
  {
    //same as above but counterclockwise
    rightSpeed = speed;
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
      setSpeed();
      delay(10);

    }
  }
  BlueTooth.println("Finished turning");
  leftSpeed = 0;
  rightSpeed = 0;
  setSpeed();
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
  // sets up a bluetooth connection
  Serial.begin(38400);
  BlueTooth.begin(38400);

  //used for the gyroscope
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
