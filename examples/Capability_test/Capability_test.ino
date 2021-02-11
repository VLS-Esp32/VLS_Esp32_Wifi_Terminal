

#include <VLS_Esp32_Wifi_Terminal.h>

#ifdef ESP32
#include <WiFi.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

const char* ssid = "*************";
const char* password = "*************";

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
 
 WifiSerial.println("Hello"); // PrintLn
 
 WifiSerial.print("Hello "); // Print
 WifiSerial.println("Word");
 
 WifiSerial.println(WifiSerial.peek());   //peek
 
 WifiSerial.println(WifiSerial.read()); // read 
 
 
 
 byte buff[8];
 WifiSerial.readBytes(buff,8);
 
 
 WifiSerial.write(buff,8); //read bytes
 
 WifiSerial.write(WifiSerial.getRemoteIP()); // Get remote ip
 
 WifiSerial.write('R'); // Write char
 
 WifiSerial.println(WifiSerial.readString()); //read string
}

}