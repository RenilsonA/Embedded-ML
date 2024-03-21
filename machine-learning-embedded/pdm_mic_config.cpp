#include <PDM.h>
#include "pdm_mic_config.h"

/**
 * Estrutura padrão das variáveis usadas para o microfone.
 */
static struct variables{
    volatile int samplesRead;
    uint16_t sampleBuffer[MLE_MICROPHONE_SAMPLE_BUFFER_SIZE];
} self = {
    .samplesRead = 0,
    .sampleBuffer = {},
};

/**
 * @brief Callback para o microfone.
 *
 */
static void mle_microphone_callback() {
    /** Número de bytes das amostras disponíveis. */
    int bytesAvailable = PDM.available();

    /** Lê o buffer de amostra. */
    PDM.read(self.sampleBuffer, MLE_MICROPHONE_SAMPLE_BUFFER_SIZE);
}

void serial_print(){
    for(int i = 0; i < 16; i++){
        Serial.print(self.sampleBuffer[i]);
        Serial.print(", ");
    }
    Serial.println();
}

void mle_microphone_pdm_config() {
    int err = 0;
    
    /** Callback do microfone. */
    PDM.onReceive(mle_microphone_callback);

    /** Setar um ganho em dB no microfone. */
    PDM.setGain(MLE_MICROPHONE_GAIN_DB);

    /** Iniciar e configurar o canal do microfone. */
    err = PDM.begin(MLE_MICROPHONE_CHANNELS, MLE_MICROPHONE_SAMPLE_RATE);
    if (!err) {
        Serial.println("Failed to start PDM!");
        while (1);
    }
}