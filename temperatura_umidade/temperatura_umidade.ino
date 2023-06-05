#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
//Definicao dos topicos
const char *topic_pub_temp = "info_temp";
const char *topic_pub_umidade = "info_umidade";

//Configuracao do WiFi
const char *ssid = "Alunos";       //SSID da rede WiFi
const char *password = "ifprpvai";  //Senha da rede WiFi

//Configuracao do Broker MQTT
const char *mqtt_id = "TesteDHT_ESP32";   //Identificacao do dispositivo
const char *mqtt_server = "broker.hivemq.com";  //Endereço do servidor MQTT
const int mqtt_port = 1883;                     //Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient;  //Criacao do objeto espClient
PubSubClient client(espClient);

#define DHTPIN 32
#define DHTTYPE DHT11 //Sensor em utilização 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 pinMode (32, INPUT);

  client.setServer(mqtt_server, mqtt_port);
  Serial.begin(115200);
}
float read_temp(){
  float t = dht.readTemperature();
  float result;
  if(!(isnan(t))){
  result = t;
  }
  else{
    result = -99.99;
  }
  Serial.print("Temperatura: ");
  Serial.println(result);
  return result;

}

float read_umi(){
  float h = dht.readHumidity();
  float result;
  if(!(isnan(h))){
  result = h;
  }
  else{
    result = -99.99;
  }
  Serial.print("Umidade: ");
  Serial.println(result);
  return result;

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


  

 keep_connection();

  char temperatura_str[10];
  sprintf(temperatura_str, "%.2fc", read_temp());

  //Envia as strings ao dashboard MQTT
  client.publish(topic_pub_temp, temperatura_str);

  char umidade_str[10];
  sprintf(umidade_str, "%.2fc", read_umi());

  //Envia as strings ao dashboard MQTT
  client.publish(topic_pub_umidade, umidade_str);
  client.loop();
  delay(100);
}


