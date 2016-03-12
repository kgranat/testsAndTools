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


const int potpin = 0;  // analog pin used to connect the potentiometer
const int servoId = 254; //servo id to control, 254 = brodcast
int knobVal;    // variable to read the value from the analog pin 

void setup(){

}

void loop(){
  
  
  knobVal = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023, which matches the positional range for an AX-12) 
  //knobVal = map(knobVal, 0, 1023, 0, 4095);     // for MX servos map 0-1023 to 0-4095, the positional range for MX servos
  SetPosition(servoId,val);
  delay(5);   
    
    
 
}




