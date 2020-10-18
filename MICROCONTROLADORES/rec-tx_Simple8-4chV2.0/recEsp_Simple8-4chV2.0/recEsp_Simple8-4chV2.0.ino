/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>
#include <EEPROM.h>
#define espacoEEPROM 1000   //1Kb para todos os Arduinos com ATMega328P

#define botGravPin   3
#define led1Pin      9
#define led2Pin     10
#define led3Pin     11
#define led4Pin     12
#define buzPin      13
#define ledSinal     8  

#define Pin01     A0
#define Pin02     A1
#define Pin03     A2
#define Pin04     A3

int addr = 0;
byte leitura;
long int value;
long   variavelLongch1;
long   variavelLongch2;
long   variavelLongch3;
long   variavelLongch4;
long   variavelLongch5;
long   variavelLongch6;
long   variavelLongch7;
long   variavelLongch8;

bool flagled1=false;
bool flagled2=false;
bool flagled3=false;
bool flagled4=false;

void EEPROMWriteLong(int address, long value); //4 Bytes
long EEPROMReadLong(int address);

void controleRemoto();
void EEPROMWriteLong();
long EEPROMReadLong();
void gravar();

RCSwitch mySwitch = RCSwitch();

void setup() {
   Serial.begin(115200);   
   Serial.println("serial iniciada");
    
   variavelLongch1 = EEPROMReadLong(1);     //Posicao 1, 2, 3 e 4 da EEPROM
   variavelLongch2 = EEPROMReadLong(5);     //Posicao 5, 6, 7 e 8 da EEPROM
   variavelLongch3 = EEPROMReadLong(9);     //Posicao 9, 10,11 e 12 da EEPROM
   variavelLongch4 = EEPROMReadLong(13);     //Posicao 13, 14, 15 e 16 da EEPROM
   variavelLongch5 = EEPROMReadLong(17);     //Posicao 17, 18, 19 e 20 da EEPROM
   variavelLongch6 = EEPROMReadLong(21);     //Posicao 21, 22, 23 e 24 da EEPROM
   variavelLongch7 = EEPROMReadLong(25);     //Posicao 25, 26, 27 e 28 da EEPROM
   variavelLongch8 = EEPROMReadLong(29);     //Posicao 29, 30, 31 e 32 da EEPROM   
   
   mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
   pinMode(led1Pin, OUTPUT);
   pinMode(led2Pin, OUTPUT);
   pinMode(led3Pin, OUTPUT);
   pinMode(led4Pin, OUTPUT);
   pinMode(buzPin, OUTPUT);
   pinMode(ledSinal, OUTPUT);
   pinMode(Pin01, INPUT);
   pinMode(Pin02, INPUT);
   pinMode(Pin03, INPUT);
   pinMode(Pin04, INPUT);
   pinMode(botGravPin, INPUT);
   
   digitalWrite(led1Pin, LOW);
   digitalWrite(led2Pin, LOW);
   digitalWrite(led3Pin, LOW);
   digitalWrite(led4Pin, LOW);
   digitalWrite(buzPin, LOW);
   digitalWrite(ledSinal, LOW);
}

void loop() {
  controleRemoto();
  if(digitalRead(Pin01)&& digitalRead(Pin02)&& digitalRead(Pin03)&& digitalRead(Pin04)){
     // Serial.println("não gravando ");
     }else{
           gravar();
            //Serial.println("modo de gravação");
          }
   if(!flagled1 && !flagled2 && !flagled3 && !flagled4 ){
        digitalWrite(buzPin, LOW); 
        }
 }

void controleRemoto(){
  if (mySwitch.available()) {
    
     value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      digitalWrite(ledSinal,HIGH );
      delay(50);
      digitalWrite(ledSinal, LOW);
    }
       
    if (value == variavelLongch1) {
      Serial.println("led1 ligado");
      digitalWrite(led1Pin, HIGH);
      digitalWrite(buzPin,HIGH);
      flagled1=true;     
      }else if (value == variavelLongch2 ) {
      Serial.println("led1 Desligado");      
      digitalWrite(led1Pin, LOW);
      //digitalWrite(buzPin, LOW);
      flagled1=false;
      }else if (value == variavelLongch3 ) {
      Serial.println("led2 ligado");
      digitalWrite(led2Pin, HIGH);
      digitalWrite(buzPin, HIGH);
      flagled2=true;       
      }else if (value == variavelLongch4 ) {
      Serial.println("led2 Desligado");
      digitalWrite(led2Pin, LOW);
      //digitalWrite(buzPin, LOW);
      flagled2=false;      
      }else if (value == variavelLongch5 ) {
      Serial.println("led3 ligado");
      digitalWrite(led3Pin, HIGH);
      digitalWrite(buzPin, HIGH);
      flagled3=true;       
      }else if (value == variavelLongch6 ) {
      Serial.println("led3 Desligado");
      digitalWrite(led3Pin, LOW);
      //digitalWrite(buzPin, LOW);
      flagled3=false;      
      }else if (value == variavelLongch7 ) {
      Serial.println("led4 ligado");
      digitalWrite(led4Pin, HIGH);
      digitalWrite(buzPin, HIGH);
      flagled4=true;       
      }else if (value == variavelLongch8 ) {
      Serial.println("led4 Desligado");
      digitalWrite(led4Pin, LOW);
      //digitalWrite(buzPin, LOW);
      flagled4=false;      
      }      
    } 
    mySwitch.resetAvailable();
  
  }

