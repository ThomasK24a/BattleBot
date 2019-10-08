// challenge 3


int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int lowLightPin = 13;
int medLightPin = 12;
int highLightPin = 11;

void setup() {
  Serial.begin(9600); //sets serial port for communication
  pinMode(lowLightPin, OUTPUT);
  pinMode(medLightPin, OUTPUT);
  pinMode(highLightPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen

  delay(100);
  if(sensorValue < 50)
  {
    digitalWrite(lowLightPin, HIGH);
    digitalWrite(medLightPin, LOW);
    digitalWrite(highLightPin, LOW);
    
  }
  else if(sensorValue < 75)
  {
    digitalWrite(lowLightPin, LOW);
    digitalWrite(medLightPin, HIGH);
    digitalWrite(highLightPin, LOW);
  }
  else
  {
    digitalWrite(lowLightPin, LOW);
    digitalWrite(medLightPin, LOW);
    digitalWrite(highLightPin, HIGH);
  }
}
