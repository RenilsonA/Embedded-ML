/**
 * @brief Pino conectado ao barramento de dados do sensor.
 *
 */
#define DHTPIN A1

/**
 * @brief Tipo do sensor de temperatura e umidade.
 *
 */
#define DHTTYPE DHT11

/**
 * @brief Função usada para configurar o sensor HTS221.
 *
 */
void mle_temperature_sensor_config();

/**
 * @brief Função usada para pegar dados de temperatura do sensor HTS221.
 *
 * @return Valor da temperatura.
 */
float mle_temperature_sensor_reader();

/**
 * @brief Função usada para pegar dados de umidade do sensor HTS221.
 *
 * @return Valor da umidade.
 */
float mle_humidity_sensor_reader();