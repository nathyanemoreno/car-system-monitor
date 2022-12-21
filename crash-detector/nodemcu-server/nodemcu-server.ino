#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>

using namespace std;

#define arduinoSlave 8

#ifndef STASSID
// #define STASSID "iPhone de Nathyane"
#define STASSID "WESTEROS"
// #define STAPSK "13579_#%"
#define STAPSK "lumusmaxima"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WiFiMulti WiFiMulti;

WiFiClient client;

void setup() {
  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  if (WiFi.getMode() & WIFI_AP) {
    WiFi.softAPdisconnect(true);
  }

  WiFiMulti.addAP(ssid, password);


  //WiFi.disconnect();
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(SDA, SCL);
}


unsigned long messageTimestamp = 0;

JsonObject parseQuery(JsonObject json, String s, String delimitor, String separator) {
  String pair;
  String token;
  size_t pairPos = 0;
  size_t tokenPos = 0;
  while ((pairPos = s.indexOf(delimitor)) != -1) {
    pair = s.substring(0, pairPos);

    while ((tokenPos = pair.indexOf(separator)) != -1) {
      token = pair.substring(0, tokenPos);
      // Token
      Serial.println(token);
      pair.remove(0, tokenPos + separator.length());
    }
    // Value for token
    // Serial.println(pair);
    json[token] = pair;

    s.remove(0, pairPos + delimitor.length());
  }
  return json;
}


// JsonObject parseQuery(JsonObject json, String s, String delimitor) {
//   String pair;
//   String token;
//   size_t pairPos = 0;
//   size_t tokenPos = 0;
//   while ((pairPos = s.indexOf(delimitor)) != -1) {
//     pair = s.substring(0, pairPos);
//     Serial.println(pair);
//     s.remove(0, pairPos + delimitor.length());
//     json[pair] = s;

//     Serial.println(s);
//   }
//   return json;
// }
// String data = Wire.readString();

void loop() {

  if (!client.connect("192.168.100.7", 5000)) {
    Serial.println("Not connected");
    delay(100);
    return;
  }

  Serial.println("Connected");
  delay(100);

  Wire.requestFrom(arduinoSlave, 30);

  while (Wire.available()) {
    String data = Wire.readString();

    delay(100);

    uint64_t now = millis();

    if (now - messageTimestamp > 10000) {
      messageTimestamp = now;

      // creat JSON message for Socket.IO (event)
      DynamicJsonDocument doc(200);
      JsonArray array = doc.to<JsonArray>();

      // socket.on('event_name', ....
      array.add("Car1");

      // add payload (parameters) for the event
      JsonObject params = array.createNestedObject();
      parseQuery(params, data, "&", "=");

      // JSON to String (serializion)
      String output;
      serializeJson(doc, output);

      // Send event
      // socketIO.sendEVENT("lajlhahsdkh");
      client.write(output.c_str());
    }
  }
}
