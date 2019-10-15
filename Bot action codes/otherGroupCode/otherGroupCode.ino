#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(A0, A1);    // (TXD, RXD) of HC-06
char BT_input;                    // to store input character received via BT.
int motorPin1 = 2;                // pin 2 on L293D IC
int motorPin2 = 3;                // pin 7 on L293D IC
int motorPin3 = 4;               // pin 15 on L293D IC
int motorPin4 = 9;               // pin 10 on L293D IC
//PORT 6 for BT
void setup()  
{
  BlueTooth.begin(38400);  
  Serial.begin(38400);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() 
{
  if (BlueTooth.available())
  {
    //BlueTooth.print("ddjfhdhf");
   BT_input=BlueTooth.read();
   if (BT_input=='q')
    {
      digitalWrite(motorPin1, HIGH);   
      digitalWrite(motorPin2, HIGH);   
      digitalWrite(motorPin3, HIGH);   
      digitalWrite(motorPin4, HIGH);   
      Serial.println("Motors are Off");
    }
    if (BT_input=='s')
    {
      digitalWrite(motorPin1, LOW);   
      digitalWrite(motorPin2, LOW);   
      digitalWrite(motorPin3, LOW);   
      digitalWrite(motorPin4, LOW);   
      Serial.println("Motors are Off");
    }
    else if (BT_input=='b')
    {
      digitalWrite(motorPin1, LOW);   
      digitalWrite(motorPin2, HIGH);  
      digitalWrite(motorPin3, LOW);   
      digitalWrite(motorPin4, HIGH);  
      Serial.println("Motors are rotating left");
    }
    else if (BT_input=='f')
    {
      digitalWrite(motorPin1, HIGH); 
      digitalWrite(motorPin2, LOW); 
      digitalWrite(motorPin3, HIGH); 
      digitalWrite(motorPin4, LOW); 
      Serial.println("Motors are rotating right");
    }
   else if (BT_input=='r')
    {
      digitalWrite(motorPin1, HIGH); 
      digitalWrite(motorPin2, LOW); 
      digitalWrite(motorPin3, LOW); 
      digitalWrite(motorPin4, HIGH); 
      Serial.println("First Motor is rotating right & Second is left");
    }
    else if (BT_input=='b')
    {
      digitalWrite(motorPin1, LOW); 
      digitalWrite(motorPin2, LOW); 
      digitalWrite(motorPin3, HIGH); 
      digitalWrite(motorPin4, HIGH); 
      Serial.println("First Motor is rotating right & Second is left");
    }
    else if (BT_input=='l')
    {
      digitalWrite(motorPin1, LOW); 
      digitalWrite(motorPin2, HIGH); 
      digitalWrite(motorPin3, HIGH); 
      digitalWrite(motorPin4, LOW); 
      Serial.println("First Motor is rotating Left & second is right");
    }
  }
 
}
