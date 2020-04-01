////  ATMEGA328p DIP  /////

#include <SoftwareSerial.h>


SoftwareSerial Serial2(17, 18);

byte NESData = 13;       
byte NESLatch = 12;         
byte NESClock = 11;

byte NESButtonData;      
byte NESButtonNew;

int specialLoop1 = 0;
int i = 0;
int semi1 = 0;
int semi2 = 0;
int semiStart = 0;
 
void setup() {

    Serial.begin(9600); 
    Serial.println("Serial connected");
    
    Serial2.begin(9600);
    Serial2.println("Serial connected");
    
    pinMode(NESLatch, OUTPUT);  
    pinMode(NESClock, OUTPUT); 
    pinMode(NESData, INPUT);    
 
    pinMode(2,OUTPUT);  // up
    pinMode(3,OUTPUT);  // DOWN
    pinMode(4,OUTPUT);  // LEFT
    pinMode(5,OUTPUT);  // RIGHT
    pinMode(6,OUTPUT);  // 1
    pinMode(7,OUTPUT);  // 2
    pinMode(8,OUTPUT);  // START
    pinMode(9,OUTPUT);  // RESET
    
    pinMode(10,OUTPUT);  // Controller Power
    digitalWrite(10,HIGH);
}
 
void loop() {       

    specialLoop1 = 0;
    i = 0;
                  
    ReadingNESControllerData();         
    NESButtonNew = NESButtonData;
   
    int button2 = bitRead(NESButtonNew,0);
    int button1 = bitRead(NESButtonNew,1);
    int buttonReset = bitRead(NESButtonNew,2);
    int buttonStart = bitRead(NESButtonNew,3);
    int buttonUP = bitRead(NESButtonNew,4);
    int buttonDown = bitRead(NESButtonNew,5);
    int buttonLeft = bitRead(NESButtonNew,6);
    int buttonRight = bitRead(NESButtonNew,7);

    Serial.print(button2);
    Serial.print(button1);
    Serial.print(buttonReset);
    Serial.print(buttonStart);
    Serial.print(buttonUP);
    Serial.print(buttonDown);
    Serial.print(buttonLeft);
    Serial.print(buttonRight);
    
    Serial2.print(button2);
    Serial2.print(button1);
    Serial2.print(buttonReset);
    Serial2.print(buttonStart);
    Serial2.print(buttonUP);
    Serial2.print(buttonDown);
    Serial2.print(buttonLeft);
    Serial2.print(buttonRight);

    
   if(button2 == 0){
    Serial.print(" 2 ");
    digitalWrite(7,LOW);
      }
    if(button2 == 1){
    digitalWrite(7,HIGH);
      }  
      
    if(button1 == 0){
    Serial.print(" 1 ");
    digitalWrite(6,LOW);
      }
      if(button1 == 1){
    digitalWrite(6,HIGH);
      }

      
    if(buttonStart == 0){
    Serial.print(" Start ");
    digitalWrite(8,LOW);
      }
    if(buttonStart == 1){
    digitalWrite(8,HIGH);
      }
      

    if(buttonReset == 0){
    Serial.print(" Reset ");
    digitalWrite(9,LOW);
      }
     
    if(buttonReset == 1){
    digitalWrite(9,HIGH);
      }
  
    if(buttonUP == 0){
    Serial.print(" UP ");
    digitalWrite(2,LOW);
      }
    if(buttonUP == 1){
    digitalWrite(2,HIGH);
      }

    if(buttonDown == 0){
    Serial.print(" Down ");
    digitalWrite(3,LOW);
      }
      if(buttonDown == 1){
      digitalWrite(3,HIGH);
      }

    if(buttonLeft == 0){
    Serial.print(" Left ");
    digitalWrite(4,LOW);
      }
      if(buttonLeft == 1){
      digitalWrite(4,HIGH);
      }

    if(buttonRight == 0){
    Serial.print(" Right ");
    digitalWrite(5,LOW);
      }
      if(buttonRight == 1){
    digitalWrite(5,HIGH);
      }

////////// Special Codes

  if(button1 == 0){
      if(button2 == 0){
          if(buttonStart == 0){
            
            specialLoop1 = 1;

            while(i < 30){
            Serial.println("in while loop");

    ReadingNESControllerData();         
    NESButtonNew = NESButtonData;
   
    int button2 = bitRead(NESButtonNew,0);
    int button1 = bitRead(NESButtonNew,1);
    int buttonReset = bitRead(NESButtonNew,2);
    int buttonStart = bitRead(NESButtonNew,3);
    int buttonUP = bitRead(NESButtonNew,4);
    int buttonDown = bitRead(NESButtonNew,5);
    int buttonLeft = bitRead(NESButtonNew,6);
    int buttonRight = bitRead(NESButtonNew,7);


   if(buttonUP == 0){
      if(semi1 == 0){
    Serial.println("semifire 1 activated");
    semi1 = 1;
    i = 301;
      }
    else{
      semi1 = 0;
      Serial.println(" Semifire 1 is off");
      i = 301;
      }
              delay(1);
              i++;
              }

      if(buttonDown == 0){
      if(semi2 == 0){
    Serial.println("semifire 2 activated");
    semi2 = 1;
    i = 301;
      }
    else{
      semi2 = 0;
      Serial.println(" Semifire 2 is off");
      i = 301;
      }
              delay(1);
              i++;
              }
   if(buttonLeft == 0){
      if(semiStart == 0){
    Serial.println("semifire Start activated");
    semiStart = 1;
    i = 301;
      }
    else{
      semiStart = 0;
      Serial.println(" Semifire Start is off");
      i = 301;
      }
              delay(1);
              i++;
              }
          }
        }
    }
  }
/////////////////////////////////////////////////////////////////////////////

    if(semi1 == 1){
      Serial.println("Semi-fire 1 is on");
       digitalWrite(6,HIGH);
      }
    if(semi2 == 1){
      Serial.println("Semi-fire 2 is on");
       digitalWrite(7,HIGH);
      }
          if(semiStart == 1){
      Serial.println("Semi-fire Start is on");
       digitalWrite(8,HIGH);
      }

    if( button2 == 1 && 
    button1 == 1 && 
    buttonStart == 1 && 
    buttonReset == 1 && 
    buttonUP == 1 && 
    buttonDown == 1 && 
    buttonLeft == 1 &&  
    buttonRight == 1 ){
    Serial.print(" Nothing Pressed ");
      }
  
    Serial.println(" ");
    delay(2);
}

 
void ReadingNESControllerData(){            
    digitalWrite(NESLatch, HIGH);       
    digitalWrite(NESLatch, LOW);      
    for(int x=0; x<=7; x++){         
        bitWrite(NESButtonData,x,digitalRead(NESData)); 
        digitalWrite(NESClock, HIGH);                 
        digitalWrite(NESClock, LOW);                 
}
}
