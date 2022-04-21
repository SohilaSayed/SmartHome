#include<LiquidCrystal.h>
#include<Servo.h>
Servo servo_m;
Servo mysrv;
const int trig = 0;
const int echo = 1;
int servo_mpin=5;
int button1=3;
int button2=4;
int button3=2;
int i =0;
int count=0;
int ldr=A5;
int led=3;
String key="";
String mypass="bca";
LiquidCrystal lcd(13,12,11,10,9,8);
int temp=A0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(temp,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode (A3,INPUT);
  pinMode (A2,INPUT);
  pinMode (A1,INPUT);
  servo_m.attach(6);
  servo_m.write(0); 
  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
}
void loop() {
  int value = analogRead(A0);
  float mv=value/1023.0;
  mv=mv*5;
  mv=mv-0.5;
  mv=mv*1000;
  float cl=mv/10;
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(cl);
  delay(100);
 // Serial.println(cl);
if(cl>30){  
  digitalWrite(7,HIGH);
  digitalWrite(2,LOW); 
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
else{
  digitalWrite(2,LOW);
  digitalWrite(7,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
 int a=digitalRead (A3);
 int b=digitalRead (A2);
 int c=digitalRead (A1);
  if(a == HIGH)
  {
    key = key + 'a';
    Serial.println("a");
    i++;
    a=0;
  }
  else if (b==1)
  {
    key =key +'b';
    Serial.println("b");
    i++;
    b=0;
  }
    
  else if (c==1)
  {// key = b
    Serial.println("c");
    key =key+'c';   // key = c
//  pass="";
    i++;
    c=0;
  }
  if (i==3)
  {
  Serial.println(key);
  delay (1000);
   
    if(key==mypass)
    {
      Serial.println("Correct Pattern");
      lcd.setCursor(0,1);
      lcd.print("Correct Pattern");
      servo_m.write(90);
      delay(2000);
      servo_m.write(0);
    }
     else
    {
       Serial.println("Wrong Pattern");
       lcd.setCursor(0,1);
       lcd.print("Wrong Pattern");
       servo_m.write(0);
    }
    i= 0;
    key="";
  }
  
  float vl=analogRead(ldr);
  vl=(vl/1023.0);
  float L=vl*255;
  if(vl>=0.4){
    analogWrite(led, L);
  }
  else{
    analogWrite(led, 0);
  }
  
delay(2000);
}
