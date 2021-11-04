#include <Wifi.h>
#include "heltec.h"

const char *ssid = "Huu Duc CT";
const char *password = "dongianthoi";

void initWifi()
{
    Serial.print("Connecting to Wifi:");
    Serial.print(ssid);
    Heltec.display->drawString(0, 12, "       Connecting to Wifi:");
    Heltec.display->drawString(30, 24, (String)(ssid));
    Heltec.display->display();
    delay(10);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    int timeout = 10 * 4; // 10 seconds
    while (WiFi.status() != WL_CONNECTED && (timeout-- > 0))
    {
        delay(250);
        Serial.print(".");
    }
    Serial.println("");

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Failed to connect, going back to sleep");
    }
    Heltec.display->clear();
    Heltec.display->drawString(0, 24, "            Connected!");
    Heltec.display->display();
    Serial.print("WiFi connected in: ");
    Serial.print(millis());
    Serial.print(", IP address: ");
    Serial.println(WiFi.localIP());
    delay(2000);
    Heltec.display->clear();
}