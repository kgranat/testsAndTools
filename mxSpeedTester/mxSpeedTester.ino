
#include <ax12.h>
#include <BioloidController.h>
#define SERVO_ID 1

int servoPosition;

//BioloidController bioloid = BioloidController(57600);  //create a bioloid object at a baud of 57600MBps
BioloidController bioloid = BioloidController(1000000);  //create a bioloid object at a baud of 1MBps

unsigned long lastReportTime;
int reportInterval = 2500;
unsigned long lastReportTick;

unsigned long lastMXReadTime;
int MXReadInterval = 33;

const int maxSpeedReadings = 5;
int speedReadings[maxSpeedReadings];
int speedReadingsCount;
float avgSpeed;

bool readSaturate = false;

int goalSpeed = 0;
int knobVal;

int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int lastButtonState2 = 0;         // variable for reading the pushbutton status


const int buttonPin = 3;     // the number of the pushbutton pin
const int buttonPin2 = 4;     // the number of the pushbutton pin
const int ledPin =  0;      // the number of the LED pin
 long ticks;
 long ticks2;
 
 long setupEnd;
bool sendPositional = false;

void setup()
{
 
//  //set wheel mode
//  ax12SetRegister2(SERVO_ID, AX_CW_ANGLE_LIMIT_L         , 0); // write two bytes to memory (ADDR, ADDR+1)
//  ax12SetRegister2(SERVO_ID, AX_CCW_ANGLE_LIMIT_L        , 0); // write two bytes to memory (ADDR, ADDR+1)
//  
  //set speed


  delay(100);
  ax12SetRegister2(SERVO_ID, AX_GOAL_SPEED_L             , 50); // write two bytes to memory (ADDR, ADDR+1)
  delay(33);
  
  ax12SetRegister2(SERVO_ID, 6, 1); // write two bytes to memory (ADDR, ADDR+1)

  delay(33);
  ax12SetRegister2(SERVO_ID, 8, 4095); // write two bytes to memory (ADDR, ADDR+1)
  delay(33);
  ax12SetRegister2(SERVO_ID, 30, 0); // write two bytes to memory (ADDR, ADDR+1)

  delay(2500);
  
 
  
  ax12SetRegister2(SERVO_ID, 6, 4095); // write two bytes to memory (ADDR, ADDR+1)

  delay(33);
  ax12SetRegister2(SERVO_ID, 8, 4095); // write two bytes to memory (ADDR, ADDR+1)

  delay(33);
  ax12SetRegister2(SERVO_ID, 30, 1); // write two bytes to memory (ADDR, ADDR+1)
  
  delay(1000);
  //
  

   Serial.begin(38400);
   Serial.println("MX Speed Test");
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);


  pinMode(buttonPin, INPUT);
  
  knobVal = analogRead(0);
  if(knobVal < 256)
  {
    goalSpeed = 10;
  }
  

  else if(knobVal >= 256 && knobVal < 512)
  {
    
    goalSpeed = 50;
  }
  
  else if(knobVal >= 512 && knobVal < 768)
  {
    
    goalSpeed = 100;
  }
  
  else if( knobVal <= 1023)
  {
    
    goalSpeed = 110;
  }
  

   Serial.print("GoalSpeed");
   Serial.println(goalSpeed);

   
  while(digitalRead(2) == HIGH)
  {
    
  }

    ax12SetRegister2(SERVO_ID, AX_GOAL_SPEED_L             , goalSpeed); // write two bytes to memory (ADDR, ADDR+1)
delay(33);
  setupEnd = millis()  ;
 }

void loop()
{
  if(millis() - setupEnd >1000 && sendPositional == false)
  {
      ax12SetRegister2(SERVO_ID, 30, 20480); // write two bytes to memory (ADDR, ADDR+1), set position
      sendPositional = true;

  }

  
//  if(digitalRead(2) == LOW)
//  {
//    Serial.println("RESET");
//    avgSpeed = 0;
//    
//     for(int i = 0; i < maxSpeedReadings; i++)
//     {
//      speedReadings[i] = 0;
////     Serial.print(speedReadings[i] );
////     Serial.print(" ");
////     Serial.println(speedSum);
//     }
//     
//  }


  if(millis() - lastMXReadTime > MXReadInterval)
  {
    if(speedReadingsCount < maxSpeedReadings)
    {
       int tempRead = ax12GetRegister(SERVO_ID,38, 2);
       if(tempRead >= 0)
       {
        speedReadings[speedReadingsCount] = tempRead;        
       }

        speedReadingsCount =  (speedReadingsCount + 1) % maxSpeedReadings ;
      
      }
      else
      {
          readSaturate = true;
      }
     lastMXReadTime = millis();
     
  }
  
 
  
  if(millis() - lastReportTime > reportInterval)
  {
    unsigned long speedSum = 0;
     for(int i = 0; i < maxSpeedReadings; i++)
     {
      speedSum = speedReadings[i] + speedSum;
//     Serial.print(speedReadings[i] );
//     Serial.print(" ");
//     Serial.println(speedSum);
     }
     avgSpeed = (float)speedSum / (float)maxSpeedReadings;
    if(readSaturate == true)
    {
     Serial.print ("Saturate ");
    }
     //Serial.print ("Average Speed @ ");
     Serial.print (millis());
     Serial.print (",");
     Serial.print(ticks);
     Serial.print (",");
     Serial.print(ticks2);
     Serial.print (",");
     Serial.println(avgSpeed);
     lastReportTime = millis();
  }




//  if(ticks - lastReportTick > 10)
//  {
//        unsigned long speedSum = 0;
//     for(int i = 0; i < maxSpeedReadings; i++)
//     {
//      speedSum = speedReadings[i] + speedSum;
////     Serial.print(speedReadings[i] );
////     Serial.print(" ");
////     Serial.println(speedSum);
//     }
//     avgSpeed = (float)speedSum / (float)maxSpeedReadings;
//    
//     //Serial.print ("Average Speed @ ");
//     Serial.print (millis());
//     Serial.print (",");
//     Serial.print(ticks);
//     Serial.print (",");
//     Serial.print(ticks - lastReportTick);
//     Serial.print (",");
//     Serial.print(millis() - lastReportTime);
//     Serial.print (",");
//     Serial.println(avgSpeed);
//     lastReportTick = ticks;
//     lastReportTime = millis();
//  }



// read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState != lastButtonState) {
    // turn LED on:
    
    digitalWrite(ledPin, !digitalRead(buttonPin));
    ticks++;
  } 

  lastButtonState = buttonState;


  if (buttonState2 != lastButtonState2) {
    // turn LED on:
    
    //digitalWrite(ledPin, !digitalRead(buttonPin2));
    ticks2++;
  } 

  lastButtonState2 = buttonState2;


  

}

