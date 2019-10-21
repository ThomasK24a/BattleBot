char controlInput = 'a';
int leftSpeed = 0;
int rightSpeed = 0;
int leftSpeedInput = 100;
int rightSpeedInput = 100;
int degreesTurned = 0;
unsigned long currentTime;
unsigned long previousTime = 0;

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
  if (leftSpeed > 0)
  {
    leftSpeedInput = leftSpeed * 25;
    //leftSpeedInput = 119;
    analogWrite(pinLeftWheelBackward, 0);
    analogWrite(pinLeftWheelForward, leftSpeedInput);
  }
  else
  {
    leftSpeedInput = leftSpeed * -25;
    analogWrite(pinLeftWheelBackward, leftSpeedInput);
    analogWrite(pinLeftWheelForward, 0);
  }

  if (rightSpeed > 0)
  {
    rightSpeedInput = rightSpeed * 23;
    //rightSpeedInput = 110;
    analogWrite(pinRightWheelBackward, 0);
    analogWrite(pinRightWheelForward, rightSpeedInput);
  }
  else
  {
    rightSpeedInput = rightSpeed * -23;
    analogWrite(pinRightWheelBackward, rightSpeedInput);
    analogWrite(pinRightWheelForward, 0);
  }
}

void turn(int speed, int degrees) {
  //Degrees is clockwise
  BlueTooth.println("Degrees about to turn: ");
  BlueTooth.println(degrees);
  
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

  
  rightSpeed = 0;
  leftSpeed = 0;
  setSpeed();
}

void driveForward(int speed)
{
  boolean condition = true;
  
  while(condition)
  {
    leftSpeed = 4;
    rightSpeed = 4;
    setSpeed;
    
    getAngle();

    if(degreesTurned > 5)
    {
      turn(4,-degreesTurned);
    }
    else if(degreesTurned < -5)
    {
      turn(4,-degreesTurned);
    }
    
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
  turn(
//  turn(4,180);
//  switch (controlInput)
//  {
//    case 'a':
//      turn(4, 180);
//      controlInput = 'q';
//    case 'q':
//      leftSpeed = 0;
//      rightSpeed = 0;
//      break;
//    
//  }

  if (BlueTooth.available())
  {
    controlInput = BlueTooth.read();

  }




  setSpeed();


  //  BlueTooth.println("left wheel: ");
  //  BlueTooth.println(leftSpeed);
  //  BlueTooth.println(" right wheel: ");
  //  BlueTooth.println(rightSpeed);
  BlueTooth.println(controlInput);
  delay(500);
}
