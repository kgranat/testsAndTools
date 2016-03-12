
#include <ax12.h>
#include <BioloidController.h>
#define SERVO_ID 254

int servoPosition;

BioloidController bioloid = BioloidController(57600);  //create a bioloid object at a baud of 1MBps
//BioloidController bioloid = BioloidController(1000000);  //create a bioloid object at a baud of 1MBps




void setup()
{

  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  
  
 }
void loop()
{
    SetPosition(SERVO_ID, 0);
    delay(1000);

    SetPosition(SERVO_ID, 2048);
    delay(1000);

    SetPosition(SERVO_ID, 1023);
    delay(1000);

    SetPosition(SERVO_ID, 3072);
    delay(1000);

    
}

