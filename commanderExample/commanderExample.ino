

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


Commander command = Commander();	//start commander object



void setup()
{
  // setup serial for commander communications 
  Serial.begin(38400);

  //set digital pins to Output 
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop()
{

  //check if there is commander compatible data coming in on the serial port
  if(command.ReadMsgs() > 0)
  {
  	//add '128' to the joystick value - this converts -127 through 128 to 0 through 255 (values tha can be sent to analogWrite)
  	analogWrite(12, command.walkH + 128);	
  	analogWrite(13, command.walkH + 128);
  	analogWrite(14, command.walkH + 128);
  	analogWrite(15, command.walkH + 128);

  	digitalWrite(0, (command.buttons & BUT_R1));
  	digitalWrite(1, (command.buttons & BUT_R2));
  	digitalWrite(2, (command.buttons & BUT_R3));
  	digitalWrite(3, (command.buttons & BUT_L4));
  	digitalWrite(4, (command.buttons & BUT_L5));
  	digitalWrite(5, (command.buttons & BUT_L6));
  	digitalWrite(6, (command.buttons & BUT_RT));
  	digitalWrite(7, (command.buttons & BUT_LT));



  }

}