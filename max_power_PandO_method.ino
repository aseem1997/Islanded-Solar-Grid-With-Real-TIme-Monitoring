
float v1=0;
float v2=0;

float i1=0;
float i2=0;

float p1=0;
float p2=0;
byte duty=0;

float v2sum=0;
float i2sum=0;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

}

void loop()
{// put your main code here, to run repeatedly:
  v2sum=0,i2sum=0;
  for(int i=0;i<10;i++)
  {
    v2sum+=5.0/1023*analogRead(A0)/0.02;
    i2sum+=5.0/1023*analogRead(A1)/0.4;
    delayMicroseconds(5);
  }
  v2=v2sum/10;
  i2=i2sum/10;
  Serial.print("v2 ");
  Serial.print(v2);
  Serial.print(" i2 ");
  Serial.print(i2);
  p2=v2*i2;
  Serial.print("        p2 ");
  Serial.print(p2);
  Serial.print("             v1 ");
  Serial.print(v1);
  Serial.print(" i1 ");
  Serial.print(i1);
  Serial.print(" p1        ");
  Serial.print(p1);
  
  
 
  
  if( (v2>v1 && p2>p1) || (v2<v1 && p1>p2))
  {
   duty=duty+2;
  }
  else
  {
    duty=duty-2;
  }
  v1=v2;
  p1=p2;

  if(duty>204)
  {
    duty=204;
  }
  analogWrite(3,duty);
  delay(10);
  Serial.print("     the duty is: ");
  Serial.println(duty);
  
}
