#include <ESP8266WiFi.h>
#include <WiFiClient.h>


//Definindo a Rede
const char* ssid = "problema";
const char* password = "12345678";
const uint16_t port = 80;

//Fixando o IP
IPAddress ip(192, 168, 1, 73); //Alterar o final do IP para configurar outro node
IPAddress gateway(192, 168, 1, 1);
IPAddress dns(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
//ARDUINO .70
//NODE 1 .71
//NODE 2 .72
//NODE 3 .73
//NODE 4 .74
#define pin_led 5



String requisicao = "";


void setup() {
 Serial.begin(115200);

  //Definindo a porta do LED
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);
 
//Configurando Wi-Fi
  Serial.println();
  Serial.println();
  WiFi.config(ip, gateway, subnet, dns);
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
Serial.println("");
  Serial.println("WiFi conectada");

  server.begin();
  Serial.println("Servidor Iniciado pelo IP:");
  Serial.println(WiFi.localIP());
}



void loop() {
  // put your main code here, to run repeatedly:

//Cria o socket de servidor e aguarda a conexão do cliente (arduino) 
WiFiClient client = server.available();
  if (client) {
      Serial.println("Conectado ao mestre!");
      requisicao = client.readStringUntil('\r');    // recebe a mensagem do arduino 
      Serial.println("Comando do mestre: "); Serial.print(requisicao);
      client.flush();
      client.stop(); 
    }
  

//Ação de ligar/desligar o LED dependendo da requisição
if (requisicao=="liga")
  {
    digitalWrite(pin_led,HIGH);
    Serial.println("Ligando LED");
    requisicao="";
  }
  if (requisicao=="desliga")
  {
    digitalWrite(pin_led,LOW);
    Serial.println("Desligando LED!");
    requisicao="";
  }


delay(100);
}
