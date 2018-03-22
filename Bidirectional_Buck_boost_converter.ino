#define vbat A1
#define vload A2
int Buck_switch = 5;
int Boost_switch = 6;
int mppt_int = 2;
int power_shortage = 13;
void setup() {
pinMode(mppt_int,OUTPUT);
pinMode(power_shortage,OUTPUT);
digitalWrite(mppt_int,LOW);
digitalWrite(power_shortage,LOW);
setPwmFrequency(5,8);
setPwmFrequency(6,8);
}

void loop() {
  if(analogRead(vload)>530)    //outputp power is higher than load
   {
    if(analogRead(vbat)>162)  //13.5V is full charge voltage at 100% SOC
      { //MPPT is not used
        digitalWrite(mppt_int,HIGH) 
        }
    else
      { //charging of battery
        analogWrite(Buck_switch,??);
        }
    }
   else
    {
       if(analogRead(vbat<114))
        { //power shortage
          digitalWrite(power_shortage,HIGH);
          
        }
        else
          { //discharging of battery
            analogWrite(Boost_switch,??);
          }
    }
    
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
