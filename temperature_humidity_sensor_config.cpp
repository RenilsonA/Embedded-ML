#include <Arduino_HTS221.h>
#include "temperature_humidity_sensor_config.h"

void mle_temperature_sensor_config() {
    int err = HTS.begin();
    if (!err) {
        Serial.println("Failed to initialize humidity temperature sensor!");
        while (1);
    }
}

float mle_temperature_sensor_reader() {
    return HTS.readTemperature();
}

float mle_humidity_sensor_reader() {
    return HTS.readHumidity();
}