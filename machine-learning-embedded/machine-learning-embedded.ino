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
    // interpreter = &static_interpreter;
    interpreter->AllocateTensors();
    // TfLiteStatus allocate_status = interpreter->AllocateTensors();

    input = interpreter->input(0);
    output = interpreter->output(0);

    mle_microphone_pdm_config();
    mle_barometric_sensor_config();
    // mle_temperature_sensor_config();
    mle_light_sensor_config();
}

void loop(){
    // float temperatura =  mle_temperature_sensor_reader();
    // float umidade = mle_humidity_sensor_reader();
    // float pressao = mle_barometric_sensor_reader();
    // mle_light_sensor_reader(self.light_values);
    //Serial.print("Temperature = ");
    //Serial.print(temperatura);
    //Serial.println(" °C");
    //Serial.print("Umidade = ");
    //Serial.print(umidade);
    //Serial.println(" %");
    // Serial.print("Pressao = ");
    // Serial.print(pressao);
    // Serial.println(" kPa");
    // Serial.print("Light = ");
    // Serial.print(self.light_values[0]);
    // Serial.print(", ");
    // Serial.print(self.light_values[1]);
    // Serial.print(", ");
    // Serial.print(self.light_values[2]);
    // Serial.print(", ");
    // Serial.print(self.light_values[3]);
    // Serial.print(", ");

    // Alimentar os dados ao modelo
    // input = interpreter->input(0);
    // input->data.f[0] = temperatura;
    // input->data.f[1] = self.light_values[3];
    // input->data.f[2] = umidade;
    // input->data.f[3] = pressao;

    // // Executar o modelo
    // interpreter->Invoke();

    // // Capturar os resultados
    // output = interpreter->output(0);
    // int resultado = static_cast<int>(output->data.f[0]);

    // // Exibir os resultados (substitua por sua implementação)
    // Serial.println(resultado);

    // // Aguardar um intervalo antes de executar a próxima inferência
    // delay(5000);

    // pressao_kpa, temperatura_c, luminosidade_lux, umidade_percentual

    // input = interpreter->input(0);
    // input->data.f[0] = 100.5;
    // input->data.f[1] = 26;
    // input->data.f[2] = 1000;
    // input->data.f[3] = 50;
    // TfLiteStatus invoke_status = interpreter->Invoke();
    // if (invoke_status != kTfLiteOk) {
    //     Serial.println("Erro");
    // }
    // output = interpreter->output(0);
    // int resultado = static_cast<int>(output->data.f[0]);
    // Serial.print(resultado);

    // input = interpreter->input(0);
    // input->data.f[0] = 100.5;
    // input->data.f[1] = 20;
    // input->data.f[2] = 1500;
    // input->data.f[3] = 30;
    // invoke_status = interpreter->Invoke();
    // if (invoke_status != kTfLiteOk) {
    //     Serial.println("Erro");
    // }
    // output = interpreter->output(0);
    // resultado = static_cast<int>(output->data.f[0]);
    // Serial.print(", ");
    // Serial.print(resultado);

    // input = interpreter->input(0);
    // input->data.f[0] = 108.5;
    // input->data.f[1] = 40;
    // input->data.f[2] = 3000;
    // input->data.f[3] = 90;
    // invoke_status = interpreter->Invoke();
    // if (invoke_status != kTfLiteOk) {
    //     Serial.println("Erro");
    // }
    // output = interpreter->output(0);
    // resultado = static_cast<int>(output->data.f[0]);
    // Serial.print(", ");
    // Serial.print(resultado);

    // input = interpreter->input(0);
    // input->data.f[0] = 102;
    // input->data.f[1] = 22;
    // input->data.f[2] = 900;
    // input->data.f[3] = 40;
    // invoke_status = interpreter->Invoke();
    // if (invoke_status != kTfLiteOk) {
    //     Serial.println("Erro");
    // }
    // output = interpreter->output(0);
    // resultado = static_cast<int>(output->data.f[0]);
    // Serial.print(", ");
    // Serial.println(resultado);

    // delay(1000);

    float entrada[12][4] = {
        {101.3,25,1200,90},
        {101.3,32,1000,50},
        {101.3,25,4000,50},
        {101.3,35,2000,20},
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
        // input->data.f[0] = entrada[i][1];
        // input->data.f[1] = entrada[i][3];
        input->data.f[0] = entrada[i][0];
        input->data.f[1] = entrada[i][1];
        input->data.f[2] = entrada[i][2];
        input->data.f[3] = entrada[i][3];

        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
            Serial.println("Erro durante a inferência");
        }

        for (int i = 0; i < NUM_LABELS; i++) {
            Serial.print(LABELS[i]);
            Serial.print(": ");
            Serial.print(static_cast<int>(output->data.f[i]));
            Serial.print(",   ");
        }
        Serial.println();

        // output = interpreter->output(0);
        // int resultado = static_cast<int>(output->data.f[0]);
        // Serial.print(resultado);
        // if (i < 3) {
            // Serial.print(", ");
        // }
    }
    delay(10000);
}