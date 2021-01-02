#include <Arduino.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>     
#include <ArduinoJson.h>
#include <core_esp8266_features.h>
#include "sensor.h"
#include "data_transfer.h"
#include "config.h"
extern "C" {
  #include "user_interface.h"
}

// Depend on case. 
Sensor my_sens(-3.0);

DataTransfer send_data(CONNECTION_STRING);
struct sendData data;
os_timer_t timer_update_server, timer_read_sensor;


void ICACHE_RAM_ATTR wrapper_handle_send_data(void){
  send_data.handle_send_data();
}

void ICACHE_RAM_ATTR wrapper_handle_read_data_from_sensor(void){
  my_sens.handle_read_data_from_sensor();
}


void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  WiFiManager wifi_mamanger;
  //wifi_mamanger.setDebugOutput(false);
  wifi_mamanger.autoConnect("A.U.L.A");

  String temp = WiFi.macAddress();
  temp.toCharArray(data.mac_addr,19);

  my_sens.begin();
  os_timer_disarm(&timer_update_server);
  os_timer_setfn(&timer_update_server, (os_timer_func_t *)wrapper_handle_send_data, NULL);
  os_timer_arm(&timer_update_server,1000,true);

  os_timer_disarm(&timer_read_sensor);
  os_timer_setfn(&timer_read_sensor, (os_timer_func_t *)wrapper_handle_read_data_from_sensor, NULL);
  os_timer_arm(&timer_read_sensor,1000,true);

}

void loop() {
  my_sens.read_data_from_sensor();
  my_sens.sensor_req(&data);
  send_data.senData(&data);
  delay(0);
}