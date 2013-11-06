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

#include "Arduino.h"


class wifiDuino
{
  private:
    int DEBUG;
    int _mode;
  public:
    wifiDuino(uint8_t mode, uint8_t debug_flag = 1);
    void changMode(uint8_t mode);
};

#endif
