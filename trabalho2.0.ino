//Biblioteca Temperatura
#include <Adafruit_Sensor.h>
#include "DHT.h"
//Biblioteca Infravermelho
#include <IRremoteESP8266.h>
#include <ESP8266WiFi.h>

//Infravermelho Pino D5
IRsend irsend(14);
int tamanho = 68; //TAMANHO DA LINHA RAW
int frequencia = 32; //FREQUÊNCIA DO SINAL 
unsigned int VOLUMEUP[68] = {8950,4550,550,650,500,650,500,650,500,650,500,650,500,650,500,650,500,650,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500,650,500,1800,500,650,500,1800,500,650,500,650,500,650,500,650,500,1800,500,650,500,1800,500,650,500,1800,500,1800,500,1800,500,
}; //CODIGO RAW
unsigned int VOLUMEDOWN[68] = {8900,4600,500,650,500,650,500,650,500,650,500,650,500,700,450,700,450,700,450,1800,500,1800,500,1800,500,1800,450,1800,500,1800,450,1800,450,1800,450,1800,450,1800,450,1800,450,700,450,700,450,700,450,700,500,650,450,700,450,700,450,700,450,1800,500,1800,450,1800,450,1800,450,1800,500,
}; //CODIGO RAW
unsigned int AVANCO[68] = {8950,4550,500,650,500,650,500,650,500,650,500,650,500,650,500,650,500,650,500,1800,500,1800,500,1800,500,1800,450,1800,500,1800,500,1800,450,1800,500,650,500,650,500,650,500,650,450,700,500,650,500,1800,500,650,500,1800,500,1800,500,1800,500,1800,500,1800,500,1800,500,650,500,1800,500,
}; //CODIGO RAW
unsigned int RETORNO[68] = {8950,4550,500,650,450,700,500,650,450,700,500,650,500,650,500,650,500,650,500,1800,450,1800,450,1800,450,1800,450,1800,450,1800,450,1800,500,1800,450,700,500,650,500,1800,450,700,500,650,450,700,450,1800,500,650,500,1800,450,1800,450,700,450,1800,450,1800,500,1800,500,650,500,1800,500,
}; //CODIGO RAW
unsigned int FASTFOWARD[68] = {8950,4550,550,600,550,650,550,600,550,650,550,600,550,650,550,600,550,600,550,1750,550,1750,550,1750,550,1750,550,1750,550,1700,550,1750,550,1700,550,1750,550,1750,550,1750,550,650,550,650,550,650,550,1750,550,650,550,650,550,650,550,650,550,1750,550,1750,550,1750,550,650,550,1750,550,
}; //CODIGO RAW

//Tempo de Resposta
unsigned long tic;
unsigned long toc;


//Sensor Pino D0
int switchValue;
int switchPin = 16;
String senspren = "Inativo";

