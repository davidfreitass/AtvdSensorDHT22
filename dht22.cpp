#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHTesp.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define API_KEY "AIzaSyAKxGq25Wal0ywZY0oTAgmbuyRvtWfwSfo"
#define DATABASE_URL "https://atvdsensordht22-default-rtdb.firebaseio.com"

const int DHT_PIN = 4;
DHTesp dhtSensor;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Conectado ao Firebase!");
  } else {
    Serial.printf("Erro ao conectar: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;

  Serial.println("Temperatura: " + String(temperatura, 2) + " °C");
  Serial.println("Umidade: " + String(umidade, 1) + " %");
  Serial.println("---");

  if (Firebase.ready()) {
    if (Firebase.setFloat(fbdo, "/sensores/dht22/temperatura", temperatura)) {
      Serial.println("Temperatura enviada!");
    } else {
      Serial.println("Falha ao enviar temperatura: " + fbdo.errorReason());
    }

    if (Firebase.setFloat(fbdo, "/sensores/dht22/umidade", umidade)) {
      Serial.println("Umidade enviada!");
    } else {
      Serial.println("Falha ao enviar umidade: " + fbdo.errorReason());
    }
  }

  delay(5000);
}

