

/*

  	Left Joystick Vertical (-128 to 127)
	  	command.walkV 

  	Left Joystick Horizontal (-128 to 127)
	  	command.walkH


  	Right Joystick Vertical (-128 to 127)
	  	command.lookV 
	  	
  	Right Joystick Horizontal (-128 to 127)
	  	command.lookH

	10-bit high resolution 'Pan' value, created by comibining both left joystick axes (0-1023)
	  	command.pan


	10-bit high resolution 'Tilt' value, created by comibining both right joystick axes (0-1023)
	  	command.tilt

  	Single byte that holds all of the button data - each bit represents a button being on or off
	  	command.buttons
  	
	Button Bitmasks
		BUT_R1
	  	BUT_R2
	  	BUT_R3
	  	BUT_L4
	  	BUT_L5
	  	BUT_L6
	  	BUT_RT
	  	BUT_LT

	Extended instruction
	  	command.ext

  	
*/
#include <Commander.h> //include commander library
#include <Servo.h> //include servo library

Commander command = Commander();	//start commander object

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

const int SERVO1_PIN = 12;
const int SERVO2_PIN = 13;
const int SERVO3_PIN = 14;
const int SERVO4_PIN = 15;
const int SERVO5_PIN = 16; 

int servo1Position = 90;
int servo2Position = 90;
int servo3Position = 90;
int servo4Position = 90;
int servo5Position = 90;

void setup()
{
  // setup serial for commander communications 
  Serial.begin(38400);
  
  //attach servos to pins
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);
  
  //center servos
  servo1.write(servo1Position);
  servo2.write(servo2Position);
  servo3.write(servo3Position);
  servo4.write(servo4Position);
  servo5.write(servo5Position);

}

void loop()
{

  //check if there is commander compatible data coming in on the serial port
  if(command.ReadMsgs() > 0)
  {
    
        //commander joysticks are read on a scale feom -127 (down or left) to 127 (up ror right). Map these values to 0-180 for a servo
        servo1Position = map(command.walkV, -127, 128, 0, 180);
        servo2Position = map(command.walkH, -127, 128, 0, 180);
        servo3Position = map(command.lookH, -127, 128, 0, 180);
        servo4Position = map(command.lookH, -127, 128, 0, 180);
        
        //set last servo based on a button (r1)
        if(command.buttons & BUT_R1)
        {
          servo5Position = 0;
        }
        
        else
        {
          servo5Position = 180;
        }
        
        


  }

}
