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

/*UART config*/
char wifiDuino::uartConfig[15] = "115200,8,n,1";

/*wifi SSID config*/
char wifiDuino::wifiSSID[32] = "";

/*
wifi encrypt options:
none:         Open network 
wep_open:     wep encryption，open authentication method 
wep:          wep encryption，encryption authentication 
wpa_tkip:     wpa tkip 
wpa_aes:      wpa aes 
wpa2_tkip:    wpa2 tkip 
wpa2_aes:     wpa2 aes 
wpawpa2_tkip: wpa/wpa2 tkip 
wpawpa2_aes:  wpa/wpa2 aes 
auto:         auto select(default)
*/
char wifiDuino::wifiEncrypt[15] = "auto";

/*wifi password config*/
char wifiDuino::wifiPassword[32] = "";

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
  commit();
  enterSerialMode();
  
  
}
/*Enter AT Command Mode*/
void wifiDuino::enterATMode(){
  pinMode(EXIT_SERIAL_PIN,OUTPUT);
  digitalWrite(EXIT_SERIAL_PIN,LOW);
  delay(300);
  digitalWrite(EXIT_SERIAL_PIN,HIGH);
}
/*Exit AT Command Mode and enter Serial Mode*/
void wifiDuino::enterSerialMode(){
  Serial1.println("at+reconn=1");
}
/*Write wifi config, this will set the parameters for AP Mode / the target parameters for Card Mode*/
void wifiDuino::writeWifiConfig(){
  Serial1.print("at+wifi_config=");
  Serial1.print(wifiSSID);
  Serial1.print(',');
  Serial1.print(wifiEncrypt);
  Serial1.print(',');
  Serial1.println(wifiPassword);
}
/*AP Mode:3, Card Mode 2*/
void wifiDuino::writeAPMode(){
  Serial1.println("at+netmode=3");
}
void wifiDuino::writeCardMode(){
  Serial1.println("at+netmode=2");
}
/*In Card Mode, config DHCP*/
void wifiDuino::writeDHCP(){
  Serial1.print("at+dhcpc=");
  Serial1.println(DHCP);
}  
/*TCP client:Client, TCP server:Server*/
void wifiDuino::writeClientMode(){
  Serial1.println("at+mode=Client");
}
void wifiDuino::writeServerMode(){
  Serial1.println("at+mode=Server");
}
/*In Card Mode, if DHCP not enable, this will set the IP address*/
void wifiDuino::writeLocalIP(){
  Serial1.print("at+net_ip=");
  Serial1.print(ip);
  Serial1.print(',');
  Serial1.print(netmask);
  Serial1.print(',');
  Serial1.print(gateway);
  Serial1.println();
}
/*If used as a TCP server, this will set the server's port, If used as a TCP client, this will set the client's port*/
void wifiDuino::writeLocalPort(){
  Serial1.print("at+Clport=");
  Serial1.println(localPort);
}
/*If used as a TCP client, this will set the remote target's ip*/
void wifiDuino::writeRemoteDomain(){
  Serial1.print("at+remoteip=");
  Serial1.println(remoteDomain);
}
/*If used as a TCP client, this will set the remote target's port*/
void wifiDuino::writeRemotePort(){
  Serial1.print("at+remoteport=");
  Serial1.println(remotePort);
}
/*config UART*/
void wifiDuino::writeUartConfig(){
  Serial1.print("at+uart=");
  Serial1.println(uartConfig);
} 
/*commit all the settings*/
void wifiDuino::commit(){
  Serial1.println("at+net_commit=1");
}   
/*wait for acknowledge*/
void wifiDuino::waitACK(){
}   
