#include<Wire.h>
const int SW_pin = 2; // digital pin connected to switch output of joystick
const int X_pin = 0; // analog pin connected to X output of joystick
const int Y_pin = 1; // analog pin connected to Y output of joystick
int Joy_y;
int Joy_x;
bool vert, hori;
char s_evt;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int buzr = 3;//the pin of the active buzzer

void setup() {
  // put your setup code here, to run once:
  //joystick setup
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

   // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);

  //setup gyroscope
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //Serial.begin(9600);

  pinMode(buzr,OUTPUT);//initialize the buzzer pin as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  Joy_x = analogRead(X_pin);
  Joy_y = analogRead(Y_pin);
  if(hori == false){
    if(Joy_x >= 900){
      Serial.print("d");
      hori = true;
      vert = false;
    }
    else if(Joy_x <= 100){
      Serial.print("a");
      hori = true;
      vert = false;
    }
  }
  if(vert == false){
    if(Joy_y >= 900){
      Serial.print("s");
      vert = true;
      hori = false;
    }
    else if(Joy_y <= 100){
      Serial.print("w");
      vert = true;
      hori = false;
    }
  }
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  if(vert == false){
    
    if(GyX >= 10000){
      Serial.println("s");
      vert = true;
      hori = false;
    }
    else if(GyX <= -10000){
      Serial.println("w");
      vert = true;
      hori = false;
    }
  }
  if(hori == false){
    if(GyY >= 10000){
      Serial.println("d");
      hori = true;
      vert = false;
    }
    else if(GyY <= -10000){
      Serial.println("a");
      hori = true;
      vert = false;
    }
  }
  delay(30);
   if (Serial.available() > 0) {
    s_evt = Serial.read();
    if(s_evt == 'f')
    {
      hori = false;
      vert = false;
    }
    if(s_evt == 'a'){
      for(int i=0;i<30;i++)
      {
        digitalWrite(buzr,HIGH);
        delay(1);//wait for 1ms
        digitalWrite(buzr,LOW);
        delay(1);//wait for 1ms
      }
    }
   }
  
}
