#include <PDM.h>
#include "pdm_mic_config.h"

/**
 * Estrutura padrão das variáveis usadas para o microfone.
 */
static struct variables{
    bool new_sample;
    volatile int samplesRead;
    uint16_t sampleBuffer[MLE_MICROPHONE_SAMPLE_BUFFER_SIZE];
} self = {
    .new_sample = false,
    .samplesRead = 0,
    .sampleBuffer = {},
};

/**
 * @brief Callback para o microfone.
 *
 */
static void mle_microphone_callback() {
    self.new_sample = true;

    /** Número de bytes das amostras disponíveis. */
    self.samplesRead = PDM.available();

    /** Lê o buffer de amostra. */
    PDM.read(self.sampleBuffer, MLE_MICROPHONE_SAMPLE_BUFFER_SIZE);
}

void serial_print(){
    if(self.new_sample){
        self.new_sample = false;
        uint16_t maxAmplitude = 0;
        for (int i = 0; i < self.samplesRead; i++) {
            if (abs(self.sampleBuffer[i]) > maxAmplitude) {
                maxAmplitude = abs(self.sampleBuffer[i]);
            }
        }
        float intensity_dB = 20.0 * log10(maxAmplitude / 32767);
        Serial.print("Intensidade do som em dB SPL: ");
        Serial.println(intensity_dB);

        Serial.print("Intensidade do som em dB SPL: ");
        Serial.println(20.0 * log10(maxAmplitude / 20.0e-6));
    }
    // for(int i = 0; i < 16; i++){
    //     Serial.print(self.sampleBuffer[i]);
    //     Serial.print(", ");
    // }
    // Serial.println();
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