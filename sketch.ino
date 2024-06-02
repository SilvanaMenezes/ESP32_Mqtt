#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "TS House";
const char* password = "net@2018";

const char* mqtt_server = "public.mqtthq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "info_temperatura";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print(" Status: ");
    Serial.println(WiFi.status());

    if (WiFi.status() == WL_NO_SSID_AVAIL) {
      Serial.println("SSID não disponível!");
      break;
    } else if (WiFi.status() == WL_CONNECT_FAILED) {
      Serial.println("Falha na conexão!");
      break;
    } else if (WiFi.status() == WL_CONNECTION_LOST) {
      Serial.println("Conexão perdida!");
      break;
    } else if (WiFi.status() == WL_DISCONNECTED) {
      Serial.println("Desconectado!");
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Falha na conexão ao WiFi, reiniciando...");
    ESP.restart();
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Função de callback vazia (não utilizada neste exemplo)
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  char tempString[8];
  dtostrf(temperatura, 1, 2, tempString);
  Serial.print("Temperatura: ");
  Serial.println(tempString);
  client.publish(mqtt_topic, tempString);

  delay(10000);
}
