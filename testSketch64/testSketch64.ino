
#include <ax12.h>
#include <BioloidController.h>
#define SERVO_ID 254

int servoPosition;

BioloidController bioloid = BioloidController(57600);  //create a bioloid object at a baud of 57600MBps
//BioloidController bioloid = BioloidController(1000000);  //create a bioloid object at a baud of 1MBps

void setup()
{

  
 }
void loop()
{
  for(servoPosition = 0; servoPosition <= 4095; servoPosition++)
 {
    SetPosition(SERVO_ID, servoPosition);
    delay(5);
 }
 
 for(servoPosition = 4095; servoPosition >= 0; servoPosition--)
 {
    SetPosition(SERVO_ID, servoPosition);
    delay(5);
 }

    
}

