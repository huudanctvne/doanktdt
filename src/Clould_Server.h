// Make an HTTP request to the IFTTT web service
#include <Wifi.h>
#include "heltec.h"

const char *resource = "/trigger/temp_system/with/key/cP11-yvqKxFM6DFazeQizv";
const char *server = "maker.ifttt.com";
String stt;

void makeIFTTTRequest()
{
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0))
  {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected())
  {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);
  // Send 
  //String jsonObject = String("{\"value1\":\"") + sData.name + "\",\"value2\":\"" + sData.time + "\",\"value3\":\"" + sData.temp + "\"}"; 
  // String jsonObject = (String("{\"value1\":\"") + sData.name.c_str() + "\",\"value2\":\"" + sData.time.c_str() + "\",\"value3\":\"" + sData.temp + "\"}");
  String jsonObject = (String("{\"value1\":\"") + sData.sID.c_str() + "\",\"value2\":\"" + sData.temp + "\",\"value3\":\"" + stt + "\"}");
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0))
  {
    delay(100);
  }
  if (!!!client.available())
  {
    Serial.println("No response...");
  }
  while (client.available())
  {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}