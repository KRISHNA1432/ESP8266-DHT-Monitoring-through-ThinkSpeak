  //ESP8266 Talking to Thingspeak
#include <DHT.h> //  DHT.h library
#include <ESP8266WiFi.h> // ESP8266WiFi.h library

#define DHTTYPE  DHT11
const int DHTPIN = D4;
const char* ssid     = "KRISHNA-HP";
const char* password = "zzzzzzzz";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "XKL5YC4NLPLFWOH1";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize sensor
 dht.begin();
  delay(1000);

//  Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    return;
  }

// make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temperature);
  url+="&field2=";
  url+=String(humidity);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(1000);
}
