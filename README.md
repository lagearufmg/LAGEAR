# Projeto de Monitoramento de Horta

Este projeto é um sistema de monitoramento de uma horta que utiliza sensores para coletar dados de temperatura, umidade do solo, luminosidade e umidade ambiente. Os dados coletados são publicados em um servidor MQTT para análise e visualização.

## Hardware Necessário

- ESP32 WEMOS LoLin Lite
- Sensores de temperatura (DS18B20), umidade (DHT11), umidade do solo e luminosidade (BH1750)
- Acesso à rede Wi-Fi
- Acesso a um servidor MQTT
- Código MonitoramentoHorta_ESP32.ino (disponível nesse repositório)

## Conexões dos Sensores

Siga estas instruções para conectar os sensores ao ESP32:

1. **Sensor de Umidade do Solo:**

   - Conecte a saída analógica do sensor de umidade do solo ao pino `SOIL_MOISTURE_PIN` (Pino 33 no exemplo) no ESP32.
   - Conecte a alimentação do sensor de umidade do solo (normalmente 3,3V) a um pino de 3,3V no ESP32.
   - Conecte o terra (GND) do sensor de umidade do solo a um pino GND no ESP32.

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

## Uso

O dispositivo coletará dados dos sensores e publicará esses dados em tópicos MQTT. Você pode se inscrever nos tópicos MQTT para receber os dados ou usar uma ferramenta MQTT de visualização para monitorar as leituras.

## Contribuição

Sinta-se à vontade para contribuir para o projeto, reportar problemas ou melhorar o código.

## Licença

Este projeto é licenciado sob a [Licença MIT](LICENSE), o que significa que você pode usá-lo livremente e modificar de acordo com suas necessidades.

## Autores

- Emídio Souza
- Agradecimentos especiais à Casa Flusser e a Robson Gregório por sua contribuição no desenvolvimento do projeto.


