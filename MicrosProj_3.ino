#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define ENABLE 5
#define CW 3
#define CCW 4
#define button 2
volatile byte updatelcd = 0;
volatile byte button_press = 0;
volatile byte upperdown = 0;
int counter = 0;
int SPEED;
void FLIPBUTTON(){
  button_press = 1;
  //reti();
}
ISR(TIMER1_OVF_vect){
  updatelcd = 1;
  if(counter <= 59)
  {
    counter++;
  }
  else{
    counter = 0;
    SPEED = 80;  
  }
}

void updateSPEED(){
  if(!upperdown){
    switch(SPEED){
      case 80:
        SPEED = 128;
        break;
      case 128:
        SPEED = 180;
        break;
      case 180:
        SPEED = 225;
        upperdown = 1;
        break;
    }
  }
  else{
    switch(SPEED){
      case 225:
        SPEED = 180;
        break;
      case 180:
        SPEED = 128;
        break;
      case 128:
        SPEED = 80;
        upperdown = 0;
        break;
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  pinMode(ENABLE,OUTPUT);
  pinMode(CW,OUTPUT);
  pinMode(CCW,OUTPUT);
  pinMode(button, INPUT);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= 0b00000100;
  TIMSK1 |= 0b00000001;
  interrupts();
  attachInterrupt(digitalPinToInterrupt(button), FLIPBUTTON, RISING);
  sei(); // Enable global interrupts
  digitalWrite(CW,HIGH); //one way
  digitalWrite(CCW,LOW);
  SPEED = 80;
  upperdown = 0;
  do{
    dt = clock.getDateTime();
  }while(dt.second != 0);
}


void loop() {
  // put your main code here, to run repeatedly:
  if(counter >= 30){
    SPEED = 0;
    analogWrite(ENABLE, 0);
  }
  else{
    if((counter % 3) == 0 && counter != 0){
      updateSPEED();
    }
    analogWrite(ENABLE, SPEED);
  
  }
  if(updatelcd){
    //noInterrupts();
    dt = clock.getDateTime();
    lcd.setCursor(0, 0);
    lcd.print("TIME: ");
    lcd.print(dt.hour);
    lcd.print(":");
    lcd.print(dt.minute); 
    lcd.print(":");
    lcd.print(dt.second);
     lcd.setCursor(0, 1);
    lcd.print("RPM:");
    switch (SPEED){
      case 225:
        lcd.print("FULL");
        break;
     case 180:
        lcd.print("3/4 ");
        break;
     case 128:
        lcd.print("1/2 ");
        break;
     case 80:
        lcd.print("1/4 ");
        break;
     default:
        lcd.print("0   ");
        break;
    }
    lcd.print(" "); 
    if(digitalRead(CW)){
      lcd.print("CW ");
    }
    else{
      lcd.print("CCW");
    }
    updatelcd = 0;
    TCNT1 = 0;
    
  }
  
  if(button_press){
    noInterrupts();
    if(SPEED == 0){
      digitalWrite(CW, !digitalRead(CW));
      digitalWrite(CCW, !digitalRead(CCW));
    }
    else{
      analogWrite(ENABLE, 0);
      digitalWrite(CW, !digitalRead(CW));
      digitalWrite(CCW, !digitalRead(CCW));
      analogWrite(ENABLE, SPEED);
    }
    button_press = 0;
    interrupts();
  }
}
