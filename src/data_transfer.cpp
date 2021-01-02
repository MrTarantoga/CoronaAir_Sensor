#include <data_transfer.h>

DataTransfer::DataTransfer(const String &connection_string): connection_string(connection_string){
    interval_counter = 0;
    send_data = true;
}

bool DataTransfer::senData(struct sendData *ptr){
    bool retValue = false;
    if (send_data){
        client.begin(wifi_client, this->connection_string);
        serialize_doc.clear();
        serialize_doc["mac_addr"]       = String(ptr->mac_addr);
        serialize_doc["temperature"]    = ptr->temperature;
        serialize_doc["eCO2"]           = ptr->eCO2;
        serialize_doc["raw_Ethanol"]    = ptr->raw_Ethanol;
        serialize_doc["raw_H2"]         = ptr->raw_H2;
        serialize_doc["pressure"]       = ptr->pressure;
        serialize_doc["humidity"]       = ptr->humidity;
        serialize_doc["TVOC"]           = ptr->TVOC;

        String JSONString;
        serializeJson(serialize_doc, JSONString);
        client.addHeader("Content-Type", "application/json");
        unsigned int statusCode = client.POST(JSONString);

        if (statusCode == 200){
            retValue = true;
        }
        client.end();
        send_data = false;
    }
        return retValue;
}

 void DataTransfer::handle_send_data(void){
    if (interval_counter++ >= 60*5){
        send_data = true;
        interval_counter = 0;
    }
 }
