#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int motor1 = 3; 
int motor2 = 5; 
void setup()
{
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{ 
//  analogWrite(motor1, 128);
//  analogWrite(motor2, 128);
  myservo.write(90);  
//  delay(2000);
//  myservo.write(80);
//  delay(2000);
//  myservo.write(100);
//  delay(2000);
} 

