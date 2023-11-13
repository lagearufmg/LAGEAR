# Ativação de Áudio por Sensor de Presença

Este repositório contém o código-fonte Arduino para ativar áudios por meio de sensor de presença. Utiliza-se um ESP32, um módulo DFPlayer Mini e um sensor de presença HC-SR501 PIR. O projeto se chama Sensor Pias pois foi utilizado na região de uma pia, dentro da Igreja de São Gonçalo do Bação. 

## Descrição do Projeto

Este é um projeto simples para Arduino que utiliza o módulo DFPlayer Mini para reprodução de áudio e um sensor de presença para acionar a reprodução quando detecta movimento. Além disso, o código controla um relé para ligar ou desligar um dispositivo externo, de acordo com o tempo de delay indicado.

## Componentes Necessários

- Dispositivo ESP32
- DFPlayer Mini
- Sensor de Presença HC-SR501 PIR

## Biblioteca Necessária

DFPlayerMini_Fast

## Pinagem

- Sensor de presença: Conecte a saída ao pino definido por sensorPin.
- Relé: Conecte a entrada do relé ao pino definido por relayPin.

## Instruções de Uso

- Conecte os componentes de acordo com a pinagem definida no código.
- Certifique-se de ter a biblioteca DFPlayerMini_Fast instalada no seu ambiente de desenvolvimento Arduino.
- Carregue o código para o Arduino Uno.
- Observe o monitor serial para mensagens de depuração.

## Personalizações

- Ajuste o valor de volume do DFPlayer Mini através da função myMP3.volume() no método setup.
- Modifique o número do arquivo de áudio a ser reproduzido através da função myMP3.play() no método loop. Os arquivos devem ser nomeados seguindo o padrão: "0001", "0002" e assim por diante.

## Observações

- Certifique-se de alimentar o DFPlayer Mini corretamente.
- Os atrasos (delay) podem ser ajustados conforme necessário para a duração da reprodução de áudio e para lidar com debounce do sensor.

## Contribuição

Sinta-se à vontade para contribuir para o projeto, reportar problemas ou melhorar o código.

## Licença

Este projeto é licenciado sob a [Licença MIT](LICENSE), o que significa que você pode usá-lo livremente e modificar de acordo com suas necessidades.

## Autores

- Emídio Souza
- Flávio Carvalho
- Agradecimentos especiais à organização do Festival de Inverno de São Gonçalo do Bação.
