
#include <ax12.h>
#include <BioloidController.h>

/* Hardware Constructs */
BioloidController bioloid = BioloidController(1000000);

const int enc1 = 0;
const int enc2 = 1;  // connect the rotary encoder
const int enc3 = 2;
const int enc4 = 3;
const int enc5 = 4;
const int enc6 = 5;

const int servoid1 = 1; //servo id to control, 254 = brodcast
const int servoid2 = 2;
const int servoid3 = 3;
const int servoid4 = 4;
const int servoid5 = 5;
const int servoid6 = 6;


const int SERVO_COUNT = 6;

int encread1;    // variable read the value from the analog pin 
int encread2;
int encread3;
int encread4;
int encread5;
int encread6;


unsigned long lastMotorUpdate ; //last time the motors were sent a new command 
int motorUpdateRate = 33;            //33 ms = ~30 hz

unsigned long lastPrint ; //last time the motors were sent a new command 
int printUpdateRate = 5000;            //33 ms = ~30 hz



void setup(){

  Serial.begin(38400);
  encread1 = analogRead(0);  
  encread2 = analogRead(1);
  encread3 = analogRead(2);
  encread4 = analogRead(3);
  encread5 = analogRead(4);
  encread6 = analogRead(5);
  
  
  encread1 = map(encread1, 0, 1023, 4096, 0);  //  do not map for ax servo-- 
  encread2 = map(encread2, 0, 1023, 0, 4096); 
  encread3 = map(encread3, 0, 1023, 0, 4096); 
  encread4 = map(encread4, 0, 1023, 4096, 0); 
  encread5 = map(encread5, 900, 400, 0, 1023); 
  //encread6 = map(encread6, 950, 840, 400, 500); 

  
  bioloid.poseSize = 6;            //2 servos, so the pose size will be 2
  bioloid.readPose();              //find where the servos are currently
  bioloid.setNextPose(servoid1,encread1);    //prepare the PAN servo to the default position
  bioloid.setNextPose(servoid2,encread2);  //preprare the tilt servo to the default position
  bioloid.setNextPose(servoid3,encread3);    //prepare the PAN servo to the default position
  bioloid.setNextPose(servoid4,encread4);  //preprare the tilt servo to the default position
  bioloid.setNextPose(servoid5,encread5);    //prepare the PAN servo to the default position
  bioloid.setNextPose(servoid6,encread6);  //preprare the tilt servo to the default position
  bioloid.interpolateSetup(2000);  //setup for interpolation from the current position to the positions set in setNextPose, over 2000ms
  while(bioloid.interpolating > 0) //until we have reached the positions set in setNextPose, execute the instructions in this loop
  {
    bioloid.interpolateStep();//move servos 1 'step
    delay(3);
  }


}

void loop(){

  
  
  encread1 = analogRead(0);  
  delay(2);
  encread2 = analogRead(1);
  delay(2);
  encread3 = analogRead(2);
  delay(2);
  encread4 = analogRead(3);
  delay(2);
  encread5 = analogRead(4);
  delay(2);
  encread6 = analogRead(5);
  
  encread1 = map(encread1, 0, 1023, 4096, 0);  //  do not map for ax servo-- 
  encread2 = map(encread2, 0, 1023, 0, 4096); 
  encread3 = map(encread3, 0, 1023, 0, 4096); 
  encread4 = map(encread4, 0, 1023, 4096, 0); 
  encread5 = map(encread5, 900, 400, 0, 1023); 
  //encread6 = map(encread6, 950, 840, 400, 500); 

  
  if(millis() - lastMotorUpdate > motorUpdateRate)
  {
    lastMotorUpdate = millis();
    SetPosition(servoid1,encread1);
    SetPosition(servoid2,encread2);
    SetPosition(servoid3,encread3);
    SetPosition(servoid4,encread4);
    SetPosition(servoid5,encread5);
    SetPosition(servoid6,encread6);
  }

  
  if(millis() - lastPrint > printUpdateRate)
  {
    
    lastPrint = millis();
    ScanServo();
  }



 
}



void ScanServo(){

  int IDCheck = 1; //assume all servos found  
  Serial.println("###########################");
  Serial.println("Starting Servo Scanning Test.");
  Serial.println("###########################");
      
  for (int id = 1; id <= SERVO_COUNT; id++)
  {
    int pos =  ax12GetRegister(id, 36, 2);
    Serial.print("Servo ID: ");
    Serial.println(id);
    Serial.print("Servo Position: ");
    Serial.println(pos);
    int errorBit = ax12GetLastError();
    
    Serial.print("Servo Error Bit: ");
    Serial.println(errorBit);
    
      
      if(ERR_NONE & errorBit)
      {
        Serial.println("          No Errors Found");
  
      }
      
      if(ERR_VOLTAGE & errorBit)
      {
        Serial.println("          Voltage Error");
  
      }
      
      if(ERR_ANGLE_LIMIT & errorBit)
      {
        Serial.println("          Angle Limit Error");
  
      }
      
      if(ERR_OVERHEATING & errorBit)
      {
        Serial.println("          Overheating Error");
  
      }
      
      if(ERR_RANGE & errorBit)
      {
        Serial.println("          Range Error");
  
      }
      
      if(ERR_CHECKSUM & errorBit)
      {
        Serial.println("          Checksum Error");
  
      }
      
      if(ERR_OVERLOAD & errorBit)
      {
        Serial.println("          Overload Error");
  
      }
      
      
      if(ERR_INSTRUCTION & errorBit)
      {
        Serial.println("          Instruction Error");
  
      }
    
    
  
  
  
    if (pos <= 0)
    {
      Serial.println("###########################");
      Serial.print("ERROR! Servo ID: ");
      Serial.print(id);
      Serial.println(" not found. Please check connection and verify correct ID is set.");
      Serial.println("###########################"); 
      IDCheck = 0;
    }
    

   delay(10);
  }
  
  if (IDCheck == 0)
  {
    Serial.println("###########################");
    Serial.println("ERROR! Servo ID(s) are missing from Scan. Please check connection and verify correct ID is set.");
    Serial.println("###########################");  
  }
  else
  {
    Serial.println("All servo IDs present.");
  }


}
