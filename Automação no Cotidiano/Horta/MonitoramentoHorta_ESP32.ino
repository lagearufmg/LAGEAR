#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <BH1750.h> // Biblioteca para o sensor de luminosidade BH1750
#include <WiFiManager.h> // Adicione esta biblioteca para o WiFiManager

// Pinos dos sensores
#define SOIL_MOISTURE_PIN 33
#define DHTPIN 22
const int pinDS18B20 = 4; // Altere para corresponder ao seu pino

// Definições do sensor DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Objeto OneWire para a comunicação com o sensor DS18B20
OneWire oneWire(pinDS18B20);

// Objeto DallasTemperature para o gerenciamento do sensor DS18B20
DallasTemperature sensors(&oneWire);

// Pino do sensor BH1750
#define SDA_PIN 16 // Pino GPIO16 para SDA
#define SCL_PIN 17 // Pino GPIO17 para SCL
BH1750 lightMeter;

// Calibração do sensor de umidade do solo
const int valorMinimoSeco = 2985;
const int valorMaximoMolhado = 1185;

// Endereço do sensor DS18B20 (substitua com o seu endereço)
DeviceAddress sensorAddress = {0xB0, 0x51, 0xFC, 0x3F, 0x94, 0x1C, 0xFC, 0x3F};

// WiFi
WiFiManager wifiManager; // Instanciar o WiFiManager

// MQTT
const char *mqttServer = "XXX.XXX.XXX.XXX"; // inclua usuário e senha se necessário, conforme a biblioteca PubSubClient.h
const int mqttPort = 1883;
const char *temperatureTopic = "sensor/temperatura/horta";
const char *soilMoistureTopic = "sensor/umidade_solo/horta";
const char *soilTemperatureTopic = "sensor/temperatura_solo/horta";
const char *humidityTopic = "sensor/umidade/horta";
const char *lightTopic = "sensor/luminosidade/horta"; // Tópico para luminosidade

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup()
{
  Serial.begin(115200);

  // Configurar os pinos SDA e SCL
  Wire.begin(SDA_PIN, SCL_PIN);

  // Inicializar sensores
  dht.begin();
  sensors.begin();
  sensors.setResolution(sensorAddress, 12); // Configura a resolução do sensor
  sensors.setWaitForConversion(false); // Configura para leitura não bloqueante
  sensors.requestTemperaturesByAddress(sensorAddress); // Solicita a temperatura pelo endereço

  // Inicializar o sensor BH1750
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  // Inicializar Wi-Fi e MQTT
  setupWiFi();
  setupMQTT();

  Serial.println("Dispositivo iniciado.");
}

void loop()
{
  client.loop();

  // Leitura dos sensores
  int soilMoistureRaw = analogRead(SOIL_MOISTURE_PIN);
  float soilMoisture = map(soilMoistureRaw, valorMinimoSeco, valorMaximoMolhado, 0, 100);
  soilMoisture = constrain(soilMoisture, 0, 100);

  sensors.requestTemperatures();
  float soilTemperature = sensors.getTempCByIndex(0);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Leitura da luminosidade
  float lightLevel = lightMeter.readLightLevel();

  // Imprimir os valores lidos no monitor serial
  Serial.print("Umidade do Solo: ");
  Serial.print(soilMoisture);
  Serial.println(" %");
  Serial.print("Temperatura do Solo: ");
  Serial.print(soilTemperature);
  Serial.println(" °C");
  Serial.print("Temperatura Ambiente: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Umidade Ambiente: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Luminosidade: ");
  Serial.print(lightLevel);
  Serial.println(" lux");

  // Publicar os valores lidos nos respectivos tópicos MQTT
  char buffer[10];

  dtostrf(temperature, 4, 2, buffer);
  client.publish(temperatureTopic, buffer);

  dtostrf(soilMoisture, 4, 2, buffer);
  client.publish(soilMoistureTopic, buffer);

  dtostrf(soilTemperature, 4, 2, buffer);
  client.publish(soilTemperatureTopic, buffer);

  dtostrf(humidity, 4, 2, buffer);
  client.publish(humidityTopic, buffer);

  dtostrf(lightLevel, 4, 2, buffer);
  client.publish(lightTopic, buffer);

  delay(1500); // Aguardar 1,5 segundos antes da próxima leitura
}

void setupWiFi()
{
  // Iniciar o WiFiManager
  wifiManager.autoConnect("MonitoramentoHorta-Config"); // Nome da rede WiFi do ESP32 no modo de configuração

  // Após a configuração bem-sucedida, o código continuará a partir deste ponto
  Serial.println("Conectado à rede Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void setupMQTT()
{
  client.setServer(mqttServer, mqttPort);

  while (!client.connected())
  {
    Serial.println("Conectando-se ao broker MQTT...");

    if (client.connect("Sensores_Horta"))
    {
      Serial.println("Conectado ao broker MQTT");
    }
    else
    {
      Serial.print("Falha na conexão com o broker MQTT, estado: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
