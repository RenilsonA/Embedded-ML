#include <Arduino_LPS22HB.h>
#include "pressure_sensor_config.h"

void mle_barometric_sensor_config() {
    int err = BARO.begin();
    if (!err) {
        Serial.println("Failed to initialize pressure sensor!");
        while (1);
    }
}

float mle_barometric_sensor_reader() {
    return BARO.readPressure();
 
    //float altitude = 44330 * ( 1 - pow(pressure/101.325, 1/5.255) );
}