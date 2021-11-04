#include <esp_now.h>
#include "heltec.h"

String success;

uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0xAB, 0x70, 0x1C};
//uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0xAB, 0x70, 0x80};

//std::string ID[] = {"MS007", "MS008", "MS009", "MS010","MS011","MS012"};
std::string ID[] = {"MS001", "MS002", "MS003", "MS004","MS005","MS006"};

typedef struct data
{
  std::string sID;
  std::string id[6];
  float temp;
} data;

data sData;           //data sending

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0)
  {
    success = "Delivery Success :)";
  }
  else
  {
    success = "Delivery Fail :(";
  }
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&sData, incomingData, sizeof(sData));
  Serial.print("Bytes received: ");
  Serial.println(len);

}

void initESP_Now()
{
    if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
