#include <Filters.h>

float testFrequency = 2;                     // test signal frequency (Hz)


float minimumForKnockFilter = 30;
float minimumForKnockRaw = 200;
int soundSensorVal;

FilterOnePole filterOneLowpass( LOWPASS, testFrequency );   // create a one pole (RC) lowpass filter

void setup() {
  // put your setup code here, to run once:


  Serial.begin( 57600 );    // start the serial port

}

void loop() {
  // put your main code here, to run repeatedly:


   soundSensorVal = analogRead(0);
   filterOneLowpass.input(soundSensorVal);

   if(filterOneLowpass.output() > minimumForKnockFilter)
   {
      Serial.print("Filtered Knock Detected@");
      Serial.println(millis());
   }

   if(soundSensorVal > minimumForKnockRaw)
   {
      Serial.print("Raw Knock Detected@");
      Serial.println(millis());
   }


}
