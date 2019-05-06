#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>

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
 
ISR(TIMER1_OVF_vect)
{
  /* Timer1 Interrupt Service Routine */
}

//Timer_1 initialisieren
void init_timer ()
{
  /* konfiguriere Timer */
  TCCR1A = 0x00;  // normal operation
  TCCR1B = 0;
  TCNT1  = 3036;  // preload counter
  TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler: 1024
  TIMSK1 |= (1 << TOIE1);  // enable interrupt on timer
}

void setup(){
  pinMode(UVSENSOR, INPUT);
  pinMode(REF_3V3, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  Serial.begin(9600);

  init_timer ();

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

void enter_sleep(void)
{
  delay (100); // wait for UART
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();

  /* AVR müde, AVR schlafen */
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();

  TCNT1 = 3036;
  sleep_cpu();

  // sleep_mode();
  sleep_disable();
  power_all_enable();
}

void loop() {
  measure();
  enter_sleep();
}
