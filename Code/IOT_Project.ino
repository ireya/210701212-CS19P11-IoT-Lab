#define BLYNK_TEMPLATE_ID "TMPL3YpsOAUTW"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitoring System"
#define BLYNK_AUTH_TOKEN "obNeeHX-mk-iHqaZkj3b1VH2vOSfeLgF"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
DHT dht;
int gas_input = 34;
int dht_pin = 4;
int sound_pin = 35;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Reah";
char pass[] = "12345678";

BlynkTimer timer;

void sendSensor() {
  int analog_data = analogRead(gas_input);
  Serial.print("Air Quality: ");
  Serial.println(analog_data); 
  delay(200);
  Blynk.virtualWrite(V0, analog_data);
  double humidity = dht.getHumidity();
  double temperature = dht.getTemperature();
  // Serial.println(temperature);
  delay(200);
  Blynk.virtualWrite(V1, temperature);
  // Serial.println(humidity);
  delay(200);
  Blynk.virtualWrite(V2, humidity);
  int noise_data = analogRead(sound_pin);
  Serial.print("Noise : ");
  Serial.println(noise_data); 
  delay(200);
  Blynk.virtualWrite(V3, noise_data);
  delay(300);

}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.setup(dht_pin);
  timer.setInterval(100L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
