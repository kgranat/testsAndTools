#include <ax12.h>
#include <BioloidController.h>

BioloidController bioloid = BioloidController(1000000);

const int numberOfServos = 8;

int servosLocated = 0; //total servos located
int servosWithErrors = 0; //total number of servos with errors
void setup()
{
  delay(100);
  Serial.begin(38400); //start serial communications at 38400bps
 
  Serial.println("Servo Scan");
  Serial.print("  Number of Servos:");
  Serial.println(numberOfServos);
  checkServos();  
 
  
  //if all servos are found, display a success message
  if(servosLocated == numberOfServos)
  {
    Serial.print("All ");
    Serial.print(numberOfServos);
    Serial.println(" servos located");
    
  }
  
  //if any of the servos are missing, display an error message
  else
  {
        
    Serial.print(numberOfServos - servosLocated);
    Serial.println(" servo(s) are missing and/or not IDed properly");
  }
  
  
  if(servosWithErrors == 0)
  {
    Serial.println("No Servo Errors Detected");
  }
  else
  {
    Serial.print(servosWithErrors);   
    Serial.println(" servo(s) have errors");   
  }
  
  
}

void loop() 
{
  
}


void checkServos()
{
  
  Serial.print("Looking for Servos 1 - ");
  Serial.println(numberOfServos);
  
  //check for each servo in the chain    
  for(int i = 0; i<numberOfServos;i++)
  {
    int id = i+1;  //the ids for the servos start at 1 while the array indexes start at 0. Add '1' to the array index to get the two to match up
    int idQuery = ax12GetRegister(id, AX_ID, 1); //use ax12GetRegister to check the id on a servo. This will let us know if the servo is connected and communicating 
    
    // expected id matches the actual id, proceed with error checking
    if(id == idQuery)
    {
      servosLocated = servosLocated + 1;
      
      int errorByte = ax12GetLastError();  //get the error byte from the last ax12 command
      
      //header
      Serial.print("    Servo # ");
      Serial.print(id);
      //print error in decimal
      Serial.print("     Error Byte(Decimal):");
      Serial.println(errorByte);
      //print error in binary so we can see each bit
      Serial.print("                  Error Byte(Binary):");
      Serial.println(errorByte, BIN);
      
      //if the error byte is zero, there are no errors. 
      if(errorByte == 0)
      {
        Serial.println("          No Errors Found");
      
      }
      //Otherwise we need to look at the individual bits to figure out the error
      else
      {
         servosWithErrors = servosWithErrors + 1;
         Serial.print("          ERROR: ");
        
        if(ERR_VOLTAGE & errorByte)
        {
          Serial.println("          Voltage Error");
        }
        
        if(ERR_ANGLE_LIMIT & errorByte)
        {
          Serial.println("          Angle Limit Error");
        }
        
        if(ERR_OVERHEATING & errorByte)
        {
          Serial.println("          Overheating Error");
        }
        
        if(ERR_RANGE & errorByte)
        {
          Serial.println("          Range Error");
        }
        
        if(ERR_CHECKSUM & errorByte)
        {
          Serial.println("          Checksum Error");
        }
        
        if(ERR_OVERLOAD & errorByte)
        {
          Serial.println("          Overload Error");
        }
        
        if(ERR_INSTRUCTION & errorByte)
        {
          Serial.println("          Instruction Error");
        }
        
      }//end error check    
    }//end servo id check
    
    //if the values do not match, then there is a problem - usually a '-1' means the servo is not available. any other value means there is some sort of error 
    else
    {
      Serial.print("ERROR: Servo #");
      Serial.print(id);
      Serial.print(" not located. Return Value:");
      Serial.println(idQuery); 
    }
    

  }
  

}






