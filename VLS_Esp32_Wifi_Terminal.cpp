//////////////////////////
// Esp 32 wifi serial. Created by VLS 
// 10.01.21
// v 1.0.5
// https://github.com/VLS-Esp32/VLS_Esp32_Wifi_Terminal
////////////////////////

#include "VLS_Esp32_Wifi_Terminal.h"

void  WifiTerminal::begin(int port) {     //////////////  Create a WiFi Server  
 if(WiFi.status() == WL_CONNECTED){
   server= WiFiServer(port);
   server.begin();
    SetUdpServer(3283);
   _WorkAlloved=true;   // Allow the recipient to work
   Process();
  }  
} 

void  WifiTerminal::begin() {
    int port=3319;
    begin(port);
 
}

int WifiTerminal::available(){
  Process();
  return _IncomingBufferCurrentPosition;
}

void  WifiTerminal::end() {           //////////////// Closing Socket
  _WorkAlloved=false;
   server.end();
   client.stop();
   for(int i=0;i<1024;i++){
    IncommingBuffer[i]=255;
   }
}




void  WifiTerminal::Process() {
      
 if(_WorkAlloved){
  
  if(!client || !client.connected()){
  client = server.available();   // Listen for incoming clients   
  }
  
   if (client&& client.connected()) {
    if(!Connected){
      Connected=true;
    }
        
    if(client.available()>0){
      if(client.peek()=='\n'){ client.print("OK"); client.stop();}else{            ///////////////If it is a scan packet (Not available)
       _TransmitteInProgress=true; 
      int tmp=client.available();  
      for(int i=_IncomingBufferCurrentPosition; i<tmp+_IncomingBufferCurrentPosition && i<1024;i++){    //////////////Save Data in buffer
        IncommingBuffer[i]=client.read(); 
        //Serial.println("Zlo");
      }
      
      _IncomingBufferCurrentPosition+=tmp;
      _TransmitteInProgress=false;
      }
      
    }
              
   }else{
    
     if(Connected){                                // Client Disconnected
      _IncomingBufferCurrentPosition=0;
      ClearBuffer();
     }
     
     Connected=false;  
   }
 }
 
}

void  WifiTerminal::ClearBuffer(){      /////////////////////////////////Clear all incoming buffer
  
for (int i=0;i<1024;i++){  
  IncommingBuffer[i]=255;
}
}

byte  WifiTerminal::nonProctedRead() {                   /////////////////////Read Byte    
  byte tmp= IncommingBuffer[0];     
  for(int i=1;i<1024;i++){
    IncommingBuffer[i-1]=IncommingBuffer[i];    
  }   
  return tmp; 
}

byte  WifiTerminal::read() {                     /////////////////////Read Byte
  Process();
  flush();
  if(_IncomingBufferCurrentPosition>0){
  byte tmp= IncommingBuffer[0];
   _IncomingBufferCurrentPosition-=1;
   
  for(int i=1;i<1024;i++){
    IncommingBuffer[i-1]=IncommingBuffer[i];
    
  }
  
  return tmp;
  }else{
   return 255; // Buffer if empty
  }
}

byte WifiTerminal::readAdress(int adress){    ////////////// Read byte from adress
  Process();
  if(adress <= _IncomingBufferCurrentPosition){
     return IncommingBuffer[adress];
  }else{
    return 255;
  }
}

byte WifiTerminal::peek(){   ////////////////Peek byte
  Process();
  if(_IncomingBufferCurrentPosition>0){
    return  IncommingBuffer[0];
  }else{
    return  255;
  }
}

void WifiTerminal::readBytes(byte *buf, int length){   ////////////Read buffer
   Process();
  if(_IncomingBufferCurrentPosition>=length){ 
       
    for(int i=0;i<length;i++){
      
      buf[i]=nonProctedRead();
    }      
      _IncomingBufferCurrentPosition-=length;   
  }
}


String WifiTerminal::readString(){ //////////////////////Read string from buffer
  Process();
   if(_IncomingBufferCurrentPosition>0){
  flush();
  String tmp="";
  
  for(int i=0;i<_IncomingBufferCurrentPosition;i++){
    char th= IncommingBuffer[i];
    tmp+= th;
  }
   ClearBuffer();  
   _IncomingBufferCurrentPosition=0;
   
  return tmp;
   }else{
    return "";
   } 
}

void WifiTerminal::flush(){
  while(_TransmitteInProgress);
}

void WifiTerminal::write(byte x){          //////////////////Writing in socket
  if(Connected){
  client.write(x);
  }
}

void WifiTerminal::write(byte buff[],int size){
  if(Connected){
      client.write(buff,size);
      
  }
  }


IPAddress WifiTerminal::getRemoteIP(){
  if(Connected){
    return client.remoteIP();
  }else{
    return  IPAddress(0,0,0,0);
  }
}


void WifiTerminal::print(String data){               //////////////////////Printing
 if(Connected){
  client.print(data);
 }
}

void WifiTerminal::print(int data){
if(Connected){
  client.print(data);
 }  
}

void WifiTerminal::print(float data){
if(Connected){
  client.print(data);
 }  
}

void WifiTerminal::print(char data){
if(Connected){
  client.print(data);
 }  
}

void WifiTerminal::println(String data){                ////////////////////////////New Line Printing
 if(Connected){
  client.println(data);
 }
}

void WifiTerminal::println(int data){
if(Connected){
  client.println(data);
 }  
}

void WifiTerminal::println(float data){
if(Connected){
  client.println(data);
 }  
}

void WifiTerminal::println(char data){
if(Connected){
  client.println(data);
 }  
}

  void WifiTerminal::SetUdpServer(int port){    //Set Up a Broadcast server
    
  if(udpServer.listen(port)) {
    udpServer.onPacket([](AsyncUDPPacket packet) {  // Packet received 
          
            //reply to the client
            if(packet.length()==21){  // Not a random packet?
            packet.printf("I Am Esp 32!");
           // Serial.print("YES"); // DEBUG!
            }
            
        });    
    }    
   }                                      
