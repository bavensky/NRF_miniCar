#include <NRF24.h>
#include "SPI.h"
#include <Servo.h>

NRF24 nrf24(9, 10);

Servo wheel;  

int motor1 = 3; 
int motor2 = 5; 

void setup()
{
  Serial.begin(9600);
  
  wheel.attach(6);
  wheel.write(90);  

  if (!nrf24.init())
    Serial.println("NRF24 init failed");
  if (!nrf24.setChannel(8))
    Serial.println("setChannel failed");
  if (!nrf24.setThisAddress((uint8_t*)"bicycle", 5))
    Serial.println("setThisAddress failed");
  if (!nrf24.setPayloadSize(32))
    Serial.println("setPayloadSize failed");
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
    Serial.println("setRF failed");    
  if (!nrf24.powerUpRx())
      Serial.println("powerOnRx failed");    
  Serial.println("initialised");
}

void loop() 
{ 
  uint8_t buf[32];
  uint8_t len = sizeof(buf);
  nrf24.waitAvailable();
  
  if (nrf24.recv(buf, &len))  {
    int speedfan = buf[1];
    int c_wheel = map(buf[2],0, 255, 100, 80);
    wheel.write(c_wheel);
    analogWrite(motor1, speedfan);
    analogWrite(motor2, speedfan);
    Serial.println(speedfan);
  }
}

