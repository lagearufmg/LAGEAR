#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "SSID";
const char* password = "password";

// MQTT broker
const char* mqttBroker = "000.000.000.000";
const int mqttPort = 000;
const char* mqttUser = "user";
const char* mqttPassword = "password";

const int trigPin = 21;
const int echoPin = 22;
const int lightPin = 32;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// WiFi connection status
bool wifiConnected = false;

// MQTT topic for publishing the distance
const char* distanceTopic = "esp32/sensor1/distancia1";
const char* lightTopic = "esp32/sensor1/light1";

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  wifiConnected = true;
}

void setupMQTT() {
  mqttClient.setServer(mqttBroker, mqttPort);
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  pinMode(trigPin, OUTPUT); // Define o pino trigPin como saída
  pinMode(echoPin, INPUT); // Define o pino echoPin como entrada
  pinMode(lightPin, INPUT);

  setupWiFi();
  setupMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

  // Gera um pulso curto no pino trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê a duração do pulso no pino echoPin
  long duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  float distanceCm = duration * 0.034 / 2;

  // Limita a distância a 400cm
  if (distanceCm > 400) {
    distanceCm = 400;
  }
  else if (distanceCm < 0) {
    distanceCm = 0;
  }

  // Mapeia a distância para o intervalo entre 0 e 1
  float distance01 = distanceCm / 400.0;

  // Lê o valor do sensor de luz
  int lightValue = analogRead(lightPin);
  float light = lightValue * (1.0 / 4095.0);

  // Limita a luz ao intervalo entre 0 e 1
  if (light > 1.0) {
    light = 1.0;
  }
  else if (light < 0.0) {
    light = 0.0;
  }

  // Publica a distância e a luz mapeadas para o intervalo entre 0 e 1
  char distanceStr[10];
  sprintf(distanceStr, "%.3f", distance01);
  mqttClient.publish(distanceTopic, distanceStr);

  char lightStr[10];
  sprintf(lightStr, "%.3f", light);
  mqttClient.publish(lightTopic, lightStr);

  delay(100);
}

