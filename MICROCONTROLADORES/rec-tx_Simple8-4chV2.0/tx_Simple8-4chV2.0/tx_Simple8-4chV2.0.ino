
#define acinaAbertura          0
#define acionaFechamento       1
#define sensorPortao           2
 static unsigned long delayPisca;
 static unsigned long delayPisca1;   
int fimDeCurso; 
void portaoaberto(){
        delayPisca = millis();

       if ( (millis() - delayPisca1) < 1000 ) {
         digitalWrite(acinaAbertura,HIGH);
         Serial.println("Potão aberto <1000");
         Serial.println("transmitindo");
       }

       if ( ((millis() - delayPisca1) >= 1000) && ((millis() - delayPisca1) < 2500) ) {
           digitalWrite(acinaAbertura,LOW);
           Serial.println("Potão aberto >= 1000");
           Serial.println("transmissão deligada ");
       }      

       if ( ((millis() - delayPisca1) >= 2500) && ((millis() - delayPisca1) < 3500) ) {
          digitalWrite(acinaAbertura,HIGH);
          Serial.println("Potão aberto >= 2500");
          Serial.println("transmitindo");
       }
       if ( ((millis() - delayPisca1) >= 3500) && ((millis() - delayPisca1) < 5000) ) {
           digitalWrite(acinaAbertura,LOW);
           Serial.println("Potão aberto >= 3500");
           Serial.println("transmissão deligada");
       }         

       if ( ((millis() - delayPisca1) >= 5000) && ((millis() - delayPisca1) < 10000) ) {
           digitalWrite(acinaAbertura,LOW);
           Serial.println("Potão aberto >= 5000");
           Serial.println("transmissão deligada");
       }       

       if ( (millis() - delayPisca1) > 100000 ) {
          Serial.println("milis reiniciado");
          
       } 
       fimDeCurso = digitalRead(sensorPortao);    
   
}
void portaoFechado(){
   delayPisca1 = millis();
  

       if ( (millis() - delayPisca) < 1000 ) {
         digitalWrite(acionaFechamento,HIGH);
         Serial.println("Potão fechado <1000");
         Serial.println("transmitindo");
       }

       if ( ((millis() - delayPisca) >= 1000) && ((millis() - delayPisca) < 2500) ) {
           digitalWrite(acionaFechamento,LOW);
           Serial.println("Potão fechado >= 1000");
           Serial.println("transmissão deligada ");
       }      

       if ( ((millis() - delayPisca) >= 2500) && ((millis() - delayPisca) < 3500) ) {
          digitalWrite(acionaFechamento,HIGH);
          Serial.println("Potão fechado >= 2500");
          Serial.println("transmitindo");
       }
       if ( ((millis() - delayPisca) >= 3500) && ((millis() - delayPisca) < 5000) ) {
           digitalWrite(acionaFechamento,LOW);
           Serial.println("Potão fechado >= 3500");
           Serial.println("transmissão deligada");
       }         

       if ( ((millis() - delayPisca) >= 5000) && ((millis() - delayPisca) < 10000) ) {
           digitalWrite(acionaFechamento,LOW);
           Serial.println("Potão fechado >= 5000");
           Serial.println("transmissão deligada");
       }       

       if ( (millis() - delayPisca) > 100000 ) {
          Serial.println("milis reiniciado");
          delayPisca = millis();
       } 
       fimDeCurso = digitalRead(sensorPortao);    
   
  }
void setup() {
 Serial.begin(115200);   
 Serial.println("serial iniciada");
 pinMode(acinaAbertura, OUTPUT);
 pinMode(acionaFechamento, OUTPUT);
 pinMode(sensorPortao, INPUT);

 digitalWrite(acinaAbertura, LOW);
 digitalWrite(acionaFechamento, LOW);
}

void loop() {
   
  fimDeCurso = digitalRead(sensorPortao);
  if(!fimDeCurso){
    portaoFechado();
    digitalWrite(acinaAbertura, LOW);
    }else{      
      portaoaberto();
      digitalWrite(acionaFechamento, LOW);
      }

 
}
