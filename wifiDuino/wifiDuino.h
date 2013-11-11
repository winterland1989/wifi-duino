/*
  wifiDuino.h - Library for Wifi-Duino.
  Wifi-Duino is a custmized arduino-compatible prototyping platform, providing wifi conectivity.
  please visiting XXXXXXXXXXXXXXXXXXXXXXXX
  Created by Winterland, November 3, 2013.
  Released under GPLv2.
*/

#ifndef wifiBoard_h
#define wifiBoard_h

#define WIFI_MODE_AP_SERVER 0
#define WIFI_MODE_ADAPTER_SERVER 1
#define WIFI_MODE_ADAPTER_CLIENT 2
#define DHCP_ENABLE 1
#define DHCP_DISABLE 0

#define EXIT_SERIAL_PIN 12

#include "Arduino.h"


static class wifiDuino
{
  public:
    static uint8_t DEBUG;
    static uint8_t MODE;
    static uint8_t DHCP;
    static char ip[16]; 
    static char netmask[16]; 
    static char gateway[16]; 
    static char remoteDomain[30]; 
    static char remotePort[5]; 
    static char localPort[5]; 
    static char uartConfig[15];
    static char wifiSSID[32];
    static char wifiEncrypt[15];
    static char wifiPassword[32];
    
    static void begin();
    static void enterATMode();
    static void enterSerialMode();
    static void writeAPMode();
    static void writeCardMode();
    static void writeDHCP();    
    static void writeWifiConfig();   
    static void writeClientMode();
    static void writeServerMode();
    static void writeLocalIP();
    static void writeLocalPort();
    static void writeRemoteDomain();
    static void writeRemotePort();
    static void writeUartConfig();    
    static void commit();    
    static void waitACK();    
    
    static void getMAC(char* MAC);  
    
}wifiDuino;

#endif
