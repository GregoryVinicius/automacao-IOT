/* 
 *  Projeto: Monitoramento da temperatura e umidade via MQTT
 *  Autor: Brayan Barros Teixeira Cordeiro Silva
 *  Data: Fevereiro/2023
 */

#include <WiFi.h>
#include <PubSubClient.h>

//Configuracoes dos componentes
const int buttonPin = 4;  // define o pino do botão como 4
int buttonState = 0;      // inicializa o estado do botão como 0

//Definicao dos topicos
const char *topic_pub_estadoBotao = "info_estadoBotao";

//Configuracao do WiFi
const char *ssid = "Juares_2G";       //SSID da rede WiFi
const char *password = "brayan2005";  //Senha da rede WiFi

//Configuracao do Broker MQTT
const char *mqtt_id = "TestebrayanIOT_ESP32";   //Identificacao do dispositivo
const char *mqtt_server = "broker.hivemq.com";  //Endereço do servidor MQTT
const int mqtt_port = 1883;                     //Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient;  //Criacao do objeto espClient
PubSubClient client(espClient);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  client.setServer(mqtt_server, mqtt_port);
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
    } else {
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
  buttonState = !digitalRead(buttonPin);  // lê o estado do botão
  Serial.println(buttonState);            // exibe a mensagem na porta serial
  delay(100);                             // aguarda 100ms para evitar leituras falsas

  keep_connection();

  char button_str[10];
  sprintf(button_str, "%d", buttonState);

  //Envia as strings ao dashboard MQTT
  client.publish(topic_pub_estadoBotao, button_str);

  client.loop();
  delay(200);
}