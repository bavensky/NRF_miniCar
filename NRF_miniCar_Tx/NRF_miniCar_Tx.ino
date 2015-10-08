#include <NRF24.h>
#include "SPI.h"

NRF24 nrf24(10, 9);

#define YAW       A0
#define THROTTLE  A1
#define ROW       A3
#define PITCH     A2

void setup() {
  Serial.begin(9600);
  if (!nrf24.init())
    Serial.println("NRF24 init failed");
  if (!nrf24.setChannel(8))
    Serial.println("setChannel failed");
  if (!nrf24.setPayloadSize(32))
    Serial.println("setPayloadSize failed");
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
    Serial.println("setRF failed");    
  nrf24.spiWriteRegister(NRF24_REG_1D_FEATURE, NRF24_EN_DYN_ACK);
  Serial.println("initialised");
}

void loop() {
int thro = map(analogRead(THROTTLE),798, 205, 0, 255);
int yaw = map(analogRead(YAW),102, 770, 255, 0 );

 Serial.print(analogRead(THROTTLE));
 Serial.print(" ");
 Serial.print(analogRead(YAW));
 Serial.print(" ");
 Serial.print(thro); 
 Serial.print(" ");
 Serial.println(yaw);
  
  uint8_t buf[32];
  
  buf[1] = thro;
  buf[2] = yaw;
  
  if (!nrf24.setTransmitAddress((uint8_t*)"bicycle", 5))
   Serial.println("setTransmitAddress failed");
  if (!nrf24.send(buf, sizeof(buf), true)) 
     Serial.println("send failed");  
  if (!nrf24.waitPacketSent())
     Serial.println("waitPacketSent failed");
}
