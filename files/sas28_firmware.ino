/***********************************************
  Project name: SAS-28, firmware v1.0.0
  URL Docs: http://rclabs.com.br/projetc/sas28
  Author: Regivaldo Costa and Stephanie Costa
  Date: Feb/2013
***********************************************/

#include <LiquidCrystal.h>
#include <EEPROM.h>

// Controle da EEPROM
int eepromAddr = 0;
byte eepromValue;

// VU Meter
const int pair1VULeft  = A0;
const int pair1VURight = A1;
const int pair2VULeft  = A2;
const int pair2VURight = A3;
int pair1Left  = 0;
int pair1Right = 0;
int pair2Left  = 0;
int pair2Right = 0;
// Hexa FF é o bloco do caracter todo preenchido
String barGraph[17] = {"                ", 
                      "\xFF               ",
                      "\xFF\xFF              ", 
                      "\xFF\xFF\xFF             ",
                      "\xFF\xFF\xFF\xFF            ", 
                      "\xFF\xFF\xFF\xFF\xFF           ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF          ", 
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF         ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF        ", 
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF       ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF      ", 
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF     ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF    ", 
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF   ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF  ", 
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF ",
                      "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"};
                      
String dotGraph[17] = {"                ", 
                       "\xFF               ",
                       " \xFF              ", 
                       "  \xFF             ",
                       "   \xFF            ", 
                       "    \xFF           ",
                       "     \xFF          ", 
                       "      \xFF         ",
                       "       \xFF        ", 
                       "        \xFF       ",
                       "         \xFF      ", 
                       "          \xFF     ",
                       "           \xFF    ", 
                       "            \xFF   ",
                       "             \xFF  ", 
                       "              \xFF ",
                       "               \xFF"};


// Controles do Rotary Encoder
int rotaryValue = 1;    
int rotaryStep = 1;    
int ampSelSP1 = 0;
int ampSelSP2 = 0;
unsigned long currentTime;
unsigned long loopTime;
const int encoderPinA = 17;  
const int encoderPinB = 18;  
const int encoderButton = 19;
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

// Pinos e controles da chaves do painel
const int onVUMeterPin = 20;
const int offDisplaysPin = 21;
const int lockSelPin = 53;
int lockSelFlag = 0;
int vuModeFlag = 0;

// Controle do LCD
LiquidCrystal lcdLeft(22,23,24,25,26,27);
LiquidCrystal lcdRight(28,29,30,31,32,33);
String lcdLeftBuffer;
String lcdRightBuffer;
String lcdBufferTmp = "Amplifier N\xDF ";

// Controle dos display de 7 segmentos
int a = 2, b = 3, c = 4, d = 5, e = 6, f = 7, g = 8;
int a2 = 9, b2 = 10, c2 = 11, d2 = 12, e2 = 13, f2 = 14, g2 = 15;
int dotDisplayPin = 16;
int dispSeg1[9][7] = {{b,c}, {a,b,e,d,g}, {a,b,c,d,g},
                     {b,c,f,g}, {a,c,d,g,f}, {a,c,d,e,f,g},
                     {a,b,c}, {a,b,c,d,e,f,g}, {b,c,e,d,g}};
int dispSeg2[9][7] = {{b2,c2}, {a2,b2,e2,d2,g2}, {a2,b2,c2,d2,g2},
                     {b2,c2,f2,g2}, {a2,c2,d2,g2,f2}, {a2,c2,d2,e2,f2,g2},
                     {a2,b2,c2}, {a2,b2,c2,d2,e2,f2,g2}, {b2,c2,e2,d2,g2}};
unsigned long timeDisplayOff;
unsigned long timeDisplayKeep = 10000;
                     
// Controle da comutação dos relés
const int amp1SP1 = 38;
int switchRelaySP1;
int switchRelaySP2;

