/*
    ESP8266 WiFi Network Scanner Example
   
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "";   // WiFi SSID
const char* password = ""; // WiFi Password

// Make Account on Cloudmqtt.
// Get your MQTT broker details from cloudmqtt.com
const char* mqttServer = "soldier.cloudmqtt.com";    //Enter Your mqttServer address
const int mqttPort = 10865;       //Port number
const char* mqttUser = "ijqieagt"; //User
const char* mqttPassword ="Sg70cdD1HgD1Fr"; //Password

WiFiClient espClient;
PubSubClient client(espClient);
//=======================================================================
//                     SETUP
//=======================================================================
void setup() {
  Serial.begin(115200);
  Serial.println(""); //Remove garbage

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  //ESP has tendency to store old SSID and PASSword and tries to connect
  delay(100);

  Serial.println("WiFi Netwoek Scan Started");
}

//=======================================================================
//                        LOOP
//=======================================================================
void loop() {
 
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
   
  Serial.println("Scan done");
  
  if (n == 0)
    Serial.println("No Networks Found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      
      //Serial.print(WiFi.BSSIDstr(i));
      if(WiFi.BSSIDstr(i)=="08:E1:25:28:6A:80")// MAC address of attendent's Beacon(wearable Wifi Hotspot)    {
        WiFi.begin(ssid, password);
 
              while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.println("Connecting to WiFi..");
                }
              Serial.print("Connected to WiFi :");
              Serial.println(WiFi.SSID());
              client.setServer(mqttServer, mqttPort);
              while (!client.connected()) {
              Serial.println("Connecting to MQTT...");
            if (client.connect("ESP8266", mqttUser, mqttPassword )) {
             Serial.println("connected");  
             } else {
                    Serial.print("failed with state ");
                    Serial.println(client.state());  //If you get state 5: mismatch in configuration
                    delay(1000);
                    }
             }
              client.publish("test/prod", "Attendent 1 :  1 Floor");
              client.subscribe("test/prod");
              delay(3000);
              WiFi.disconnect();
            }
              delay(10);
            }
  }
  Serial.println("Out Of Loop");

  // Wait a bit before starting New scanning again
  delay(10000);
}
//=======================================================================
