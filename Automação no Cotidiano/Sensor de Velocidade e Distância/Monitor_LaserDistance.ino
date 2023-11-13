#include <Wire.h>
#include <VL53L0X.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

VL53L0X sensor;
unsigned long previousMillis = 0;
int previousDistance = 0;

// WiFi e configurações MQTT
WiFiManager wifiManager;
const char* mqtt_server = "000.000.000.000";
const int mqtt_port = 0000;
const char* mqtt_topic_videospeed = "sensor/laser_distance/video_speed"; // Tópico de velocidade
const char* mqtt_topic_distance = "sensor/laser_distance/video_distance"; // Tópico de distância
const char* mqtt_topic_speed = "sensor/laser_distance/speed"; // Terceiro tópico

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  Wire.begin(19, 23);

  wifiManager.autoConnect("AutoConnectAP");

  client.setServer(mqtt_server, mqtt_port);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
}

void loop()
{
  unsigned long currentMillis = millis();
  int currentDistance = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) { 
    Serial.print(" TIMEOUT"); 
  } else {
    // Calcula a velocidade em metros por segundo (m/s)
    float velocity = (float(currentDistance - previousDistance) / 1000.0) / (float(currentMillis - previousMillis) / 1000.0);
    
    // Mapeia a velocidade para um valor entre 10 e -10
    float mappedSpeed = map(velocity * 10, -10, 10, -10, 10);
    
    // Publica os valores nos tópicos MQTT
    if (client.connected()) {
      char videospeedStr[10];
      char distanceStr[10];
      char speedStr[10];
      dtostrf(mappedSpeed, 4, 2, videospeedStr);
      dtostrf(currentDistance / 1000.0, 4, 2, distanceStr);
      dtostrf(velocity, 4, 2, speedStr);
      
      client.publish(mqtt_topic_videospeed, videospeedStr);
      client.publish(mqtt_topic_distance, distanceStr);
      client.publish(mqtt_topic_speed, speedStr); // Terceiro tópico
    }
    
    Serial.print("Distance: ");
    Serial.print(currentDistance / 1000.0);
    Serial.print(" m, Velocity: ");
    Serial.print(velocity);
    Serial.print(" m/s, mappedSpeed: ");
    Serial.print(mappedSpeed);
    Serial.println(" units");
    

    previousMillis = currentMillis;
    previousDistance = currentDistance;
  }
  
  // Reconecta ao servidor MQTT, se necessário
  if (!client.connected()) {
    reconnectMqtt();
  }

  client.loop();
}

void reconnectMqtt() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed to connect to MQTT, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}
