
#include <ax12.h>
#include <BioloidController.h>
#define SERVO_ID 254

int servoPosition;

BioloidController bioloid = BioloidController(57600);  //create a bioloid object at a baud of 1MBps
//BioloidController bioloid = BioloidController(1000000);  //create a bioloid object at a baud of 1MBps




void setup()
{

  bioloid.poseSize = 3;//2 servos, so the pose size will be 2
  bioloid.readPose();//find where the servos are currently
  bioloid.setNextPose(1,0);//prepare the PAN servo to the centered position, pan/2048
  bioloid.setNextPose(2,0);//prepare the PAN servo to the centered position, pan/2048
  bioloid.setNextPose(3,0);//prepare the PAN servo to the centered position, pan/2048

  bioloid.interpolateSetup(4000);//setup for interpolation from the current position to the positions set in setNextPose, over 2000ms
  while(bioloid.interpolating > 0)  //until we have reached the positions set in setNextPose, execute the instructions in this loop
  {
    bioloid.interpolateStep();//move servos 1 'step
    delay(3);
  }
  
  
 }
void loop()
{
  for(servoPosition = 0; servoPosition < 4096; servoPosition++)
 {
    SetPosition(SERVO_ID, servoPosition);
    delay(10);
 }
 
 for(servoPosition = 4095; servoPosition >= 0; servoPosition--)
 {
    SetPosition(SERVO_ID, servoPosition);
    delay(10);
 }

    
}