void setup(){
   // Configura estado inicial para o Rotary Encoder
   Serial.begin (9600);
   pinMode(encoderPinA, INPUT);
   pinMode(encoderPinB, INPUT);
   pinMode(encoderButton, INPUT);
   digitalWrite(encoderPinA, HIGH);
   digitalWrite(encoderPinB, HIGH); 
   digitalWrite(encoderButton, HIGH); 
   currentTime = millis();
   loopTime = currentTime; 
  
   // Configura estado inical dos LCDs 
   lcdLeft.begin(16,2); 
   lcdRight.begin(16,2);
   lcdLeft.print("     SAS-28");
   lcdLeft.setCursor(0, 1);
   lcdLeft.print("Firmware v1.0.0");
   lcdRight.print("Loading SP/Amps");
   lcdRight.setCursor(0, 1);
   lcdRight.print("Configuration...");      
   delay(1000); // Aguarda para que a versão de firmware possa ser visualizada
   lcdLeft.clear();
   lcdRight.clear();

   // Define saídas digitais a serem usadas como OUTPUT
   pinMode(2,OUTPUT); pinMode(3,OUTPUT); pinMode(4,OUTPUT); 
   pinMode(5,OUTPUT); pinMode(6,OUTPUT); pinMode(7,OUTPUT); 
   pinMode(8,OUTPUT); pinMode(9,OUTPUT); pinMode(10,OUTPUT);
   pinMode(11,OUTPUT); pinMode(12,OUTPUT); pinMode(13,OUTPUT);
   pinMode(14,OUTPUT); pinMode(15,OUTPUT); pinMode(16,OUTPUT); pinMode(36,OUTPUT); 
   pinMode(37,OUTPUT); pinMode(38,OUTPUT); pinMode(39,OUTPUT); 
   pinMode(40,OUTPUT); pinMode(41,OUTPUT); pinMode(42,OUTPUT); 
   pinMode(43,OUTPUT); pinMode(44,OUTPUT); pinMode(45,OUTPUT); 
   pinMode(46,OUTPUT); pinMode(47,OUTPUT); pinMode(48,OUTPUT); 
   pinMode(49,OUTPUT); pinMode(50,OUTPUT); pinMode(51,OUTPUT); 
   pinMode(52,OUTPUT); pinMode(53,OUTPUT); 
   clearDisplaySP1();
   clearDisplaySP2();
   
   // Configura modo de leitura das teclas externas
   pinMode(onVUMeterPin, INPUT);
   pinMode(offDisplaysPin, INPUT);
   digitalWrite(onVUMeterPin, HIGH); 
   digitalWrite(offDisplaysPin, HIGH); 
   pinMode(lockSelPin, INPUT);
   digitalWrite(lockSelPin, HIGH); 
   
   // Ler dados da EEPROM para ativar ultima configuração
   // Ler primeiro byte da eeprom (estado de SP1)
   eepromValue = EEPROM.read(eepromAddr);
   ampSelSP1 = eepromValue - 1;

   // Ler primeiro byte da eeprom (estado de SP2)
   eepromAddr = eepromAddr + 1;
   eepromValue = EEPROM.read(eepromAddr);
   ampSelSP2 = eepromValue - 1;

   // Apresenta e ativa estado de comutação desde o último power-off
   switchRelays(ampSelSP1, ampSelSP2);
} 

