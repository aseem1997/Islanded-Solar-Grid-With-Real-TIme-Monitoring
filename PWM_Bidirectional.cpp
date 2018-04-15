#include "mbed.h"

PwmOut led1(PB_4);
AnalogIn sense(PA_1);
PwmOut led2(PB_3);
float Kp_set = 0.00005f;
float kp_set = 0.0005f;
float Kp = 0.0;
int flag=1;

int main() 
{
    
    led1.period(0.00001f);
    led2.period(0.00001f);
   // led2.write(0.40f);
    while(1)
    {
        float duty_boost=0.15f;
         
      
    while(flag==1)
    {  
          
        led2.write(0.0f);
        uint16_t setpoint = 0xA0B3;
        double error_per = 0.0f;
        uint16_t bus_voltage = sense.read_u16();
        for(int i=0;i<10;i++)
        {
        uint16_t bus_voltage = sense.read_u16();   
        int32_t error = setpoint - bus_voltage;
        error_per += (double(setpoint)-double(bus_voltage))/double(setpoint)*100.0f;   
        }
        error_per = error_per/10.0f;
       if (duty_boost <= 0.700f)
        {
             
             if (error_per > 5 || error_per < (-5))
                Kp = Kp_set*10;
            
            else
                Kp = Kp_set;
        
           // if (error_per > 2 ||error_per < (-2))
            //{
                duty_boost = duty_boost + Kp*error_per;
                led1.write(duty_boost);
           // }   
            
        }  

        else duty_boost = 0.700f;
       // printf("%f  %f \n ",error_per,duty_boost);
        if(error_per<=0.0f&&duty_boost<=0.2) 
        {
          //printf("buck hona chahiye");
          flag=0;
          led1.write(0.0f);
         } 
           
    // float Voltagef = float(bus_voltage)*3.3f;  
    //  printf("  %f  %d \n", Voltagef , flag);                                       
                                                    
     } 
    
     float duty_buck=0.0f;
     while(flag==0)
    {    
        led1.write(0.0f);
        
        //printf("buck ho rha hai");
        uint16_t setpoint = 0xA0B3;
        float error_per = 0.0f;
         uint16_t bus_voltage = sense.read_u16();
        for(int i=0;i<5;i++)
        {
        uint16_t bus_voltage = sense.read_u16();   
        int32_t error = bus_voltage - setpoint;
        error_per += (float(bus_voltage)-float(setpoint))/float(setpoint)*100.0f;   
        }
        error_per = error_per/5.0f;
   
            if (error_per > 5 || error_per < (-5))
                Kp = kp_set*10;
            
            else
                Kp = kp_set;
        
            //if (error_per > 2 ||error_per < (-2))
            
          duty_buck = duty_buck + Kp*error_per;
          led2.write(0.4f);
             
                                     
     //  if(duty_buck>1)duty_buck=1; 
       // printf("%f  dbk= %f  \n",error_per,duty_buck)    ;    
        if(error_per<0.0f&&duty_buck<0.29 )
        {
            flag=1;
            led2.write(0.0f);
        }
     // float Voltagef = float(bus_voltage)*3.3f;  
     // printf("  %f  %d \n", Voltagef , flag);  
      //  printf(" %f    %x    %d    %f \n", duty, input, error, error_per);                                           
                                                    
    }
    
  
 }
}