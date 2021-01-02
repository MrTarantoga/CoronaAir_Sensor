#ifndef SEND_DATA_SENSOR_STRUCTURE
#define SEND_DATA_SENSOR_STRUCTURE

struct sendData{
  char mac_addr[19];
  float temperature;
  float humidity;
  float pressure;
  uint16_t raw_H2;
  uint16_t raw_Ethanol;
  uint16_t eCO2;
  uint16_t TVOC;
};

#endif