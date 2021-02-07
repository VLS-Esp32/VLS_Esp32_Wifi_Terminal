#include <VLS_Esp32_Wifi_Terminal.h>

#ifdef ESP32
#include <WiFi.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

const char* ssid = "*****";
const char* password = "********";

WifiTerminal WifiSerial;

void setup() {
  Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
// Print local IP address and start server
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

WifiSerial.begin();   // Starting the server
}

void loop() {
  
if(WifiSerial.available()){
  Serial.write(WifiSerial.read());   // From Wifi Serial to serial
}
if(Serial.available()){     // From Serial to  Wifi Serial
  WifiSerial.write(Serial.read());
}

}
