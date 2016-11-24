#include <Servo.h>
#include <PS2X_lib.h>  //for v1.6

int pos = 15;
int servoSpeed = 8;

int leftPad = 0;
int rightPad = 0;

int leftPin1 = 2;
int leftPin2 = 3;
int leftSpeedPin = 5;

int rightPin1 = 4;
int rightPin2 = 7;
int rightSpeedPin = 6;

Servo kippi;
PS2X ps2x;

void setup(){
 
  pinMode(leftPin1, OUTPUT);
  pinMode(leftPin2, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightPin1, OUTPUT);
  pinMode(rightPin2, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  
  kippi.attach(9);
  kippi.write(pos);
  Serial.begin(57600);
  delay(300);
  ps2x.config_gamepad(13,11,10,12,false,false);
}

void loop() {
    ps2x.read_gamepad(false, 0);
    
    leftPad = ps2x.Analog(PSS_LY);
    rightPad = ps2x.Analog(PSS_RY);
    
    if(leftPad > 127) {
      digitalWrite(leftPin1, LOW); 
      digitalWrite(leftPin2, HIGH);
      analogWrite(leftSpeedPin, leftPad);
    }
    if(leftPad < 127) {
      digitalWrite(leftPin1, HIGH); 
      digitalWrite(leftPin2, LOW);
      analogWrite(leftSpeedPin, 255 - leftPad);
    }
    if(leftPad == 127) {
      analogWrite(leftSpeedPin, 0);
    }
    
    if(rightPad > 127) {
      digitalWrite(rightPin1, HIGH); 
      digitalWrite(rightPin2, LOW);
      analogWrite(rightSpeedPin, rightPad);
    }
    if(rightPad < 127) {
      digitalWrite(rightPin1, LOW); 
      digitalWrite(rightPin2, HIGH);
      analogWrite(rightSpeedPin, 255 - rightPad);
    }
    if(rightPad == 127) {
      analogWrite(rightSpeedPin, 0);
    }
    
    if(ps2x.Button(PSB_L1)){
      if(pos > 0) {
        pos = pos - servoSpeed;
        if(pos < 0) {
          pos = 0;
        }
        kippi.write(pos);
      }
    }

    if(ps2x.Button(PSB_R1)){
       if(pos < 180) {
        pos = pos + servoSpeed;
        if(pos > 180) {
          pos = 180;
        }
        kippi.write(pos);
      }
    }   
    delay(50);  
}

