#include "heltec.h"
#include <HTTPClient.h>
#include <dht_nonblocking.h>
#include <espSend_Receive.h>
#include <OLED.h>
#include <WifiConnect.h>
#include <Clould_Server.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

const int logotime = 500;
int progress;
int i;
// People in Room
const int n = 6;
// Time to sleep
uint64_t uS_TO_S_FACTOR = 1000000; // Conversion factor for micro seconds to seconds
// sleep for 30 minutes = 1800 seconds
uint64_t TIME_TO_SLEEP = 1800;

WiFiClientSecure client;

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    Heltec.begin(true, false, true);

    logo();
    delay(logotime);
    Heltec.display->clear();

    initWifi();

    initESP_Now();
}

void loop()
{
    // updateDisplay();
    Serial.println("INCOMING DATA READINGS");
    Serial.print("ID ");
    Serial.print(sData.sID.c_str());
    Serial.println(" ||");
    Serial.print("Temperature: ");
    Serial.print(sData.temp);
    Serial.println(" ºC");
    Serial.println();

    // LCD
    // Heltec.display->clear();
    Serial.print(n);
    Heltec.display->drawString(0, 0, (String)n);
    Heltec.display->drawString(14, 0, "Data package received");
    Heltec.display->display();
    delay(500);

    if (n == 0)
    {
        Heltec.display->clear();
        Heltec.display->drawString(0, 0, "no people in room");
        Heltec.display->display();
        while (1)
            ;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            sData.id[i] = ID[i];
            sData.temp = (random(35, 40) + (0.01 * random(0, 99)));
            Heltec.display->drawString(0, (i + 1) * 9, (String)(i + 1));
            Heltec.display->drawString(6, (i + 1) * 9, ":");
            Heltec.display->drawString(12, (i + 1) * 9, (sData.id[i].c_str()));
            Heltec.display->drawString(47, (i + 1) * 9, " (");
            Heltec.display->drawString(55, (i + 1) * 9, (String)(sData.temp));
            Heltec.display->drawString(83, (i + 1) * 9, "*C)");
            if ((sData.temp <= 36) || (sData.temp >= 37.8))
            {
                Heltec.display->drawString(105, (i + 1)*9 , "!!!");
            }
            Heltec.display->display();
            delay(100);
            esp_now_register_recv_cb(OnDataRecv);
            sData.sID = sData.id[i];
            if (i == (n - 1))
            {
                stt = "Done!";
            }
            else
            {
                stt = "";
            }

            if ((sData.temp != 0) && (WiFi.status() == WL_CONNECTED))
            {
                makeIFTTTRequest();
            }
            else
            {
                esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&sData, sizeof(sData));
                // Send message via ESP-NOW

                if (result == ESP_OK)
                {
                    Serial.println("Sent with success");
                }
                else
                {
                    Serial.println("Error sending the data");
                }
            }
        }
    }

    delay(20000);
    Heltec.display->clear();
    delay(2000);
    Serial.println("Going to sleep now");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    // ESP.deepSleep(20e6); // deepsleep after 20e6s
}
