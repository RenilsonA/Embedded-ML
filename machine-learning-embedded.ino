#include "pdm_mic_config.h"
#include "light_sensor_config.h"
#include "pressure_sensor_config.h"
#include "temperature_humidity_sensor_config.h"
#include <Arduino_APDS9960.h>
/**
 * Estrutura padrão das variáveis usadas para o microfone.
 */
static struct variables{
    float temperature;
    float humidity;
    int light_values[4];
} self = {
    .temperature = 0,
    .humidity = 0,
    .light_values = {},
};

void setup() {
    Serial.begin(115200);
    while(!Serial);
    mle_microphone_pdm_config();
    mle_barometric_sensor_config();
    //mle_temperature_sensor_config();
    mle_light_sensor_config();
}

void loop(){
    //float temperatura =  mle_temperature_sensor_reader();
    //float umidade = mle_humidity_sensor_reader();
    float pressao = mle_barometric_sensor_reader();
    mle_light_sensor_reader(self.light_values);
    //Serial.print("Temperature = ");
    //Serial.print(temperatura);
    //Serial.println(" °C");
    //Serial.print("Umidade = ");
    //Serial.print(umidade);
    //Serial.println(" %");
    Serial.print("Pressao = ");
    Serial.print(pressao);
    Serial.println(" kPa");
    Serial.print("Light = ");
    Serial.print(self.light_values[0]);
    Serial.print(", ");
    Serial.print(self.light_values[1]);
    Serial.print(", ");
    Serial.print(self.light_values[2]);
    Serial.print(", ");
    Serial.print(self.light_values[3]);
    Serial.print(", ");
    delay(5000);
}