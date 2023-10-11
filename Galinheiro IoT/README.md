# Monitoramento de Galinheiro via MQTT

Este repositório contém o código-fonte Arduino para monitorar o status das galinhas em um poleiro usando MQTT. O código é projetado para rodar em um dispositivo ESP32 e utiliza as bibliotecas WiFiManager para configurar a conexão Wi-Fi e PubSubClient para estabelecer a conexão MQTT.

## Descrição do Projeto

O código consiste em um loop principal que verifica o estado de um botão conectado ao pino 2 (definido como `botaoPoleiro`). Ele publica o status das galinhas (no poleiro ou fora do poleiro) em um tópico MQTT definido como `sensor/poleiro_galinhas` no servidor MQTT especificado.

## Componentes Necessários

- Dispositivo ESP32
- Botão conectado ao pino 2 (ou outro pino de sua escolha)
- Servidor MQTT (endereço IP ou nome de domínio) para publicação dos dados
- Acesso à rede Wi-Fi

## Configuração

Antes de usar o código, é necessário configurar as informações de conexão Wi-Fi e MQTT. As configurações iniciais são definidas como variáveis globais no início do código:

- `mqtt_server`: O endereço IP ou nome de domínio do servidor MQTT.
- `mqtt_port`: A porta MQTT a ser utilizada (padrão é 1883).
- `mqtt_topic`: O tópico MQTT no qual os dados serão publicados.

## Uso

1. Conecte o botão ao pino 2 (ou outro pino de sua escolha) do ESP32.

2. Carregue o código no ESP32 usando a plataforma Arduino.

3. O dispositivo ESP32 criará um ponto de acesso Wi-Fi com o nome "GalinheiroAP". Conecte-se a este ponto de acesso usando um dispositivo móvel ou computador.

4. Abra um navegador e digite "192.168.4.1" na barra de endereço. Isso abrirá a página de configuração do WiFiManager.

5. Configure a conexão Wi-Fi para se conectar à sua rede Wi-Fi. Você também pode fornecer as informações do servidor MQTT, se desejar.

6. Após a configuração bem-sucedida, o dispositivo se conectará à rede Wi-Fi e ao servidor MQTT.

7. O código publicará "1" no tópico MQTT quando o botão estiver pressionado (galinhas no poleiro) e "0" quando o botão estiver solto (galinhas fora do poleiro).

## Observações

- Certifique-se de que a biblioteca `WiFi.h`, `PubSubClient.h`, e `WiFiManager.h` estejam instaladas em sua plataforma Arduino.

- O código foi projetado para uma aplicação de exemplo e pode ser personalizado conforme necessário para atender aos requisitos específicos do seu projeto.

- Certifique-se de que seu servidor MQTT esteja configurado e acessível na rede.

- Este código assume que um servidor MQTT está disponível para receber as mensagens. Certifique-se de que o endereço do servidor MQTT e a porta correspondam às configurações do seu servidor MQTT.

- O código publica mensagens MQTT a cada segundo. Você pode ajustar o intervalo de publicação conforme necessário.

Aproveite o uso deste código para monitorar o status das galinhas em seu galinheiro ou adapte-o para atender a outras necessidades de monitoramento por MQTT.
