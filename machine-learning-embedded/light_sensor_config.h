/**
 * @brief Função usada para configurar o sensor APDS9960 para luz.
 *
 */
void mle_light_sensor_config();

/**
 * @brief Função usada para pegar dados de luz ambiente.
 *
 * @return Ponteiro contendo a intensidade das cores e da luz, seguindo: Vermelho, Verde, Azul e a Intensidade luminosa.
 */
void mle_light_sensor_reader(int valores[]);