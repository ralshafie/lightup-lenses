#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
 
const int buttonPin = 26; 

// variables will change:
int buttonState = 0; 

//LEDS
#define PIN1       33
#define PIN2       32
#define NUMPIXELS 24

Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels


void broadcast(const String &message){
  uint8_t broadcastAddress[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy (&peerInfo.peer_addr,broadcastAddress,6);
  if (!esp_now_is_peer_exist(broadcastAddress)){
    esp_now_add_peer(&peerInfo);
  }
  esp_err_t result1 = esp_now_send(broadcastAddress, (uint8_t *) message.c_str(), message.length());
  if (result1 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

}
 
void setup() {
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
 
  Serial.println();
  Serial.println(WiFi.macAddress());
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // register peer
  esp_now_peer_info_t peerInfo;
   
  //memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
         
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
   pinMode(buttonPin, INPUT_PULLUP);

  pixels1.begin();
  pixels2.begin(); 
}
 
void loop() {
  StaticJsonDocument<2048> doc;
  JsonObject JSONencoder = doc.to<JsonObject>();
  buttonState = digitalRead(buttonPin);

  int redSensorValue = analogRead(32); //27 WORKS
  int greenSensorValue = analogRead(37); //37 WORKS
  int blueSensorValue = analogRead(38); //38 WORKS

  JsonArray dial = JSONencoder.createNestedArray("dial");
 dial.add(redSensorValue);
 dial.add(greenSensorValue); 
 dial.add(blueSensorValue); 
  String StrredSensorValue;
   if (buttonState == HIGH) { 
   
     delay(200); 
 
   }else if (buttonState == LOW) {
    int x = digitalRead(26);
 
      String comma = ",";
      String toSend = redSensorValue + comma + greenSensorValue + comma + blueSensorValue;
      Serial.println(toSend);
      broadcast(toSend);
            

     delay(200); 

     
    
   //}
   }

   serializeJson(JSONencoder,Serial);
}