//Definindo a Rede
const char* ssid = "Lopes 2.4GHz";
const char* password = "naovoutedizer";
//Fixando o IP
IPAddress ip(192, 168, 1, 70);
IPAddress gateway(192, 168, 1, 1);
IPAddress dns(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
 

//Temperatura Pino D1
#define DHTPIN 5
#define DHTTYPE DHT11
int humidade2;
int temperatura2;
DHT dht(DHTPIN, DHTTYPE);

//LDR PINO A0
String luz = "Desligada";


void setup() {

  Serial.begin(115200);
  
  //Define a Porta de Leitura do Sensor de presença
  pinMode(switchPin, INPUT);
  
  // Inicia a leitura de tempetatura
  dht.begin();
  //Inicia a função de infravermelho
  irsend.begin();

  
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
  
//Wi-FI
   WiFiClient client = server.available();
  if (!client) {
    return;
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  tic=millis(); //Inicia a contagem do tempo de resposta
  client.flush();
  
//Wi-Fi

 //INICIO TEMPERATURA
 //Realiza a Leitura de Temperatura
 int humidade = dht.readHumidity(); //Define uma variavel para humidade
 int temperatura = dht.readTemperature(); //Define uma variavel para Temperatura
//Checa Overflow de Leitura
if (temperatura>100)
{
 humidade = humidade2;
 temperatura=temperatura2;
} 
 humidade2 = humidade;
 temperatura2=temperatura;
 
 // Se ouver falha na leitura 
 if (isnan(temperatura) || isnan(humidade)) 
 {
 Serial.println("Erro na leitura do sensor"); 
 } 
  
 else  //Se nao ouver erro...
 { 
 Serial.print("Humidade: "); 
 Serial.print(humidade);
 Serial.print(" %\t");
 Serial.print("Temperatura: "); 
 Serial.print(temperatura);
 Serial.println(" *C");
 }
//FIM TEMPERATURA

//INICIO LDR

int sensorValue = analogRead(A0);
  // Converte o dado de 0 a 1023 para 0-100. 
  float voltage = sensorValue * (100 / 1023.0);
  // Printa a tensão do LDR
  Serial.println(voltage);
   if (voltage >= 75){
    luz = "Desligada";
  }else {
    luz = "Ligada";
  } 

//FIM LDR


//INICIO INFRAVERMELHO
  

    if (request.indexOf("/VOLUMEUP") != -1){ 
        irsend.sendRaw(VOLUMEUP,tamanho,frequencia);  
    }

    if (request.indexOf("/VOLUMEDOWN") != -1){ 
        irsend.sendRaw(VOLUMEDOWN,tamanho,frequencia);  
    }

    if (request.indexOf("/AVANCO") != -1){ 
        irsend.sendRaw(AVANCO,tamanho,frequencia);  
    }

    if (request.indexOf("/RETORNO") != -1){ 
        irsend.sendRaw(RETORNO,tamanho,frequencia); 
    }

    if (request.indexOf("/FASTFOWARD") != -1){ 
        irsend.sendRaw(FASTFOWARD,tamanho,frequencia); 
    }
toc=millis()-tic; //calcula o tempo de resposta
Serial.println(toc);//printa tempo de resposta
//FIM INFRAVERMELHO

//INICIO SENSOR DE PRESENÇA

switchValue = digitalRead(switchPin);
Serial.println("Sensor de presença:");
Serial.println(switchValue);
if(switchValue==1)
  {
  senspren = "Ativo";
  }
  else  {
    senspren = "Inativo";
    } ;


//FIM SENSOR DE PRESENÇA


//Wi-Fi Print
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  String cabecalho = "";
  cabecalho += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  cabecalho += "<h3>Controle do Quarto</h3>";
  cabecalho += "</html>\n";
  client.print(cabecalho);
  client.flush();
  
  String temp = "";
  temp += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  temp += "<h4>Temperatura da sala:</h4>";
  temp += "</html>\n";
  client.print(temp);
  client.print(temperatura);
  client.println(" *C");
  String umid = "";
  umid += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  umid += "<h4>Umidade da sala:</h4>";
  umid += "</html>\n";
  client.print(umid);
  client.print(humidade);
  client.print(" %\t");
  String ldr = "";
  ldr += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  ldr += "<h4>A luz esta atualmente:</h4>";
  ldr += "</html>\n";
  client.print(ldr);
  client.print(luz);
  client.flush();
  String sensorpresenca = "";
  sensorpresenca += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  sensorpresenca += "<h4>O sensor de presenca esta:</h4>";
  sensorpresenca += "</html>\n";
  client.print(sensorpresenca);
  client.print(senspren);
  client.println("</html>");
  client.println("<br><br>");
  String espaco = "";
  espaco += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  espaco += "<h4>Funcoes do Controle</h4>";
  client.print(espaco);
  client.flush();
  client.println(" <a href=\"/VOLUMEUP\">Aumentar Volume</a><br>");
  client.println("</html>");
  client.println("<br><br>");
  client.println(" <a href=\"/VOLUMEDOWN\">Diminuir Volume</a><br>");
  client.println("</html>");
  client.println("<br><br>");
  client.println(" <a href=\"/AVANCO\">Avancar Estacao</a><br>");
  client.println("</html>");
  client.println("<br><br>");
  client.println(" <a href=\"/RETORNO\">Retornar Estacao</a><br>");
  client.println("</html>");
  client.println("<br><br>");
  client.println(" <a href=\"/FASTFOWARD\">Avanco Rapido Estacao</a><br>");
  client.println("</html>");

//Fim Wi-Fi Print






  }
