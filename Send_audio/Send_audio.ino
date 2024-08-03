#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define AUD_IN 36
#define Fs 100 //microseconds of frecuency sample
 
static const char* WIFI_SSID = "TP-VJ";
static const char* WIFI_PASS = "FES38613921";
 
WiFiUDP Udp;

void setup(){
  Serial.begin(115200);
  pinMode(AUD_IN,INPUT);
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.println();
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

int instant;
float prev;
void loop()
{
  Udp.beginPacket("192.168.3.14",4321);
  for(int i=0; i<1500; i++){
    prev=micros();
    instant = int(analogRead(AUD_IN)/8);
    Udp.write(instant);
    while(micros() < Fs + prev);
  }
  Udp.endPacket();
  delay(1);
}
