#include <WiFi.h>
#include <PubSubClient.h>

//Definicao dos topicos
const char *topic_pub_distancia = "distancia_da_RE";

//Configuracao do WiFi
const char *ssid = "Alunos";       //SSID da rede WiFi
const char *password = "ifprpvai";  //Senha da rede WiFi

//Configuracao do Broker MQTT
const char *mqtt_id = "Testesensorre_ESP32";   //Identificacao do dispositivo
const char *mqtt_server = "broker.hivemq.com";  //Endereço do servidor MQTT
const int mqtt_port = 1883;                     //Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient;  //Criacao do objeto espClient
PubSubClient client(espClient);
int leitura = 0;

void setup() {
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  client.setServer(mqtt_server, mqtt_port);
  Serial.begin(115200);
}

int ReadUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delay(2);
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return (int)(0.01723 * (double)pulseIn(echoPin, HIGH));
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
  int compare = ReadUltrasonicDistance(18, 19);

  if (compare < 300) {
  leitura = compare;
  Serial.println(leitura);
  }
  
  if (leitura > 34) {
    //apaga os LEDs se necessário
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
  }
  
  if (leitura > 25 & leitura < 35) {
    //apaga os LEDs se necessário
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
    
    digitalWrite(27, HIGH);
  }
  
  if (leitura > 15 & leitura < 26) {
    //apaga os LEDs se necessário
    digitalWrite(25, LOW);
    
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
  }
  
  if (leitura < 16) {

    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
  }

  keep_connection();

  char distance_str[10];
  sprintf(distance_str, "%d", leitura);

  //Envia as strings ao dashboard MQTT
  client.publish(topic_pub_distancia, distance_str);

  client.loop();
  delay(100);
}