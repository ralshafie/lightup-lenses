#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN1       33
#define PIN2       17
#define NUMPIXELS 24

Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

 
void onReceiveData(const uint8_t *mac, const uint8_t *data, int len) {
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];
  int msgLen = min(ESP_NOW_MAX_DATA_LEN, len);
  strncpy(buffer, (const char *)data, msgLen);

  // Make sure we are null terminated
  buffer[msgLen] = 0;
  String recvd = String(buffer);
  int comma1 = recvd.indexOf(',');
  int comma2 = recvd.indexOf(',', comma1+1); 

  String first = recvd.substring(0,comma1);
  String second = recvd.substring(comma1+1, comma2);
  String third = recvd.substring(comma2+1); 
  
  Serial.println(first.toInt());
  Serial.println(second.toInt());
  Serial.println(third.toInt());
  for(int i=0; i<24; i++){
    pixels1.setPixelColor(i,pixels1.Color(first.toInt(),second.toInt(),third.toInt()));
    pixels1.show();
    pixels2.setPixelColor(i,pixels2.Color(first.toInt(),second.toInt(),third.toInt()));
    pixels2.show();
  }
 
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  pixels1.begin();
  pixels2.begin(); 

  esp_now_register_recv_cb(onReceiveData);
  
}
 
void loop() {}
