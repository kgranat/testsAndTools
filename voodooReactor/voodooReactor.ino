     /* 
  ArbotiX Firmware - Commander Extended Instruction Set Example
  Copyright (c) 2008-2010 Vanadium Labs LLC.  All right reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the Vanadium Labs LLC nor the names of its 
        contributors may be used to endorse or promote products derived 
        from this software without specific prior written permission.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL VANADIUM LABS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/ 
 
#include <ax12.h>
#include <BioloidController.h>

/* Hardware Constructs */
BioloidController bioloid = BioloidController(1000000);

//analog pins = plug in your potentiometer to each analog port, i.e. A0 for base, A1 for shoulder, etc
#define BASE_ANALOG_PIN    0
#define SHOULDER_ANALOG_PIN   1
#define ELBOW_ANALOG_PIN   2
#define WRIST_ANALOG_PIN  3
#define GRIPPER_ANALOG_PIN   4

#define BASE_SERVO 1
#define SHOULDER_SERVO_1 2
#define SHOULDER_SERVO_2 3
#define ELBOW_SERVO_1 4
#define ELBOW_SERVO_2 5
#define WRIST_ANGLE_SERVO 6
#define WRIST_ROT_SERVO 7
#define GRIPPER 8

#define SERVO_NUMBER 8
#define SPEED 300 // speed. 0 = full speed. Any other values = speed * .111 RPM. 300= ~33.3 RPM http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_20

// the F2 'C' bracket attached to the tilt servo creates a physical limitation to how far
// we can move the tilt servo. This software limit will ensure that we don't jam the bracket into the servo.
#define SHOULDER_UPPER_LIMIT 800 
#define SHOULDER_LOWER_LIMIT 200

#define ELBOW_UPPER_LIMIT 868 
#define ELBOW_LOWER_LIMIT 250

#define WRIST_UPPER_LIMIT 856
#define WRIST_LOWER_LIMIT 158

//Upper/Lower limits for the pan servo - by defualt they are the normal 0-1023 (0-300) positions for the servo
#define BASE_UPPER_LIMIT 1023 
#define BASE_LOWER_LIMIT 0

#define GRIPPER_UPPER_LIMIT 512 
#define GRIPPER_LOWER_LIMIT 0

//values for the potentiometers (0-1023)
int potBaseVal, potShoulderVal, potElbowVal, potGripperVal, potWristVal;

int positionHistory[5][5]; //2d array to hold averages for 5 main joints 
int avgReady = 0; //we've read enough positions to start averaging
int avgPosition = 0; //current index in the averaging array

void setup(){
 
 Serial.begin(9600);   //serial data for debugging 
 
 //set compliance slopes for the gripper, this means the gripper will not fight as hard to get to a position, which will reduce burn-out.
 ax12SetRegister(8, AX_CW_COMPLIANCE_SLOPE, 128);
 ax12SetRegister(8, AX_CCW_COMPLIANCE_SLOPE, 128);
 
 
 for(int i = 0; i < SERVO_NUMBER; i++ )
 {
  ax12SetRegister2(i, AX_GOAL_SPEED_L, SPEED);//set the goal speed register for each servo
 }
 



}

