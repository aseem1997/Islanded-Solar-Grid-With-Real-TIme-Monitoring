//char dataString[50] = {0};
int a =0,b=0;
float curr=0.0;
float volt=0.0;
int powerd=0;
float powersum=0;
float powerf=0;

void setup() {
Serial.begin(9600); //Starting serial communication
}
  
void loop() {
  //a=random(400,800);
  //sprintf(dataString,"%02X",a); // convert a value to hexa
  powersum=0.0; 
  for(int i=0;i<10000;i++){
  curr=(analogRead(A0)-100.0)/27.5;
  volt=analogRead(A5)*5.0/1024.0*29.0/0.93;
  powersum+=curr*volt;
  }
  powerf=powersum/10000.0;
  
  powerd=ceil(powerf);
  //Serial.println(power);
  Serial.println(powerd);
  b=b+1;
  Serial.println(b);   // send the data
  //delay(1000);                  // give the loop some break
  
}
