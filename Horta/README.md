# Projeto de Monitoramento de Horta

Este projeto é um sistema de monitoramento de uma horta que utiliza sensores para coletar dados de temperatura, umidade do solo, luminosidade e umidade ambiente. Os dados coletados são publicados em um servidor MQTT para análise e visualização.

## Hardware Necessário

- ESP32 WEMOS LoLin Lite
- Sensores de temperatura (DS18B20), umidade (DHT11), umidade do solo  e luminosidade (BH1750)
- Acesso à rede Wi-Fi
- Acesso a um servidor MQTT
- Código MonitoramentoHorta_ESP32.ino (disponível nesse repositório)

## Conexões dos Sensores

Siga estas instruções para conectar os sensores ao ESP32:

1. **Sensor de Umidade do Solo:**

   - Conecte a saída analógica do sensor de umidade do solo ao pino `SOIL_MOISTURE_PIN` (Pino 33 no exemplo) no ESP32.
   - Conecte a alimentação do sensor de umidade do solo (normalmente 3,3V) a um pino de 3,3V no ESP32.
   - Conecte o terra (GND) do sensor de umidade do solo a um pino GND no ESP32.

   **Calibração do Sensor de Umidade do Solo:**

   O sensor de umidade do solo pode requerer calibração para fornecer leituras precisas. Para calibrar o sensor, siga estas etapas:

   a. Deixe o sensor no solo por um período de tempo para estabilizar as leituras.
   b. Meça a umidade do solo em um estado conhecido (por exemplo, solo seco e solo úmido) e anote as leituras.
   c. Use esses valores para calibrar as leituras do sensor no código.

2. **Sensor de Temperatura DS18B20:**

   - Conecte o pino de dados (geralmente amarelo) do sensor DS18B20 ao pino `pinDS18B20` (Pino 4 no exemplo) no ESP32.
   - Conecte o terra (GND) do sensor DS18B20 a um pino GND no ESP32.
   - Conecte a alimentação do sensor DS18B20 (geralmente vermelho) a um pino de 3,3V no ESP32.
   - **Nota**: Em alguns casos, pode ser necessário adicionar um resistor pull-up de 4.7k Ohm entre o pino de dados e a alimentação (3,3V) para garantir a leitura correta do sensor.

3. **Sensor de Umidade e Temperatura DHT11:**

   - Conecte o pino de dados (geralmente branco ou amarelo) do sensor DHT11 ao pino `DHTPIN` (Pino 22 no exemplo) no ESP32.
   - Conecte o terra (GND) do sensor DHT11 a um pino GND no ESP32.
   - Conecte a alimentação do sensor DHT11 (geralmente vermelho) a um pino de 3,3V no ESP32.

4. **Sensor de Luminosidade BH1750:**

   - Conecte o pino SDA do sensor BH1750 ao pino `SDA_PIN` (Pino 16 no exemplo) no ESP32.
   - Conecte o pino SCL do sensor BH1750 ao pino `SCL_PIN` (Pino 17 no exemplo) no ESP32.
   - Conecte a alimentação do sensor BH1750 (geralmente 3,3V) a um pino de 3,3V no ESP32.
   - Conecte o terra (GND) do sensor BH1750 a um pino GND no ESP32.

Certifique-se de que todas as conexões estejam firmes e de que os sensores estejam devidamente alimentados e conectados aos pinos corretos no ESP32. Além disso, verifique se os pinos utilizados correspondem às definições no seu código.

## Configuração Wi-Fi

Para configurar o ESP32 para se conectar à sua rede Wi-Fi, siga as instruções abaixo:

1. Carregue o código no seu ESP32 usando a Arduino IDE ou outra plataforma de desenvolvimento.
2. Abra a Serial Monitor e aguarde as mensagens.
3. Quando o dispositivo não conseguir se conectar à rede WiFi configurada anteriormente, ele entrará no modo de configuração.
4. Conecte-se à rede Wi-Fi do dispositivo, que deve aparecer com o nome "ESP32-Config".
5. Abra um navegador da web e acesse o endereço IP `192.168.4.1`.
6. Você será redirecionado para uma página de configuração onde poderá inserir as informações da sua rede Wi-Fi, como o SSID e a senha.
7. Após a configuração, o dispositivo tentará se conectar à sua rede Wi-Fi usando as novas informações.

## Configuração MQTT

Para publicar e receber dados dos sensores, este projeto utiliza o protocolo MQTT. Para configurar o MQTT, siga estas etapas:

1. Abra o código fonte `MonitoramentoHorta_ESP32.ino` no Arduino IDE ou em sua plataforma de desenvolvimento preferida.

2. Encontre as seguintes linhas no código:

   ```cpp
   // WiFi
   const char *ssid = "sua-rede";
   const char *password = "sua-senha";

   // MQTT
   const char *mqttServer = "seu-broker-mqtt"; //inclua usuário e senha se necessário, conforma a biblioteca PubSubClient.h
   const int mqttPort = 1883;
   const char *temperatureTopic = "sensor/temperatura/horta";
   const char *soilMoistureTopic = "sensor/umidade_solo/horta";
   const char *soilTemperatureTopic = "sensor/temperatura_solo/horta";
   const char *humidityTopic = "sensor/umidade/horta";
   const char *lightTopic = "sensor/luminosidade/horta"; // Tópico para luminosidade

**Edite as informações a seguir para corresponder à sua configuração MQTT:**

3. mqttServer: Insira o endereço IP ou o nome de domínio do seu servidor MQTT.
   mqttPort: Insira a porta do servidor MQTT (o valor padrão é 1883).
   temperatureTopic, soilMoistureTopic, soilTemperatureTopic, humidityTopic, lightTopic: Personalize os tópicos MQTT de acordo com suas preferências.
   Salve o código após as edições.

4. Carregue o código no seu ESP32 utilizando a Arduino IDE ou a plataforma de desenvolvimento de sua escolha.

5. Agora, o ESP32 está configurado para se conectar ao seu servidor MQTT e publicar dados nos tópicos MQTT especificados.

6. Certifique-se de que seu servidor MQTT esteja configurado corretamente e que os tópicos MQTT definidos no código estejam corretos. Você pode usar um cliente MQTT, como o MQTT Explorer, para monitorar os tópicos e receber os dados dos sensores.

7. Lembre-se de que a segurança do servidor MQTT (autenticação e autorização) é importante para proteger suas comunicações. A configuração específica pode variar dependendo do seu ambiente MQTT.


## Uso

O dispositivo coletará dados dos sensores e publicará esses dados em tópicos MQTT. Você pode se inscrever nos tópicos MQTT para receber os dados ou usar uma ferramenta MQTT de visualização para monitorar as leituras.

## Contribuição

Sinta-se à vontade para contribuir para o projeto, reportar problemas ou melhorar o código.

## Licença

Este projeto é licenciado sob a [Licença MIT](LICENSE), o que significa que você pode usá-lo livremente e modificar de acordo com suas necessidades.

## Autores

- Emídio Souza
- Agradecimentos especiais à Casa Flusser e a Robson Gregório por sua contribuição no desenvolvimento do projeto.
