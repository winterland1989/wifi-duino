#include "Arduino.h"
#include "wifiDuino.h"

uint8_t wifiDuino::DEBUG = 0;
uint8_t wifiDuino::MODE = WIFI_MODE_AP_SERVER;
uint8_t wifiDuino::DHCP = 0;
char wifiDuino::ip[16] = "192.168.1.154"; 
char wifiDuino::netmask[16] = "255.255.255.0"; 
char wifiDuino::gateway[16] = "192.168.1.1"; 

char wifiDuino::remoteDomain[30] ="www.baidu.com"; 
char wifiDuino::remotePort[5] = "8080";
char wifiDuino::localPort[5] = "3136";

char wifiDuino::uartConfig[15] = "115200,8,n,1";

void wifiDuino::begin(){

  if(DEBUG){
    Serial.println("Starting WifiDuino!");
    Serial.print("Setting Mode:");
  }
  
  if(Serial1){
    Serial1.flush();
    delay (2);
    Serial1.end();
  }
  Serial1.begin(115200);
  delay(100);
  enterATMode();
  if(MODE == WIFI_MODE_AP_SERVER){
    writeAPMode();
    writeServerMode();
    
  }
  else if(MODE == WIFI_MODE_ADAPTER_SERVER){
    writeCardMode();
    writeDHCP();
    if(!DHCP) writeLocalIP();
    writeServerMode();
  }else if(MODE == WIFI_MODE_ADAPTER_CLIENT){
    writeCardMode();
    writeDHCP();
    if(!DHCP) writeLocalIP();
    writeClientMode();
    writeRemoteDomain();
    writeRemotePort();
    writeLocalPort();
  }
  writeUartConfig();
  Commit();
  enterSerialMode();
  
  
}
void wifiDuino::enterATMode(){
  pinMode(EXIT_SERIAL_PIN,OUTPUT);
  digitalWrite(EXIT_SERIAL_PIN,LOW);
  delay(300);
  digitalWrite(EXIT_SERIAL_PIN,HIGH);
}
void wifiDuino::enterSerialMode(){
  Serial1.println("at+reconn=1");
}
void wifiDuino::writeAPMode(){
  Serial1.println("at+netmode=3");
}
void wifiDuino::writeCardMode(){
  Serial1.println("at+netmode=2");
}
void wifiDuino::writeDHCP(){
  Serial1.print("at+dhcpc=");
  Serial1.println(DHCP);
}  
void wifiDuino::writeClientMode(){
  Serial1.println("at+mode=Client");
}
void wifiDuino::writeServerMode(){
  Serial1.println("at+mode=Server");
}
void wifiDuino::writeLocalIP(){
  Serial1.print("at+net_ip=");
  Serial1.print(ip);
  Serial1.print(',');
  Serial1.print(netmask);
  Serial1.print(',');
  Serial1.print(gateway);
  Serial1.println();
}
void wifiDuino::writeLocalPort(){
  Serial1.print("at+Clport=");
  Serial1.println(localPort);
}
void wifiDuino::writeRemoteDomain(){
  Serial1.print("at+remoteip=");
  Serial1.println(remoteDomain);
}
void wifiDuino::writeRemotePort(){
  Serial1.print("at+remoteport=");
  Serial1.println(remotePort);
}
void wifiDuino::writeUartConfig(){
  Serial1.print("at+uart=");
  Serial1.println(uartConfig);
} 
void wifiDuino::Commit(){
  Serial1.println("at+net_commit=1");
}   