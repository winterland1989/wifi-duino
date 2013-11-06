#include "Arduino.h"
#include "wifiDuino.h"

wifiDuino::wifiDuino(uint8_t mode, uint8_t debug_flag){
  if( !Serial || !debug_flag )
    DEBUG = 0;

  if(Serial1){
    Serial1.flush();
    delay(2);
    Serial1.end();
  }
  Serial1.begin(115200); 

  if(DEBUG){
    Serial.println("Starting wifiDuino!");
    Serial.print("Setting Mode:");
  }

  _mode = mode;
  switch(_mode){
    case WIFI_MODE_AP_SERVER:
      Serial.println("AP SERVER");

      break;
    case WIFI_MODE_ADAPTER_SERVER:
      Serial.println("ADAPTER SERVER.");

      break;
    case WIFI_MODE_ADAPTER_CLIENT:
      Serial.println("ADAPTER CLIENT.");

      break;
    default:
      Serial.println("Wrong Mode, wifiDuino not started.");
  }
}

void wifiDuino::changMode(uint8_t mode){

}
