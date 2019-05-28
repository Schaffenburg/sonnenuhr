#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Stepper.h>

#define UVSENSOR A0
#define REF_3V3 A1
#define ENABLE 12
#define LED 13
#define M1 5
#define M2 6
#define M3 7
#define M4 8

const float inMin = 0.99;
const float inMax = 2.9;
const float outMin = 0.0;
const float outMax = 15.0;

const float idxCoeff = 1.0567;
const float idxOffset = -2.358;

const byte numberOfReadings = 16;

volatile long lastPos = 0;

// Hauttyp 3 Eigenschutzzeit bei UV 8 = 30 min
// baseTime in s bei UV 1 (Hauttyp 3)
const int baseTime = 14400;

const int STEPS_PER_REV = 24;

volatile int poti = 0;

ISR(TIMER1_OVF_vect)
{
  /* Timer1 Interrupt Service Routine */
}

Stepper clockStepper(STEPS_PER_REV, M1, M2, M3, M4);
int speed;
bool continuous;
bool do_display;
int steps;

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

void stepper_disable() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}

void setup(){
  pinMode(UVSENSOR, INPUT);
  pinMode(REF_3V3, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  Serial.begin(9600);

  speed = 30;
  continuous = false;
  do_display = false;

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

void set_clock(int seconds)
{
  int h,m,rest;
  h = seconds/3600;
  rest = seconds - h*3600;
  m = rest/60;
  rest -= m*60;

  Serial.print(" Max.Exp.dauer: ");
  Serial.print(seconds);
  Serial.print(" Sekunden ≙ ");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.print(rest);
  long steps = (long) seconds * ((float) STEPS_PER_REV / 60.0);
  Serial.print(" Turning stepper by ");
  Serial.print(steps);
  Serial.print("-");
  Serial.println(lastPos);

  if (do_display) {
    clockStepper.step(steps-lastPos);
    lastPos = steps;
  }
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
  stepper_disable();

  TCNT1 = 3036;
  sleep_cpu();

  // sleep_mode();
  sleep_disable();
  power_all_enable();

}

void measure() {
  digitalWrite(LED, HIGH);
  digitalWrite(ENABLE, HIGH);
  int uvLevel = averageAnalogRead(UVSENSOR);
  int refLevel = averageAnalogRead(REF_3V3);
  digitalWrite(LED, LOW);
  digitalWrite(ENABLE, LOW);

  float refVoltage = 5.0 * refLevel/1024;
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
  float maxtime = baseTime;

  if (uvindex <= 0.0)
    uvindex = 0.0;
  else if (uvindex > 11)
      uvindex = 11.0;

  if (uvindex >= 1.0)
    maxtime = baseTime / uvindex;

  Serial.print((int)uvindex);
  set_clock(maxtime);
}

void adjust()
{
  steps = 0;
  int incomingByte = Serial.read();
  Serial.print(incomingByte);
  Serial.flush();
  switch (incomingByte)
  {
    case '+':
      speed++;
      Serial.print(" increase speed to ");
      Serial.println(speed);
      break;
    case '-':
      speed--;
      Serial.print(" decrease speed to ");
      Serial.println(speed);
      break;
    case ' ':
      steps = 1;
      break;
    case 's':
      continuous = false;
      Serial.println(" disable contiuous revolution ");
      break;
    case 'c':
      continuous = true;
      Serial.println(" enble contiuous revolution ");
      break;
    case 'm':
      steps = STEPS_PER_REV;
      break;
    case 'h':
      steps = STEPS_PER_REV * 60;
      break;
    case 'i':
      speed *= -1;
      Serial.println(" inverse direction ");
      break;
    case 'u':
      do_display ^= true;
      Serial.print(" toggle UV display: ");
      Serial.println(do_display ? "enabled" : "disabled");
    case '4':
      Serial.print(" init 4 hour position ");
      lastPos = 4*60*STEPS_PER_REV;
    default:
      break;
  }
  if (speed > 0) {
    clockStepper.setSpeed(speed*10);
  } else if (speed < 0) {
    clockStepper.setSpeed(speed*-10);
    steps *= -1;
  }

  if (continuous) {
    if (speed > 0) {
      clockStepper.step(1);
    } else if (speed < 0) {
      clockStepper.step(-1);
    }
  } else if (steps) {
      Serial.print(" step ");

      Serial.println(steps);
      clockStepper.step(steps);
  }
}

void loop() {
  while (Serial.available() > 0) {
    adjust();
  }
  measure();
  enter_sleep();
}
