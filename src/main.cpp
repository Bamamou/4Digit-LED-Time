#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFi.h> // for WiFi shield
#include <WiFiUdp.h>
#include "TM1637.h"

const int CLK = 12;            //ESp32 GPIO2
const int DIO = 13;           // ESP32 GPIO4
TM1637 tm;                 // Instantiate a tm object
bool colon = true;
// Replace with your own network credentials
const char* ssid = "FLYRouter-e920";
const char* password = "b33cd675";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      // WiFi.begin("Wokwi-GUEST", "", 6);  // This funtion is used only for Wokwi
      // WiFi.begin(ssid, password);  //call this function when you are using your own network
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnected.");
    //begin the 4 digit led
    tm.begin(CLK, DIO, 4);  //Clock, Data In-Out, digit number
    tm.displayClear();
    tm.setBrightness(7);     // full brightness, default is 3
    // begine the NTPclinet to get time from
    timeClient.begin();
    timeClient.setTimeOffset(3600 * 8); //GMT+8 in Beijing
  }
}

void loop() {
  timeClient.update();
  tm.displayTime(timeClient.getHours(), timeClient.getMinutes(), colon); // display the numbers
  colon = !colon;         // toggle colon
  delay(1000);

}

