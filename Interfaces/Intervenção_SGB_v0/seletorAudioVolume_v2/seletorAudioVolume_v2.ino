#include <WiFi.h>
#include <PubSubClient.h>
#include "DFRobotDFPlayerMini.h"

// WiFi credentials
const char* ssid = "SSID";
const char* password = "password";

// MQTT broker
const char* mqttBroker = "000.000.000.000";
const int mqttPort = 0000;
const char* mqttUser = "user";
const char* mqttPassword = "password";

// DFPlayer Mini pin configuration
const byte RXD2 = 16; // Connects to module's RX
const byte TXD2 = 17; // Connects to module's TX
const byte busyPin = 4; // Connects to module's BUSY pin

// Variáveis de controle de áudio
int volume = 15;
int backgroundTrack = 0;
int adTrack = 0;

HardwareSerial dfSD(1); // Use UART channel 1
DFRobotDFPlayerMini player;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// WiFi connection status
bool wifiConnected = false;

// MQTT topic for receiving the audio control topic
const char* audioControlTopic = "esp32/audio1/faixa_fundo";
const char* audioVolumeTopic = "esp32/audio1/volume";
const char* audioAdTopic = "esp32/audio1/faixa_fala";

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
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';

  if (strcmp(topic, audioControlTopic) == 0) {
    // Received background track
    int track = atoi((char*)payload);
    backgroundTrack = track;
    player.loop(backgroundTrack);  
  } else if (strcmp(topic, audioVolumeTopic) == 0) {
    // Volume
    volume = atoi((char*)payload);
    player.volume(volume);
    Serial.print("Volume changed to: ");
    Serial.println(volume);
  } else if (strcmp(topic, audioAdTopic) == 0) {
    // Received ad track
    adTrack = atoi((char*)payload);
    player.advertise(adTrack);
  }
}

void setupMQTT() {
  mqttClient.setServer(mqttBroker, mqttPort);
  mqttClient.setCallback(mqttCallback);
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
      mqttClient.subscribe(audioControlTopic);
      delay(50);
      mqttClient.subscribe(audioVolumeTopic);
      delay(50);
      mqttClient.subscribe(audioAdTopic);
      delay(50);
    } else {
      Serial.print("failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Setup WiFi
  setupWiFi();

  // Setup MQTT
  setupMQTT();

  // Setup DFPlayer Mini
  dfSD.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(5000);

  if (player.begin(dfSD)) {
    Serial.println("DFPlayer Mini initialized");
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  // Configure the busy pin as INPUT
  pinMode(busyPin, INPUT);
}

void loop() {
  // Check if WiFi is connected
  if (!wifiConnected) {
    if (WiFi.status() == WL_CONNECTED) {
      wifiConnected = true;
      Serial.println("WiFi connected");
    }
  } else {
    // Ensure MQTT connection
    if (!mqttClient.connected()) {
      reconnectMQTT();
    }
    mqttClient.loop();
  }
   
}
