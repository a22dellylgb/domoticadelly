/* Proxecto casa domótica. Práctica 3. Sensor binario: botón e LED 
 Delly Galvan, mayo 2024*/

#include <WiFi.h>
#include <PubSubClient.h>

// Completa cos teus datos:SSID, contrasinal e IP do broker MQTT
const char* ssid = "Domotica";
const char* password = "tecnoteis";
const char* mqtt_server = "192.168.12.61"; 
const char* mqtt_user = "";  // Nombre de usuario MQTT (deja en blanco si no es necesario)
const char* mqtt_password = "";  // Contraseña MQTT (deja en blanco si no es necesario)

const int botonPin = 4; // Pin do pulsador
const int ledPin = 2;    // Pin do LED

WiFiClient espClient1;
PubSubClient client(espClient1);
bool ledAceso = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado á rede WiFi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensaxe recibida desde o topic: ");
  Serial.println(topic);
  Serial.print("Contenido da mensaxe: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "casa/actuadores/led1") {
    Serial.print("Cambiando a saída a  ");
    if(messageTemp == "true"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "false"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexión MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao servidor MQTT");
      client.subscribe("casa/actuadores/led1");
    } else {
      Serial.print("Fallou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando de novo en 5 segundos");
      delay(5000);
    }
  }
}
