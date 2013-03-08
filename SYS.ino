/*
Sys Cyber
0.7
*/

#include <TM1638.h>
#include <stdio.h>
#include <stdlib.h>
#include <Servo.h>

 int pinX = A4; //ServoX input
 int pinY = A5; //ServoY input
 int pinSw = A3;
 int posX; //Initial Position of ServoX
 int posY; //Initial Position of ServoY
 char* name; //Data for 7s
 int i;
 String namePos;
 int mode = 0;
 const int servo1 = 3; // ServoX output
 const int servo2 = 5; // ServoY output
 
 Servo servoX;  // ServoX Object
 Servo servoY;  // ServoY Object
 
 //This defines a module with data on pin 8, clock on pin 9 and strobe on pin 7.
 TM1638 module(8, 9, 7);

void setup() {
  Serial.begin(9600);
  servoX.attach(servo1);  // attaches the servo
  servoY.attach(servo2);  // attaches the servo
  module.setupDisplay(true, 1);
  name = "Cyber 06";
  module.setDisplayToString(name,0b00001000);
 
}

void loop() {
 
  byte keys = module.getButtons();
  module.setLEDs(0xFF00);
  
  // Modo rapido, con coordenadas
   if (mode == 1){
      posX = map(analogRead(pinX), 0, 1023, 0, 180);
      servoX.write(posX);
      posY = map(analogRead(pinY), 0, 1023, 0, 180);
      delay(50);
      servoY.write(posY);
 
      namePos = String(posX,DEC) + "-" + String(posY,DEC) + "   ";
      
      //outputJoystick();
      module.setDisplayToString(namePos);
   }

   // Modo presicion
   if (mode == 2){
      int ejeX = map(analogRead(pinX), 0, 1023, 0, 16);     
      int ejeY = map(analogRead(pinY), 0, 1023, 0, 16);
      if(ejeX > 10) posX+=5;
      if(ejeY > 10) posY+=5;
      
      servoX.write(posX);
      delay(10);
      servoY.write(posY);
      delay(50);
   }
   
   if (mode==3){
      for(i=0;i<8;i++){ module.setLED(0xF, i); delay(100);} 
   }
   if (mode==4){
      //digitalWrite(pinSw, HIGH);
      int ejeX = map(random(0,1023), 0, 1023, 0, 180);     
      int ejeY = map(random(0,1023), 0, 1023, 0, 180);
           
      servoX.write(ejeX);
      delay(10);
      servoY.write(ejeY);
      delay(1000);
   }
   
   
  if(keys == 0b10000000){
   name = "Mode1 ON";
   module.setDisplayToString(name,0b00010000);
   delay(300);
   mode = 1;
   module.clearDisplay();
  }
  if(keys == 0b01000000){
   name = "Mode2 ON";
   module.setDisplayToString(name,0b00010000);
   delay(300);
   posX = 90;
   posY = 45;
   mode = 2;
  }
  if(keys == 0b00100000){
   name = "Mode3 ON";
   module.setDisplayToString(name,0b00010000);
   delay(300);
   mode = 3;
  }
  if(keys == 0b00010000){
   name = "Mode4 ON";
   module.setDisplayToString(name,0b00010000);
   delay(300);
   mode = 4;
  }
}
void outputJoystick(){

    Serial.print(posX);
    Serial.print ("---"); 
    Serial.print(posY);
    Serial.print ("--------------");
    Serial.println(namePos);
}
