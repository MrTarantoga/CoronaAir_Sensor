#ifndef SENSOR_HANDLE
#define SENSOR_HANDLE

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>
#include <Adafruit_BME280.h>
#include <sensor_data.h>

class Sensor{
    private:
      Adafruit_BME280 bme; // I2C
      Adafruit_SGP30 sgp;
      TwoWire TWI;

      float humidity, temperature;
      void task(void);
      uint32_t getAbsoluteHumidity(float temperature, float humidity);
      volatile bool read_data; 
      unsigned short counter;
      bool copy_data_flag;
      const float temp_offset;

    public:
      Sensor(const float temp_offset);
      void begin(void);
      void handle_read_data_from_sensor(void);
      void read_data_from_sensor(void);
      void sensor_req(struct sendData * ptr);
    
};

#endif