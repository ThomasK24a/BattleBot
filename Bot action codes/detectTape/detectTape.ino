int sensorPinLeft = 10;
int sensorPinRight = 11;
int sensorValueLeft;

void setup() 
{
  Serial.begin(9600); //sets serial port for communication
  
}

void loop() 
{
  sensorValueLeft = digitalRead(sensorPinLeft); // read the value from the sensor
  Serial.println(sensorValueLeft); //prints the values coming from the sensor on the screen
}
