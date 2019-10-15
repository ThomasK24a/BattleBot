  #define trigPin 13
  #define echoPin 12
  
  
  void setup() {
    // put your setup code here, to run once:
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
  }
  
  void loop() 
  {
    // put your main code here, to run repeatedly:
    int duration;
    int distance;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
  
    if (distance >= 200 || distance <= 0)
    {
      Serial.println("Out of range \r\n");
      //Serial.print(distance);
      //Serial.print(" cm \r\n");
    }
    else
    {
      Serial.print(distance);
      Serial.print(" cm \r\n");
    }
    delay(50);
    
  }
