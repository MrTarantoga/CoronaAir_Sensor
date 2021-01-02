#include "sensor.h"

Sensor::Sensor(const float temp_offset): temp_offset(temp_offset){
    this->read_data = true;
    this->counter = 200;
    this->copy_data_flag = false;
}

void Sensor::begin(void){
    TWI.begin(D2, D1);
    bme.begin(0x76, &TWI);
    sgp.begin(&TWI);
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                Adafruit_BME280::SAMPLING_X1, // temperature
                Adafruit_BME280::SAMPLING_X1, // pressure
                Adafruit_BME280::SAMPLING_X1, // humidity
                Adafruit_BME280::FILTER_OFF   );
    bme.setTemperatureCompensation(this->temp_offset);
}

uint32_t Sensor::getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void Sensor::read_data_from_sensor(void){
    if(this->read_data){
        sgp.IAQmeasure();
        sgp.IAQmeasureRaw();
        if (counter++ > 20){
            bme.takeForcedMeasurement();
            this->temperature  = bme.readTemperature();
            this->humidity     = bme.readHumidity();
            sgp.setHumidity(getAbsoluteHumidity(this->temperature, this->humidity));
            counter = 0;
        }
        copy_data_flag = true;
        read_data = false;
    }
}

void Sensor::sensor_req(struct sendData *ptr){
    if (copy_data_flag){
        ptr->pressure     = bme.readPressure();
        ptr->TVOC         = sgp.TVOC;
        ptr->eCO2         = sgp.eCO2;
        ptr->raw_Ethanol  = sgp.rawEthanol;
        ptr->raw_H2       = sgp.rawH2;
        ptr->humidity     = this->humidity;
        ptr->temperature  = this->temperature;
        copy_data_flag = false;
    }
}

void Sensor::handle_read_data_from_sensor(void){
    read_data = true;
}