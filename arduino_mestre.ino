#include <SPI.h>
#include <Ethernet.h>


//Arduino Mega com ShieldEthernet 

String pedido="";


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192,168,1,70);          //Define o endereco IP
IPAddress gateway(192,168,1,1);      //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
EthernetClient client;


IPAddress node1(192, 168, 1, 71);
IPAddress node2(192, 168, 1, 72);
IPAddress node3(192, 168, 1, 73);
//ARDUINO .70
//NODE 1 .71
//NODE 2 .72
//NODE 3 .73


void setup() {

    Serial3.begin(115200);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    

  //Inicia a conexão ethernet com o modem 
   Ethernet.begin(mac, ip, gateway, subnet);

  Serial.print("Conectado no IP: ");
  Serial.println(Ethernet.localIP());

    
}

void loop() {

   pedido=Serial3.readString();
   

    if(pedido=="liga1"){
    digitalWrite(13,HIGH); //Teste de LED para verificar se a mensagem foi recebida
   client.connect(node1, 80); //Cria a conexão com o node1
   Serial.println("Conectado com Escravo 1");
    client.println(liga+"\r");  //Manda a mensagem
    client.flush(); //Espera o fim da mensagem
    client.stop();  //Desliga a conexão
     pedido="";
     } 


if(pedido=="desliga1"){
    digitalWrite(13,LOW);
     client.connect(node1, 80); //Cria a conexão com o node1
     Serial.println("Conectado com Escravo 1");
     client.println(desliga+"\r");  //Manda a mensagem
     client.flush(); //Espera o fim da mensagem
     client.stop();  //Desliga a conexão
     pedido="";
     } 


   if(pedido=="liga2"){
    digitalWrite(12,HIGH);
     client.connect(node2, 80); //Cria a conexão com o node2
     Serial.println("Conectado com Escravo 2");
     client.println(liga+"\r");  //Manda a mensagem
     client.flush(); //Espera o fim da mensagem
     client.stop();  //Desliga a conexão
     pedido="";
     } 


if(pedido=="desliga2"){
    digitalWrite(12,LOW);
     client.connect(node2, 80); //Cria a conexão com o node2
     Serial.println("Conectado com Escravo 2");
     client.println(desliga+"\r");  //Manda a mensagem
     client.flush(); //Espera o fim da mensagem
     client.stop();  //Desliga a conexão
     pedido="";
     } 


   if(pedido=="liga3"){
    digitalWrite(11,HIGH);
     client.connect(node3, 80); //Cria a conexão com o node3
     Serial.println("Conectado com Escravo 3");
     client.println(liga+"\r");  //Manda a mensagem
     client.flush(); //Espera o fim da mensagem
     client.stop();  //Desliga a conexão
     pedido="";
     } 


if(pedido=="desliga3"){
    digitalWrite(11,LOW);
     client.connect(node3, 80); //Cria a conexão com o node3
     Serial.println("Conectado com Escravo 3");
     client.println(desliga+"\r");  //Manda a mensagem
     client.flush(); //Espera o fim da mensagem
     client.stop();  //Desliga a conexão
     pedido="";
}

pedido="";


}
