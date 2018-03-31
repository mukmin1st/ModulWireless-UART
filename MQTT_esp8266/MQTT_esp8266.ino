#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "skripsi";
const char* password = "admin123";
const char* mqtt_server = "ngehubx.online";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup(){
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println("0"); //pesan connecting wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   
  } 
  Serial.println("1"); //pesan wifi connected
}


void reconnect() {
  while (!client.connected()) {
    if (debug) Serial.print("Attempting MQTT connection...");
    Serial.println("2"); //pesan connecting broker
    if (client.connect("ESP8266Client")) {   
      Serial.println("3"); //pesan connected broker
    } else {
      Serial.println("4"); //pesan error connection
      delay(4000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    if (Serial.available() > 0) {
      value = Serial.parseInt();   
      snprintf (msg, 50, "Accepted : %ld", value);
      client.publish("skripsi/esp8266", msg);
    }
  }
}
