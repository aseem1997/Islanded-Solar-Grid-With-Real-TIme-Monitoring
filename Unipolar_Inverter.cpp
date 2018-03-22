#include "mbed.h"

//Number of dutycycle steps for output wave
#define SINE_STEPS        200
//Frequency of output sine in Hz
#define SINE_OUT_FREQ     50

//Constants to compute the sine waveform
#define PI                 3.141592f
#define SINE_STEPS_RAD    (2.0f * PI / (float)SINE_STEPS)

//Table to generate the sine waveform using dutycycles
float sine_duty1[SINE_STEPS];
float sine_duty2[SINE_STEPS];


//Frequency of Pulse Width Modulated signal in Hz
#define PWM_FREQ          5000

//PWM pin
PwmOut PwmPin1 (p22);
PwmOut PwmPin2 (p21);

//Heartbeat LED
DigitalOut myled(LED1);


//Ticker to update the PWM dutycycle
Ticker pwm_ticker;

//Ticker calls this fucntion to update the PWM dutycycle
void pwm_duty_updater() {
  static int idx=0;
  if(sine_duty1[idx]!=0)
  PwmPin1.write(sine_duty1[idx]*0.8f);// Set the dutycycle % to next value in array
  //PwmPin1.write(0.5f);
    
  if(sine_duty2[idx]!=0)
  PwmPin2.write(sine_duty2[idx]*0.8f);
  //PwmPin2.write(0.5f);
  idx++;                         // Increment the idx
  if (idx == SINE_STEPS) idx=0;  // Reset the idx when teh end has been reached  

}
  
int main() {
  int i;
  
  // Init the duty cycle array
  for (i=0; i<100; i++) {
    sine_duty1[i] = ( sin(i * SINE_STEPS_RAD)) / 1.0;  // convert sine (-1.0 .. +1.0) into dutycycle (0.0 .. 1.0)
  }  
  
  for (i=100; i<200; i++){
    sine_duty1[i]=0;
   }
  for(i=0;i<100;i++){
    sine_duty2[i]=0;
  }  
  for(i=0;i<100;i++){
    sine_duty2[i+100] = ( sin(i * SINE_STEPS_RAD) ) / 1.0f;  // convert sine (-1.0 .. +1.0) into dutycycle (0.0 .. 1.0)
  } 
 
    
  // Set PWM frequency to 200 KHz (period = 5 us)
  PwmPin1.period( 1.0f / (float) PWM_FREQ);
  PwmPin2.period( 1.0f / (float) PWM_FREQ);

  // Init the Ticker to call the dutycyle updater at the required interval
  // The update should be at (SINE_STEPS * SINE_OUT_FREQ) 
  pwm_ticker.attach(&pwm_duty_updater, 1.0f / (float)(SINE_STEPS * SINE_OUT_FREQ));

  while(1){ //infinite loop
    myled = !myled; 
    wait(0.5);  
  }
       
} 

