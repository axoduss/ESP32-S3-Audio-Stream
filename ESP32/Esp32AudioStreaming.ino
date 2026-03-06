/*
 * ESP32-S3 + INMP441 → UDP Audio Streaming
 * Compatibile con Arduino Core ESP32 3.x
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <driver/i2s.h>

// 🔐 Configurazione WiFi
const char* ssid = "YOUR-SSD";
const char* password = "YOUR-PASSWORD";

// 🎯 Configurazione UDP (IP del tuo PC)
const char* udpAddress = "192.168.1.8";  // ← MODIFICA con IP del tuo PC
const int udpPort = 9000;

// 🎙️ Pin INMP441
#define I2S_WS 1
#define I2S_SD 2
#define I2S_SCK 42
#define I2S_PORT I2S_NUM_0

// ⚙️ Parametri audio
#define SAMPLE_RATE 16000
#define BUFFER_SAMPLES 256
#define BUFFER_BYTES (BUFFER_SAMPLES * 2)
int16_t audioBuffer[BUFFER_SAMPLES];

WiFiUDP udp;

// ================= I2S Setup =================
void i2s_install() {
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_SAMPLES,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  i2s_set_pin(I2S_PORT, &pin_config);
}

// ================= Invia pacchetto UDP =================
void sendAudioPacket() {
  udp.beginPacket(udpAddress, udpPort);
  udp.write((uint8_t*)audioBuffer, BUFFER_BYTES);
  udp.endPacket();
}

// ================= Setup =================
void setup() {
  Serial.begin(115200);
  Serial.println("\n🎙️ ESP32-S3 Audio Streamer UDP");
  
  // WiFi
  Serial.print("📡 Connessione a "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connesso!");
  Serial.print("📍 IP ESP32: "); Serial.println(WiFi.localIP());
  
  // I2S
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  Serial.println("🔊 I2S avviato");
  
  // UDP ✅ CORRETTO: passa la porta come argomento
  udp.begin(udpPort);  // ← QUI ERA L'ERRORE!
  Serial.print("📤 Streaming UDP verso "); 
  Serial.print(udpAddress); Serial.print(":"); Serial.println(udpPort);
  
  delay(1000);
}

// ================= Loop =================
void loop() {
  size_t bytesRead = 0;
  esp_err_t result = i2s_read(I2S_PORT, audioBuffer, BUFFER_BYTES, &bytesRead, portMAX_DELAY);
  
  if (result == ESP_OK && bytesRead > 0) {
    sendAudioPacket();
  }
}