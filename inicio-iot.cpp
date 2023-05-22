/* 
 *  Projeto: Alternar estado do led utilizando MQTT
 *  Autor: Brayan Barros Teixeira Cordeiro Silva
 *  Data: Novembro/2022
 */

#include <WiFi.h>
#include <PubSubClient.h>
 
//Configuracoes dos componentes
#define LED 21 //GPIO ligado ao led

//Definicao dos topicos
const char *topic_sub_led = "alterna_led";

//Configuracao do WiFi
const char *ssid = "Alunos";      //SSID da rede WiFi
const char *password = "ifprpvai"; //Senha da rede WiFi
 
//Configuracao do Broker MQTT
const char *mqtt_id = "TestebrayanIOT_ESP32";  //Identificacao do dispositivo
const char *mqtt_server = "broker.hivemq.com"; //Endereço do servidor MQTT
const int mqtt_port = 1883;                    //Porta do Broker MQTT
   
//Variáveis e objetos globais
WiFiClient espClient; //Criacao do objeto espClient
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

//Metodo reponsavel por receber mensagem
void callback(char *topic, byte *message, unsigned int length) {
  String messageTemp;

  //Armazena mensagem recebida
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
 
  //Altera estado do led mediante valor recebido
  if (String(topic) == topic_sub_led) {
    if (messageTemp == "0"){
      digitalWrite(LED, LOW);
      Serial.println(" = led desligado!");
    }
    else if (messageTemp == "1"){
      digitalWrite(LED, HIGH);
      Serial.println(" = led ligado!");
    }
  } 
}

//Efetua conexao com o WiFi
void connect_wifi() {
  Serial.print("Conectando-se a rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" Conectado ao WiFi!");
}

//Efetua conexao com o Broker
void connect_mqtt() {
  while (!client.connected()) {
    Serial.print("Conectando ao Broker MQTT: ");
    Serial.println(mqtt_server);
    
    if (client.connect(mqtt_id)) {
      Serial.println("Conectado ao Broker com sucesso!");
      client.subscribe(topic_sub_led);
      Serial.println("Fez o subscribe");
    }
    else {
      Serial.println("Falha na conexao");
      delay(1000);
    }
  }
}

//Mantem conexao
void keep_connection() {
  if (WiFi.status() != WL_CONNECTED) {
    connect_wifi();
  }
  if (!client.connected()) {
    connect_mqtt();
  }
}

void loop() {
  keep_connection();
  client.loop();
  delay(2000);
}	