void loop()
{
  //Serial.println(avgPosition);
  
  
    positionHistory[BASE_ANALOG_PIN][avgPosition] = analogRead(BASE_ANALOG_PIN); 
    delay(5);   
    positionHistory[SHOULDER_ANALOG_PIN][avgPosition] = analogRead(SHOULDER_ANALOG_PIN); 
    delay(5);   
    positionHistory[ELBOW_ANALOG_PIN][avgPosition] = analogRead(ELBOW_ANALOG_PIN); 
    delay(5);   
    positionHistory[WRIST_ANALOG_PIN][avgPosition] = analogRead(WRIST_ANALOG_PIN); 
    delay(5);   
    positionHistory[GRIPPER_ANALOG_PIN][avgPosition] = analogRead(GRIPPER_ANALOG_PIN); 
    delay(5);   
    
    Serial.print(positionHistory[0][avgPosition]);
    Serial.print(" ");
    Serial.print( positionHistory[2][avgPosition]);
    
  
  avgPosition = avgPosition + 1;
//  Serial.println(avgPosition++);
  if(avgPosition > 4)
  {
     avgReady = 1;  //let theprogram know that it can run, i.e. we have a valid average set
     avgPosition = 0;//reset the averaging index
    Serial.println("Average");
  }
  
  if(avgReady ==1)
  {
    //get the average for each joint
    potGripperVal = (positionHistory[4][0]+ positionHistory[4][1]+ positionHistory[4][2]+ positionHistory[4][3]+ positionHistory[4][4])/5;
    potWristVal = (positionHistory[3][0]+ positionHistory[3][1]+ positionHistory[3][2]+ positionHistory[3][3]+ positionHistory[3][4])/5;
    potElbowVal = (positionHistory[2][0]+ positionHistory[2][1]+ positionHistory[2][2]+ positionHistory[2][3]+ positionHistory[2][4])/5;
    potShoulderVal = (positionHistory[1][0]+ positionHistory[1][1]+ positionHistory[1][2]+ positionHistory[1][3]+ positionHistory[1][4])/5;
    potBaseVal = (positionHistory[0][0] + positionHistory[0][1] + positionHistory[0][2] + positionHistory[0][3] + positionHistory[0][4])/5;
      
    Serial.print(potElbowVal);
    Serial.print(" ");
    
//      Serial.print(positionHistory[3][0]);
//      Serial.print(" | ");
//      Serial.print(positionHistory[3][1]);
//      Serial.print(" | ");
//      Serial.print(positionHistory[3][2]);
//      Serial.print(" | ");
//      Serial.print(positionHistory[3][3]);
//      Serial.print(" | ");
//      Serial.print(positionHistory[3][4]);
//      Serial.print(" | ");      
//      Serial.print(potGripperVal);
//      Serial.println(" | ");
    
    //gripper mapping for the FSR
    potGripperVal = map(potGripperVal-200, 0, 824,GRIPPER_LOWER_LIMIT, GRIPPER_UPPER_LIMIT);
    
    //contrain the input value to the joint limits
    potBaseVal = constrain(potBaseVal,BASE_LOWER_LIMIT, BASE_UPPER_LIMIT );
    potShoulderVal = constrain(potShoulderVal,SHOULDER_LOWER_LIMIT, SHOULDER_UPPER_LIMIT );
    potElbowVal = constrain(potElbowVal,ELBOW_LOWER_LIMIT, ELBOW_UPPER_LIMIT );
    potGripperVal = constrain(potGripperVal,GRIPPER_LOWER_LIMIT, GRIPPER_UPPER_LIMIT);
    potWristVal = constrain(potWristVal,WRIST_LOWER_LIMIT, WRIST_UPPER_LIMIT );
        
    Serial.print(potElbowVal);
    Serial.println(" ");
    
    SetPosition(BASE_SERVO,1023-potBaseVal); //set base position - 1023-potBaseVal inverts the value to align with the voodoom arm.     
    
    SetPosition(SHOULDER_SERVO_1,potShoulderVal);//set shoulder value
    SetPosition(SHOULDER_SERVO_2,1023-potShoulderVal); //invert the value for the 2nd joint
    
    SetPosition(ELBOW_SERVO_1,potElbowVal);//set elbow value
    SetPosition(ELBOW_SERVO_2,1023-potElbowVal); //invert the value for the 2nd joint
        
    SetPosition(WRIST_ANGLE_SERVO,1023-potWristVal); //invert the value to align to the voodoo arm
    SetPosition(WRIST_ROT_SERVO,512);  //fixed position for the wrist rotate
    SetPosition(GRIPPER,512-potGripperVal);  //grippper onyl works from 0-512, 512-potGripperVal inverts the value to align with the FSR
    
  
    delay(15);   
  }
}





