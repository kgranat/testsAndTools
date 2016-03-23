/***************************
 * DXL Encoder Read
 * Read servo and send data to 
 * Serial Monitor
 ***************************/

//import ax12 library to send DYNAMIXEL commands
#include <ax12.h>
#include <BioloidController.h>

const int SERVO_ID = 1;
int servoPosition;

BioloidController bioloid = BioloidController(1000000);

void setup()
{
  Serial.begin(38400);
   
}

void loop()
{
 
    servoPosition = GetPosition(1);
    delay(500);//wait for servo to move
    
    Serial.println(servoPosition);//print servo Position
   
}




