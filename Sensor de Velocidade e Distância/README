# Projeto de Monitoramento de Distância a Laser

Este projeto utiliza um sensor de distância a laser VL53L0X para medir a distância e a velocidade de um objeto. Os dados coletados são publicados em um servidor MQTT para análise e visualização.

## Hardware Necessário

- ESP32 WEMOS LoLin Lite
- Sensor de distância a laser VL53L0X
- Acesso à rede Wi-Fi
- Código .ino disponível neste repositório

## Conexões

Conecte o sensor VL53L0X ao ESP32 conforme sua preferência para os pinos SDA (Serial Data) e SCL (Serial Clock). O código foi configurado para usar os pinos padrão do ESP32 para I2C (SDA em 19 e SCL em 23), mas você pode alterá-los conforme necessário.

## Configuração Wi-Fi

Para configurar o ESP32 para se conectar à sua rede Wi-Fi, siga as instruções abaixo:

1. Carregue o código no seu ESP32 usando a Arduino IDE ou outra plataforma de desenvolvimento.
2. Abra a Serial Monitor e aguarde as mensagens.
3. Quando o dispositivo não conseguir se conectar à rede Wi-Fi configurada anteriormente, ele entrará no modo de configuração.
4. Conecte-se à rede Wi-Fi do dispositivo, que deve aparecer com o nome "AutoConnectAP".
5. Abra um navegador da web e acesse o endereço IP `192.168.4.1`.
6. Você será redirecionado para uma página de configuração onde poderá inserir as informações da sua rede Wi-Fi, como o SSID e a senha.
7. Após a configuração, o dispositivo tentará se conectar à sua rede Wi-Fi usando as novas informações.

## Configuração MQTT

Para publicar e receber dados dos sensores, este projeto utiliza o protocolo MQTT. Para configurar o MQTT, siga estas etapas:

1. Abra o código fonte `MonitoramentoHorta_ESP32.ino` no Arduino IDE ou em sua plataforma de desenvolvimento preferida.

2. Encontre as seguintes linhas no código:

 ```cpp
// Configuração MQTT
const char* mqtt_server = "seu-broker-mqtt";
const int mqtt_port = 1883;
const char* mqtt_topic_videospeed = "sensor/laser_distance/video_speed"; // Tópico de velocidade
const char* mqtt_topic_distance = "sensor/laser_distance/video_distance"; // Tópico de distância
const char* mqtt_topic_speed = "sensor/laser_distance/speed"; // Terceiro tópico

3. Edite as informações a seguir para corresponder à sua configuração MQTT:

   mqttServer: Insira o endereço IP ou o nome de domínio do seu servidor MQTT.
   mqttPort: Insira a porta do servidor MQTT (o valor padrão é 1883).
   temperatureTopic, soilMoistureTopic, soilTemperatureTopic, humidityTopic, lightTopic: Personalize os tópicos MQTT de acordo com suas preferências.
   Salve o código após as edições.

4. Carregue o código no seu ESP32 utilizando a Arduino IDE ou a plataforma de desenvolvimento de sua escolha.

5. Agora, o ESP32 está configurado para se conectar ao seu servidor MQTT e publicar dados nos tópicos MQTT especificados.

6. Certifique-se de que seu servidor MQTT esteja configurado corretamente e que os tópicos MQTT definidos no código estejam corretos. Você pode usar um cliente MQTT, como o MQTT Explorer, para monitorar os tópicos e receber os dados dos sensores.

7. Lembre-se de que a segurança do servidor MQTT (autenticação e autorização) é importante para proteger suas comunicações. A configuração específica pode variar dependendo do seu ambiente MQTT.

## Uso

**Controle de Velocidade de Vídeo no Max MSP**
Este projeto foi originalmente desenvolvido para controlar a velocidade de um vídeo no software Max MSP usando a variável videospeed. Você pode integrar o ESP32 com Max MSP para ajustar a velocidade de reprodução de vídeos com base na distância medida pelo sensor VL53L0X. Isso é útil para criar instalações de arte interativas, por exemplo.
O dispositivo coletará dados da distância e velocidade do sensor VL53L0X e publicará esses dados em tópicos MQTT. O tópico MQTT para a velocidade é "sensor/laser_distance/video_speed" e o tópico para a distância é "sensor/laser_distance/video_distance".

## Aplicações Possíveis

Este projeto oferece uma variedade de aplicações relacionadas à natureza e ao monitoramento ambiental:

1. **Monitoramento de Animais Selvagens:** Use o sensor de distância para detectar a presença e a velocidade de animais selvagens em áreas de conservação, como florestas, parques nacionais ou reservas naturais. Isso pode ser útil para estudar o comportamento dos animais e sua interação com o ambiente.

2. **Monitoramento de Ninhos de Pássaros:** Coloque o sensor próximo a ninhos de pássaros para monitorar a entrada e saída de pássaros e calcular a frequência das visitas. Isso pode ser útil para a pesquisa de aves e conservação.

3. **Monitoramento de Fluxo de Rios e Córregos:** Instale o sensor acima de um rio ou córrego para medir a altura da água e calcular o fluxo. Isso é valioso para estudos hidrológicos e pode alertar sobre inundações iminentes.

4. **Medição de Velocidade do Vento:** Configure o sensor de distância para medir a velocidade do vento monitorando a distância até um objeto em movimento devido ao vento, como uma bandeira. Isso pode ser usado para coletar dados meteorológicos em tempo real.

5. **Monitoramento de Crescimento de Plantas:** Coloque o sensor próximo a plantas e use-o para medir o crescimento das plantas à medida que elas se aproximam do sensor. Isso é útil para estudos de botânica e agricultura.

6. **Monitoramento de Insetos Polinizadores:** Configure o sensor perto de flores e monitore insetos polinizadores, como abelhas, para entender padrões de visitação e ajudar na conservação das espécies polinizadoras.

Essas aplicações são apenas algumas ideias para demonstrar como o monitoramento de distância a laser pode ser útil na pesquisa e conservação da natureza. Você pode adaptar o projeto de acordo com suas necessidades específicas e criar soluções personalizadas para monitoramento ambiental e de vida selvagem.

## Contribuição

Sinta-se à vontade para contribuir para o projeto, reportar problemas ou melhorar o código.

## Licença

Este projeto é licenciado sob a [Licença MIT](LICENSE), o que significa que você pode usá-lo livremente e modificar de acordo com suas necessidades.

## Autores

- Emídio Souza
- Agradecimentos especiais à Casa Flusser e a Robson Gregório por sua contribuição no desenvolvimento do projeto.


