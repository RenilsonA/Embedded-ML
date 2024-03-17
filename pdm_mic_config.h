#define MLE_MICROPHONE_CHANNELS 1                 /** Número de microfones e/ou canais usados no projeto. */
#define MLE_MICROPHONE_SAMPLE_RATE 16000          /** Número de amostras do microfone. */
#define MLE_MICROPHONE_GAIN_DB 30                 /** Decibéis de ganho do microfone. */
#define MLE_MICROPHONE_SAMPLE_BUFFER_SIZE 1024    /** Tamanho do buffer de amostra do áudio. */

/**
 * @brief Função usada para configurar o microfone PDM.
 *
 */
void mle_microphone_pdm_config();

void serial_print();