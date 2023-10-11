#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

// Variáveis globais para armazenar as configurações de rede Wi-Fi e MQTT
char mqtt_server[40] = "XXX.XXX.XXX.XXX"; // Endereço IP ou nome de domínio do servidor MQTT
int mqtt_port = 1883; // Porta MQTT padrão
char mqtt_topic[40] = "sensor/poleiro_galinhas"; // Tópico MQTT

const int botaoPoleiro = 2;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(botaoPoleiro, INPUT_PULLUP);
  setupWiFiManager();
  client.setServer(mqtt_server, mqtt_port);
}

void setupWiFiManager() {
  // Crie um objeto WiFiManager
  WiFiManager wifiManager;

  // Tentar recuperar as informações salvas anteriormente
  if (!wifiManager.autoConnect("GalinheiroAP")) {
    Serial.println("Falha ao conectar e hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  Serial.println("Conexão WiFi estabelecida");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Converta a porta MQTT em uma string
  String mqtt_port_str = String(mqtt_port);

  // Obtenha as informações do servidor MQTT do WiFiManager
  WiFiManagerParameter custom_mqtt_server("server", "Endereço do Servidor MQTT", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "Porta MQTT", mqtt_port_str.c_str(), 6);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.autoConnect("GalinheiroAP");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao servidor MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int estadoBotao = digitalRead(botaoPoleiro);

  if (estadoBotao == LOW) {
    Serial.println("Galinhas no poleiro");
    client.publish(mqtt_topic, "1"); // Publica no tópico MQTT quando as galinhas estão no poleiro
  } else {
    Serial.println("Galinhas fora do poleiro");
    client.publish(mqtt_topic, "0"); // Publica no tópico MQTT quando as galinhas estão fora do poleiro
  }

  delay(1000);
}
