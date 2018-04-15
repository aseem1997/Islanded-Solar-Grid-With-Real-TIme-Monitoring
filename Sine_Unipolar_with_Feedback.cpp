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
Serial pc(USBTX, USBRX);
float kp=0.0f;
float ki=0.0f;
float kd=0.0f;


//Frequency of Pulse Width Modulated signal in Hz
#define PWM_FREQ          5000

//PWM pin
PwmOut PwmPin1 (p22);
PwmOut PwmPin2 (p21);
AnalogIn sense(p20);
float vref=0.3f;
float mf=0.4;
//Heartbeat LED
DigitalOut myled(LED1);

int printcounter=0;
float vrms=0.0f;
void mf_updater()
{
  mf+=(vref-vrms)*0.1f;
  if(mf>1.0f)
  mf=1.0f;
  if(++printcounter==500)
  {
  pc.printf("vrms = %f , mf = %f , error = %f \n ",vrms*3.3f,mf,(vref-vrms));
  printcounter=0;
  }
}


//Ticker to update the PWM dutycycle
Ticker pwm_ticker;
int counter=0;
float sine_fdbk,sum=0.0f;
//Ticker calls this fucntion to update the PWM dutycycle
int sampling_count; 
void pwm_duty_updater() {
  if(++counter==200)
   {
     mf_updater();
     counter=0;
   }
 static int idx=0;
  PwmPin1.write(sine_duty1[idx]*mf);// Set the dutycycle % to next value in array
    //PwmPin1.write(0.5f);
  PwmPin2.write(sine_duty2[idx]*mf);
  //PwmPin2.write(0.5f);
  idx++;                         // Increment the idx
   
   
   sine_fdbk=sense.read();
   sum+=(sine_fdbk*sine_fdbk);
   if(idx == SINE_STEPS)
   {
       vrms=sqrt(sum/float(SINE_STEPS));
       idx=0;
       sum=0.0f;
    }

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

