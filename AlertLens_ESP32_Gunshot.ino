
#include <Arduino.h>
#include <driver/i2s.h>
#include "Gunshot_Detection-1_inferencing.h"  // Replace with your actual model header

#define I2S_SCK  14  // BCLK
#define I2S_WS   15  // LRCL
#define I2S_SD   13  // Data In
#define I2S_PORT I2S_NUM_0

#define TRIGGER_PIN 21
#define AUDIO_BUFFER_SIZE 16000  // Ensure this matches your model's required length

int16_t sampleBuffer[AUDIO_BUFFER_SIZE];

// Signal getter function
int get_signal_data(size_t offset, size_t length, float *out_ptr);

signal_t input_signal;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);

  input_signal.total_length = AUDIO_BUFFER_SIZE;
  input_signal.get_data = get_signal_data;

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = EI_CLASSIFIER_FREQUENCY,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);

  Serial.println("✅ Setup complete. Listening for gunshots...");
}

void loop() {
  size_t bytesRead;
  i2s_read(I2S_PORT, (void *)sampleBuffer, AUDIO_BUFFER_SIZE * sizeof(int16_t), &bytesRead, portMAX_DELAY);

  ei_impulse_result_t result;
  EI_IMPULSE_ERROR res = run_classifier(&input_signal, &result, false);

  if (res == EI_IMPULSE_OK) {
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      Serial.printf("→ %s: %.2f
", result.classification[ix].label, result.classification[ix].value);

      if (strcmp(result.classification[ix].label, "gunshot") == 0 &&
          result.classification[ix].value > 0.36f) {
        Serial.println("🚨 GUNSHOT DETECTED!");
        digitalWrite(TRIGGER_PIN, HIGH);
        delay(200);
        digitalWrite(TRIGGER_PIN, LOW);
      }
    }
  }

  delay(300);
}

int get_signal_data(size_t offset, size_t length, float *out_ptr) {
  if ((offset + length) > AUDIO_BUFFER_SIZE) return -1;
  for (size_t i = 0; i < length; i++) {
    out_ptr[i] = (float)sampleBuffer[offset + i] / 32768.0f;
  }
  return 0;
}
