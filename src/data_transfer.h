#ifndef DATA_TRANSFER
#define DATA_TRANSFER

#include <Arduino.h>
#include <ArduinoJson.h>
#include <sensor_data.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


class DataTransfer{
    private:
        HTTPClient client;
        WiFiClient wifi_client;
        volatile unsigned int interval_counter;
        volatile bool send_data;
        StaticJsonDocument<(JSON_ARRAY_SIZE(sizeof(struct sendData)) + JSON_OBJECT_SIZE(1))> serialize_doc;
        const String connection_string;

    public:
        DataTransfer(const String &connection_string);
        bool senData(struct sendData *ptr);
        void handle_send_data(void);
};

#endif