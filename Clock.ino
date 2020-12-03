#define BUTTON1 A0
#define BUTTON2 A1
#define BUTTON3 A2
#define LIGHT A5
#include <LiquidCrystal.h>
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
Serial.begin(9600);
lcd.begin(16,2);
pinMode(BUTTON1,INPUT_PULLUP);
pinMode(BUTTON2,INPUT_PULLUP);
pinMode(BUTTON3,INPUT_PULLUP);
pinMode(LIGHT,OUTPUT);
digitalWrite(LIGHT,HIGH);

}
unsigned long previous=0;
int h=0;
int m=0;
int s=0;
int Ah=0;
int Am=1;
int As=0;
int lightMode=0;
void loop() {

showTime(h,m,s,Ah,Am,As);
  if(millis()-previous>=1000)
  {
   previous = millis();
   s++;
   lcd.clear();
     
      if(digitalRead(BUTTON3))
      {
        if(!digitalRead(BUTTON1)){h++;}
        if(!digitalRead(BUTTON2)){m++;}
      }

      if(!digitalRead(BUTTON3))
      {
        if(!digitalRead(BUTTON1)){Ah++;}
        if(!digitalRead(BUTTON2)){Am++;}
      }

      if(alarm(h,m,Ah,Am))
      {
        if(lightMode==0){lightMode=1;digitalWrite(LIGHT,LOW);}
        else{lightMode=0;digitalWrite(LIGHT,HIGH);}
      }
   }
}
//Wyswietlanie danych na ekran LCD 2x16
void showTime(int& H, int& M, int& S,int& AH, int& AM, int& AS )
{
//ustawienia logiki
if(S==60){ S=0;M++;}
if(M==60){ M=0;H++;}
if(H==24){H=0;M=0;S=0;}
if(AS==60){ AS=0;AM++;}
if(AM==60){ AM=0;AH++;}
if(AH==24){AH=0;AM=0;AS=0;}

  //Wyswietlanie zegarka
  lcd.setCursor(4,0);
  if(H<10){lcd.print(0);}
  lcd.print(H);
  lcd.print(":");
  if(M<10){lcd.print(0);}
  lcd.print(M);
  lcd.print(":");
  if(S<10){lcd.print(0);}
  lcd.print(S);

//Wyswietlanie alarmu
  lcd.setCursor(4,1);
  if(AH<10){lcd.print(0);}
  lcd.print(AH);
  lcd.print(":");
  if(AM<10){lcd.print(0);}
  lcd.print(AM);
  lcd.print(":");
  if(AS<10){lcd.print(0);}
  lcd.print(AS);
 
}



bool alarm(int& H, int& M, int& AH, int& AM)
{
if(H==AH && M==AM ) {return true;}
else {return false;}
}
