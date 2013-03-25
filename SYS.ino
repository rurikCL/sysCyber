/*
Sys Cyber
0.8
*/

//#include <TM1638.h>
#include <stdio.h>
#include <stdlib.h>
#include <Servo.h>

 int pinX = A4; //JoystickX input
 int pinY = A5; //JoystickY input
 int pinSw = 4; //switch input
 
 const int servo1 = 3; // ServoX output
 const int servo2 = 5; // ServoY output
 const int pinLaser = 6;
 
 int posX; //Initial Position of ServoX
 int posY; //Initial Position of ServoY

 int i; 
 int mode = 0;
 int buttonState;
 
 Servo servoX;  // ServoX Object
 Servo servoY;  // ServoY Object
 
void setup() {
  Serial.begin(9600);
  servoX.attach(servo1);  // attaches the servo
  servoY.attach(servo2);  // attaches the servo
  
  pinMode(pinSw, INPUT);  
}

void loop() {

  buttonState = digitalRead(pinSw);
  if (buttonState == HIGH) {     
    // turn LED on:    
    mode++;
    if(mode>3) mode = 1;
    delay(10);  
  } 
  if(mode == 1) analogWrite(pinLaser,100);
  else if(mode == 2) analogWrite(pinLaser,150);
  else if(mode == 3) analogWrite(pinLaser,255);
  
      int ejeX = map(analogRead(pinX), 0, 1023, 0, 16);     
      int ejeY = map(analogRead(pinY), 0, 1023, 0, 16);
      if(ejeX > 10) posX+=2;
      if(ejeY > 10) posY+=2;
      if(ejeX < 6) posX-=2;
      if(ejeY < 6) posY-=2;
      
      if(posX < 0) posX = 0;
      if(posX > 180) posX = 180;
      if(posY < 0) posY = 0;
      if(posY > 180) posY = 180;
      
      servoX.write(posX);
      delay(10);
      servoY.write(posY);
             
      outputJoystick();
   
}


void outputJoystick(){

    Serial.print(posX);
    Serial.print ("---"); 
    Serial.print(posY);
    Serial.print ("--------------");
    //Serial.println(namePos);
}
