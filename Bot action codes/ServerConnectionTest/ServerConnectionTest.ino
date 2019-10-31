#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0x00, 0x71, 0xCC, 0x3B, 0x58, 0x5D };
 
// Enter the IP address for Arduino, as mentioned we will use 192.168.0.16
// Be careful to use , insetead of . when you enter the address here
IPAddress ip(10,232,0,107);

int sensorPinLeft = 10; // Analog input pin on Arduino we connected the SIG pin from sensor
int sensorValueLeft; // Here we will place our reading

// Initialize the Ethernet server library
EthernetServer server(80);

void setup() 
{
 
 // Serial.begin starts the serial connection between computer and Arduino
  Serial.begin(9600);
 
 // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Arduino server IP address: ");
  Serial.println(Ethernet.localIP());
}
  
void loop()
{
  
}
