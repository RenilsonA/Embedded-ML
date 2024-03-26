#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"

#include "pdm_mic_config.h"
#include "light_sensor_config.h"
#include "pressure_sensor_config.h"
#include "temperature_humidity_sensor_config.h"
#include "modelo_data.h"

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

namespace {
    const tflite::Model* model = nullptr;
    tflite::AllOpsResolver resolver;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* input = nullptr;
    TfLiteTensor* output = nullptr;
    int inference_count = 0;
    constexpr int kTensorArenaSize = 2000;
    alignas(16) uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

const char* LABELS[] = {
  "toleravel", "intoleravel", "otimo", "bom"
};

#define NUM_LABELS (sizeof(LABELS) / sizeof(LABELS[0]))

void setup() {
    Serial.begin(115200);
    while(!Serial);

    tflite::InitializeTarget();

    model = tflite::GetModel(modelo_tflite);

    interpreter = new tflite::MicroInterpreter(model, resolver, tensor_arena, kTensorArenaSize);
    interpreter->AllocateTensors();

    input = interpreter->input(0);
    output = interpreter->output(0);

    int64_t entrada[12][4] = {
        {101,25,1200,90},
        {101,32,1000,50},
        {101,25,4000,50},
        {101,35,2000,20},
        {100,25,1300,40},
        {101,27,100,50},
        {108,26,1500,60},
        {98,26,1600,60},
        {101,32,1000,10},
        {102,29,3000,20},
        {103,27,3000,60},
        {102,30,3000,80},
    };

    for (int i = 0; i < 12; i++) {
        input = interpreter->input(0);
        input->data.f[0] = entrada[i][0];
        input->data.f[1] = entrada[i][1];
        input->data.f[2] = entrada[i][2];
        input->data.f[3] = entrada[i][3];

        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
            Serial.println("Erro durante a inferência");
        }

        for (int j = 0; j < NUM_LABELS; j++) {
            Serial.print(LABELS[j]);
            Serial.print(": ");
            Serial.print(output->data.f[j], 4);
            if(j < (NUM_LABELS - 1)){
                Serial.print("  //  ");
            }
        }
        Serial.println();
    }

    mle_microphone_pdm_config();
    mle_barometric_sensor_config();
    mle_temperature_sensor_config();
    mle_light_sensor_config();
}

void loop(){
    // float temperatura =  mle_temperature_sensor_reader();
    // float umidade = mle_humidity_sensor_reader();
    // float pressao = mle_barometric_sensor_reader();
    // mle_light_sensor_reader(self.light_values);
    // Serial.print("Temperature = ");
    // Serial.print(temperatura);
    // Serial.println(" °C");
    // Serial.print("Umidade = ");
    // Serial.print(umidade);
    // Serial.println(" %");
    // Serial.print("Pressao = ");
    // Serial.print(pressao);
    // Serial.println(" kPa");
    // Serial.print("Light = ");
    // Serial.println(self.light_values[3]);
    serial_print();

    // input = interpreter->input(0);
    // input->data.f[0] = entrada[i][0];
    // input->data.f[1] = entrada[i][1];
    // input->data.f[2] = entrada[i][2];
    // input->data.f[3] = entrada[i][3];

    // TfLiteStatus invoke_status = interpreter->Invoke();
    // if (invoke_status != kTfLiteOk) {
    //     Serial.println("Erro durante a inferência");
    // }

    // for (int j = 0; j < NUM_LABELS; j++) {
    //     Serial.print(LABELS[j]);
    //     Serial.print(": ");
    //     Serial.print(output->data.f[j], 4);
    //     if(j == (NUM_LABELS - 1)){
    //         Serial.print("  //  ");
    //     }
    // }

    delay(2000);
}