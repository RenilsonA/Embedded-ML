#include <Arduino_APDS9960.h>
#include "light_sensor_config.h"

void mle_light_sensor_config() {
    int err = APDS.begin();
    if (!err) {
        Serial.println("Error initializing APDS9960 sensor!");
        while (1);
    }
}

void mle_light_sensor_reader(int valores[]) {
    while (!APDS.colorAvailable()) {
        delay(5);
    }
    APDS.readColor(valores[0], valores[1], valores[2], valores[3]);
}