void loop(){
   if (!digitalRead(lockSelPin)){
      lockSelFlag = 1; // Tecla "Lock Sel" pressionada
   }
   else{
      lockSelFlag = 0;
   }
   if (digitalRead(offDisplaysPin)){ // Chave "Display Off" pressionada
      digitalWrite(dotDisplayPin, HIGH); 
      if (digitalRead(onVUMeterPin)){ // Chave pressionada para modo VU Meter   
         if (vuModeFlag == 1){ // Volta ao normal após despressionamento da chave VU
            vuModeFlag = 0;
            switchRelays(ampSelSP1, ampSelSP2); // Garante Comutação dos relés e informa estado no LCD
         }
            
         // Tempo inicial para referência do Rotary
         currentTime = millis();

         // Apaga display após 10 segundos da última operação (variavel timeDisplayKeep)
         if (currentTime > timeDisplayOff){
            clearDisplaySP1();
            clearDisplaySP2();
         }

        // Inicio do algoritmo para leitura do Rotary
        if (currentTime >= (loopTime + 1)){  
           encoder_A = digitalRead(encoderPinA); // Ler estado do pino do encoder
           encoder_B = digitalRead(encoderPinB);   
           if ((!encoder_A) && (encoder_A_prev)){ // Houve movimento
              timeDisplayOff = millis() + timeDisplayKeep; // tempo para desligar display
              if (lockSelFlag == 1){
                 printLCD(2, " Buttom Locked.", "Pull for Unlock."); 
                 delay(1000);           
                 switchRelays(ampSelSP1, ampSelSP2);                 
              }
              else{                                      
                 if (encoder_B){ // Movimento para direita
                    ampSelSP2 ++; // Correspondência do amplificador
                    if (ampSelSP2 == 9) ampSelSP2 = 0; // Round Robin da seleção
                    clearDisplaySP2();
                    SetValueDisplaySP2(ampSelSP2); // Define o valor nos displays
                    SetValueDisplaySP1(ampSelSP1);
                    if (rotaryValue + rotaryStep <= 9) rotaryValue += rotaryStep; // Round Robin do Rotary              
                  }
                  else{ // Movimento para esquerda
                    ampSelSP1 ++;
                    if (ampSelSP1 == 9) ampSelSP1 = 0;
                    clearDisplaySP1();
                    SetValueDisplaySP1(ampSelSP1); 
                    SetValueDisplaySP2(ampSelSP2);
                    if (rotaryValue - rotaryStep >= 0) rotaryValue -= rotaryStep;               
                  }           
              }              
           }   // Houve movimento do encoder
           encoder_A_prev = encoder_A; // Grava valor do Pino A para próxima passagem    
           loopTime = currentTime; // Renova referência de tempo para identificar novo movimento
        }
        
        if (!digitalRead(encoderButton)){
           if (lockSelFlag == 0){
              timeDisplayOff = millis() + timeDisplayKeep;
              SetValueDisplaySP1(ampSelSP1);
              SetValueDisplaySP2(ampSelSP2);
              switchRelays(ampSelSP1, ampSelSP2); // Comuta relés e informa estado no LCD
   
              // Grava na EEPROM dados da seleção
              eepromAddr = 0;
              EEPROM.write(eepromAddr, (ampSelSP1 + 1));
              EEPROM.write(eepromAddr + 1, (ampSelSP2 + 1));
           }
           else{
            printLCD(2, " Buttom Locked.", "Pull for Unlock."); 
            delay(1000);           
            switchRelays(ampSelSP1, ampSelSP2);
           }   
        }  // Botão encoder pressionado                 
      } // Acionado modo VU
      else{
        if(vuModeFlag == 0){
          // Faz leitura das entradas analógicas A0-A3
          pair1Left   = map((analogRead(pair1VULeft)),0,1023,0,16);  
          pair1Right  = map((analogRead(pair1VURight)),0,1023,0,17);
          pair2Left   = map((analogRead(pair2VULeft)),0,1023,0,17);
          pair2Right  = map((analogRead(pair2VURight)),0,1023,0,17);
          // Faz chamada a função para plotar no LCD barra do VU
          printVUPair1(pair1Left, pair1Right);
          printVUPair2(pair2Left, pair2Right);
          //delay(2);
          
        }  
      }
   } // Displays desligados a partir do botão
   else{
      digitalWrite(dotDisplayPin, LOW);
      clearDisplaySP1();
      clearDisplaySP2();
   }    
} // Fim da funçao loop

// Apaga segmentos do display SP1
void clearDisplaySP1(){
   digitalWrite(a,HIGH); digitalWrite(b,HIGH); digitalWrite(c,HIGH);
   digitalWrite(d,HIGH); digitalWrite(e,HIGH); digitalWrite(f,HIGH);
   digitalWrite(g,HIGH);
}

// Apaga segmentos do display SP2
void clearDisplaySP2(){
   digitalWrite(a2,HIGH); digitalWrite(b2,HIGH); digitalWrite(c2,HIGH);
   digitalWrite(d2,HIGH); digitalWrite(e2,HIGH); digitalWrite(f2,HIGH);
   digitalWrite(g2,HIGH);
}

