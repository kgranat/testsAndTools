
#include <ax12.h>
#include <BioloidController.h>
#define SERVO_ID 1

int servoPosition;

//BioloidController bioloid = BioloidController(57600);  //create a bioloid object at a baud of 57600MBps
BioloidController bioloid = BioloidController(1000000);  //create a bioloid object at a baud of 1MBps

void setup()
{
 
  //set wheel mode
  ax12SetRegister2(SERVO_ID, AX_CW_ANGLE_LIMIT_L         , 0); // write two bytes to memory (ADDR, ADDR+1)
  ax12SetRegister2(SERVO_ID, AX_CCW_ANGLE_LIMIT_L        , 0); // write two bytes to memory (ADDR, ADDR+1)
  
  //set speed
  ax12SetRegister2(SERVO_ID, AX_GOAL_SPEED_L             , 1023); // write two bytes to memory (ADDR, ADDR+1)

    
  
 }
void loop()
{

}

