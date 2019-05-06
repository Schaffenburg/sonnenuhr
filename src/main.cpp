#include <Arduino.h>

#define UVSENSOR A0
#define REF_3V3 A1
#define ENABLE 12
#define LED 13

const float inMin = 0.99;
const float inMax = 2.9;
const float outMin = 0.0;
const float outMax = 15.0;

const float idxCoeff = 1.0567;
const float idxOffset = -2.358;
 
const byte numberOfReadings = 8;
 
void setup(){
  pinMode(UVSENSOR, INPUT);
  pinMode(REF_3V3, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sonnenuhr Start");
}
 
int averageAnalogRead(int pinToRead){
  unsigned int runningValue = 0; 
  for(int x = 0 ; x < numberOfReadings ; x++){
    unsigned int val = analogRead(pinToRead);
    runningValue += val;
  } 
  return(runningValue / numberOfReadings);  
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void measure() {
  digitalWrite(LED, HIGH);
  digitalWrite(ENABLE, HIGH);
  int uvLevel = averageAnalogRead(UVSENSOR);
  int refLevel = averageAnalogRead(REF_3V3);
  digitalWrite(LED, LOW);
  digitalWrite(ENABLE, LOW);

  float refVoltage = 3.3 * refLevel/1024;
  float outputVoltage = 3.3 / refLevel * uvLevel;
  Serial.print(" Ref Voltage: ");
  Serial.print(refVoltage);
  Serial.print(" Sensor Voltage: ");
  Serial.print(outputVoltage);
  
  float uvIntensity = mapfloat(outputVoltage, inMin, inMax, outMin, outMax);
 
  Serial.print(" UV Intensität: ");
  Serial.print(uvIntensity);
  Serial.print(" mW/cm² ≙ UV Index:");
  float uvindex = (idxCoeff * uvIntensity) + idxOffset;
  if (uvindex < 0)
    uvindex = 0.0;
  else if (uvindex > 11)
    uvindex = 11.0;
  Serial.println((int)uvindex);
}

void loop() {
  measure();
  enter_sleep();
}
