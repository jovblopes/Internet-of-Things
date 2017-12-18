#include <Modbus.h>
#include <ModbusSerial.h>

// Arduino Mega conectado via USB com PC

// Modbus Registers Offsets (0-9999)
const int LAMP1_COIL = 100; 
const int LAMP2_COIL = 200; 
const int LAMP3_COIL = 300; 

//Variáveis auxiliares para evitar repetição de comando
int x1=0;
int x2=0;
int x3=0;
int y1=1;
int y2=1;
int y3=1;

// ModbusSerial object
ModbusSerial mb;

void setup() {
    // Configurando o modbus (port, speed, byte format) 
    mb.config(&Serial, 9600, SERIAL_8N1);
    // Set the Slave ID (1-247)
    mb.setSlaveId(10);  
    Serial3.begin(115200);
   
    // Set ledPin mode
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    
    // Adicionando os equipamentos modbus
    mb.addCoil(LAMP1_COIL);
    mb.addCoil(LAMP2_COIL);
    mb.addCoil(LAMP3_COIL);
}

void loop() {
   // Call once inside loop() - all magic here
   mb.task();
   
   //Recebe o comando modbus e opera as variáveis auxiliares para evitar repetição de comando e envia o o comando para o próximo Arduino   
   if(mb.Coil(LAMP1_COIL)){ 
   x1=1;
   }else{
   digitalWrite(13,LOW); //Teste de LED para checar se a mensagem foi recebida
   Serial3.print("desliga1");  //Manda a mensagem de desligar
   y1=1;
   x1=0;
   }

 // Mesmo caso acima
  if(mb.Coil(LAMP2_COIL)){ 
   x2=1;
   }else{
   digitalWrite(12,LOW);
   Serial3.println("desliga2");  //Manda a mensagem
   y2=1;
   x2=0;
   }

// Mesmo caso acima
if(mb.Coil(LAMP3_COIL)){ 
   x3=1;
   }else{
   digitalWrite(11,LOW);
   Serial3.print("desliga3");  //Manda a mensagem
   y3=1;
   x3=0;
   }
   

if(x1 && y1) //Checagem para evitar repetição
{    Serial3.print("liga1");  //Manda a mensagem de ligar
     digitalWrite(13,HIGH);
     y1=0; // Evitar repetição
}


// Mesmo caso acima
if(x2 && y2)
{    Serial3.print("liga2");  //Manda a mensagem
     digitalWrite(12,HIGH); //Teste de LED para checar se a mensagem foi recebida
     y2=0;
}

// Mesmo caso acima
if(x3 && y3)
{    Serial3.print("liga3");  //Manda a mensagem
     digitalWrite(11,HIGH);
     y3=0;
}

}
