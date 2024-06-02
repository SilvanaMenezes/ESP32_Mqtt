# ESP32 MQTT Sensor de Temperatura

Este é um projeto simples para um sensor de temperatura utilizando um ESP32, um sensor DHT22 e comunicação MQTT para enviar os dados de temperatura para um servidor MQTT.

## Pré-requisitos

- Hardware:
  - ESP32
  - Sensor DHT22
- Bibliotecas:
  - WiFi.h
  - PubSubClient.h
  - DHT.h

## Configuração

1. Conecte o sensor DHT22 ao ESP32. Certifique-se de que o pino do sensor esteja configurado corretamente no código.
2. Altere as constantes `ssid`, `password`, `mqtt_server`, `mqtt_port` e `mqtt_topic` conforme a sua configuração de rede e servidor MQTT.

## Instalação

1. Carregue o código para o ESP32 usando a IDE do Arduino ou outra ferramenta de programação compatível.
2. Abra o monitor serial para visualizar a saída e garantir que o ESP32 esteja conectado à rede Wi-Fi e ao servidor MQTT.

## Uso

O ESP32 irá ler a temperatura do sensor DHT22 a cada 10 segundos e enviar os dados para o servidor MQTT. Você pode monitorar os dados de temperatura usando um cliente MQTT ou integrá-los em outros sistemas.