void EEPROMWriteLong(int address, long value) {
   byte four = (value & 0xFF);
   byte three = ((value >> 8) & 0xFF);
   byte two = ((value >> 16) & 0xFF);
   byte one = ((value >> 24) & 0xFF);

   EEPROM.write(address, four);
   EEPROM.write(address + 1, three);
   EEPROM.write(address + 2, two);
   EEPROM.write(address + 3, one);
}

long EEPROMReadLong(int address) {
   long four = EEPROM.read(address);
   long three = EEPROM.read(address + 1);
   long two = EEPROM.read(address + 2);
   long one = EEPROM.read(address + 3);

   return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
void gravar(){

  int buttonState = digitalRead(botGravPin);  
  if(!digitalRead(Pin01)&& digitalRead(Pin02)&& digitalRead(Pin03)&& digitalRead(Pin04)){
    Serial.println("Gravação CH01 ");
     if(!buttonState) {
       variavelLongch1 = value; 
       EEPROMWriteLong(1, variavelLongch1);     //Posicao 1, 2, 3 e 4 da EEPROM
       Serial.print("variavelLongch1: ");
       Serial.println(variavelLongch1);
     }
    }else if(digitalRead(Pin01)&& !digitalRead(Pin02)&& digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH02 ");
     if(!buttonState) {
       variavelLongch2 = value; 
       EEPROMWriteLong(5, variavelLongch2);     //Posicao 5, 6, 7 e 8 da EEPROM
       Serial.print("variavelLongch2: ");
       Serial.println(variavelLongch2);
       } 
    }else if(!digitalRead(Pin01)&& !digitalRead(Pin02)&& digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH03 ");
     if(!buttonState) {
       variavelLongch3 = value; 
       EEPROMWriteLong(9, variavelLongch3);     //Posicao 9, 10, 11 e 12 da EEPROM
       Serial.print("variavelLongch3: ");
       Serial.println(variavelLongch3);
       } 
    }else if(digitalRead(Pin01)&& digitalRead(Pin02)&& !digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH04 ");
     if(!buttonState) {
       variavelLongch4 = value; 
       EEPROMWriteLong(13, variavelLongch4);     //Posicao 13, 14, 15 e 16 da EEPROM
       Serial.print("variavelLongch4: ");
       Serial.println(variavelLongch4);
       } 
    }else if(!digitalRead(Pin01)&& digitalRead(Pin02)&& !digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH05 ");
     if(!buttonState) {
       variavelLongch5 = value; 
       EEPROMWriteLong(17, variavelLongch5);     //Posicao 17, 18, 19 e 20 da EEPROM
       Serial.print("variavelLongch5: ");
       Serial.println(variavelLongch5);
       } 
    }else if(digitalRead(Pin01)&& !digitalRead(Pin02)&& !digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH06 ");
     if(!buttonState) {
       variavelLongch6 = value; 
       EEPROMWriteLong(21, variavelLongch6);     //Posicao 21, 22, 23 e 24 da EEPROM
       Serial.print("variavelLongch6: ");
       Serial.println(variavelLongch6);
       } 
    }else if(!digitalRead(Pin01)&& !digitalRead(Pin02)&& !digitalRead(Pin03)&& digitalRead(Pin04)){
      Serial.println("Gravação CH07 ");
     if(!buttonState) {
       variavelLongch7 = value; 
       EEPROMWriteLong(25, variavelLongch7);     //Posicao 25, 26, 27 e 28 da EEPROM
       Serial.print("variavelLongch7: ");
       Serial.println(variavelLongch7);
       } 
    }else if(digitalRead(Pin01)&& digitalRead(Pin02)&& digitalRead(Pin03)&& !digitalRead(Pin04)){
      Serial.println("Gravação CH08 ");
     if(!buttonState) {
       variavelLongch8 = value; 
       EEPROMWriteLong(29, variavelLongch8);     //Posicao 29, 30, 31 e 32 da EEPROM
       Serial.print("variavelLongch8: ");
       Serial.println(variavelLongch8);
       } 
    } 

  }
