#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "TFT_eSPI.h";

TFT_eSPI tft = TFT_eSPI();

const char* ssid     = "Swiss Bank";
const char* password = "macintosh";
#define NTP_OFFSET  19800 // In seconds 
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "in.pool.ntp.org"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void setup()
{
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  pinMode(0, INPUT_PULLUP);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    tft.fillScreen(TFT_RED);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.print("Wifi not connected!!");

    tft.setCursor(0, 50);
    tft.setTextSize(2);
    tft.print("Press reset");



  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  tft.fillScreen(TFT_BLACK);
  tft.fillRectVGradient(0, 0, 1000, 200, TFT_WHITE, TFT_BLUE);
  timeClient.begin();

}


void showTime() {
  timeClient.update();
  String ft = timeClient.getFormattedTime();
  tft.setTextSize(3);
  tft.setCursor(50, 50);
  tft.println(ft);
}


void loop()
{
  timeClient.update();
  String ft = timeClient.getFormattedTime();

  showTime();





}
