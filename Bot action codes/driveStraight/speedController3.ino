char controlInput = 'b';

int leftSpeed = 2;
int rightSpeed = 2;
int leftSpeedInput = 100;
int rightSpeedInput = 100;

int degreesTurned = 0;

unsigned long currentTime;
unsigned long previousTime;

#include<Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);
int pinLeftWheelBackward = 2;
int pinRightWheelBackward = 4;
int pinLeftWheelForward = 3;
int pinRightWheelForward = 9;

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

void turn(int speed, int degrees) 
{
  leftSpeed = 0;
  rightSpeed = 0;
  setSpeed();
  delay(500);
  //Degrees is clockwise
  BlueTooth.println("Degrees about to turn: ");
  BlueTooth.println(degrees);

  previousTime = 0;
  float temp = 0.0;
  degreesTurned = 0;
  if (degrees > 0)
  {
    leftSpeed = speed;
    degrees = -degrees;
    while (temp > degrees)
    {
      currentTime = millis();
      if ((currentTime - previousTime) > 50)
      {
        temp += degreesTurned;
        previousTime = currentTime;
      }
      getAngle();


      BlueTooth.println("Degrees turned: ");
      BlueTooth.println(temp);
      setSpeed();

      delay(10);

    }
  }
  else
  {
    rightSpeed = speed;
    degrees = -degrees;
    while (temp < degrees)
    {
      currentTime = millis();
      if ((currentTime - previousTime) > 50)
      {
        temp += degreesTurned;
        previousTime = currentTime;
      }
      getAngle();


      BlueTooth.println("Degrees turned: ");
      BlueTooth.println(temp);
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

void driveForward()
{  
  float divergence = 0.0;
  while(true)
  {  
    leftSpeed = 4;
    rightSpeed = 4;
    setSpeed();

    
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
 
  if (BlueTooth.available())
  {
    controlInput = BlueTooth.read();
  
  }
  if(controlInput == 'c')
  {
    
    driveForward();
    controlInput = 'b';
  }
 if(controlInput == 'd')
  {
    
    turn(4, -15);
    controlInput = 'b';
  }
  delay(500);
}