// Define valor para o display SP1
void SetValueDisplaySP1(int n){
   for (int i=0;i<7;i++) {
      digitalWrite(dispSeg1[n][i], LOW);
   }
}
// Define valor para o display SP2 
void SetValueDisplaySP2(int n){
   for (int i=0;i<7;i++) {
     digitalWrite(dispSeg2[n][i], LOW);
   }
}

// Efetua as comutação em tempo de boot e apresenta no LCD
void switchRelays(int sp1, int sp2){  
   switchRelaySP1 = 50 - (sp1 * 2); // Porta do arduino correspondente ao relé SP1
   switchRelaySP2 = 51 - (sp2 * 2); // Porta do arduino correspondente ao relé SP2
   lcdLeft.clear();
   lcdRight.clear();
 
   // Loop que garante a desativação e ativação conforme seleção
   for (int relayCount=51; relayCount > 36; relayCount--){
      // Amps associados a SP1 (pinos pares iniciando em 36)
      if (relayCount % 2 == 0){ 
         if (relayCount == switchRelaySP1){
            digitalWrite(relayCount, HIGH);
         }
         else{
            digitalWrite(relayCount, LOW);
         }
      }  
      else{ // Amps associados a SP2 (Portas impares do arduino iniciando em 37)
         if (relayCount == switchRelaySP2){
            digitalWrite(relayCount, HIGH);
         }
         else{
            digitalWrite(relayCount, LOW);
         }
      }
   }
 
   // Seleção "d", desativa todos os relés relacionados a SP1
   if (sp1 == 8){
      lcdLeft.print("System Speakers");
      lcdLeft.setCursor(0, 1);
      lcdLeft.print("SP1 deactivated");
   }
   else{ // Ativa Amp selecionado e associado a SP1
      lcdLeft.clear();
      lcdLeftBuffer = lcdBufferTmp + (sp1 + 1);
      lcdLeft.print(lcdLeftBuffer);
      lcdLeft.setCursor(0, 1);
      lcdLeft.print("ACTIVE ON SP1");
      digitalWrite(switchRelaySP1, HIGH);
   }
   
   // Seleção "d", desativa todos os relés relacionados a SP2
   if (sp2 == 8){
      lcdRight.print("System Speakers");
      lcdRight.setCursor(0, 1);
      lcdRight.print("SP2 deactivated");
   }
   else {  // Ativa Amp selecionado e associado a SP2
      lcdLeftBuffer = lcdBufferTmp + (sp2 + 1);
      lcdRight.clear();
      lcdRight.print(lcdLeftBuffer);
      lcdRight.setCursor(0, 1);
      lcdRight.print("ACTIVE ON SP2");
      digitalWrite(switchRelaySP2, HIGH);
   }
}

void printLCD(int lcdPos, String l1, String l2){ // Escreve nos LCDs
   if (lcdPos == 0 || lcdPos == 2){
      lcdLeft.clear();
      lcdLeft.print(l1);
      lcdLeft.setCursor(0, 1);
      lcdLeft.print(l2);
   }
   if (lcdPos == 1 || lcdPos == 2){
      lcdRight.clear();
      lcdRight.print(l1);
      lcdRight.setCursor(0, 1);
      lcdRight.print(l2);
   }
}

void printVUPair1(int leftVUP1, int rightVUP1){ // Escreve no LCD da esquerda 
      delay(10);
      lcdLeft.setCursor(0, 0);
      lcdLeft.print(barGraph[leftVUP1]);
      lcdLeft.setCursor(0, 1);
      lcdLeft.print(barGraph[rightVUP1]);    
}

void printVUPair2(int leftVUP2, int rightVUP2){ // Escreve no LCD da direita 
      delay(10);
      lcdRight.setCursor(0, 0);
      lcdRight.print(barGraph[leftVUP2]);
      lcdRight.setCursor(0, 1);
      lcdRight.print(barGraph[rightVUP2]);    
}
