#include "DHT.h"
#include "temperature_humidity_sensor_config.h"

DHT dht(DHTPIN, DHTTYPE);

void mle_temperature_sensor_config() {
    dht.begin();
}

float mle_temperature_sensor_reader() {
    return dht.readTemperature();
}

float mle_humidity_sensor_reader() {
    return dht.readHumidity();
}