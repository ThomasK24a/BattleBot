#define trigPin 13
#define echoPin 12
int duration;
int distance;

void measureDistance()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Out of range \r\n");
  }
  else
  {
    Serial.print(distance);
    Serial.print(" cm \r\n");
  }
}
  
  void setup() {
    // put your setup code here, to run once:
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
  }
  
  void loop() 
  {
    measureDistance();
    
    
    
  }
