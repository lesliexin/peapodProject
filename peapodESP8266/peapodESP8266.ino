//import all the libraries which will be used
#include "ESP8266WiFi.h"
#include <Time.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

//Change to wifi credentials you will be using
const char* ssid = "iPhone";
const char* password = "Maaran1234!!";

int status = WL_IDLE_STATUS;

String espMAC = (String)(WiFi.macAddress()); //Mac Address of the ESP8266

int numOfSamples = 10; //How many times you want to collect data

String curSSID = "";
String curBSSID = "";
String curRSSI = "";

int numOfNets = 0;

String BssidVal = "";
DynamicJsonBuffer jsonBuffer;
DynamicJsonBuffer jsonBuffer1;
JsonObject& root = jsonBuffer.createObject();  
JsonObject& root1 = jsonBuffer.createObject();

char serverName[] = "10.46.52.20";//change to your serve IP
int serverPort = 80; //change to the port you are using
char pageName[] = "/echo/"; //change to whatever page name you are using
int totalCount = 0;
char params[32];

#define delayMillis 5000UL

unsigned long thisMillis = 0;
unsigned long lastMillis = 0;  

String jsonFinal = "";

WiFiClient client;

void setup() {
  pinMode(0, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.begin(115200);
  Serial.println("Ready");
  boolean readyToScan = true;
  connect();
  Serial.println(WiFi.macAddress());
}

//wifi connect function
void connect(){
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  JsonArray& time = root1.createNestedArray("time");
  //scan the networks
  numOfNets = WiFi.scanNetworks();
  //create an array for times of data collection
  time_t t[numOfSamples];
  //3D arrays for the data collection
  String allBssid[numOfSamples][numOfNets];
  String allSSID[numOfSamples][numOfNets];
  int allRSSIValues[numOfSamples][numOfNets];
  //Use nested for loops to collect data
  if(numOfNets>0){
    for(int i = 0; i<numOfSamples;i++){
      delay(100);
      WiFi.scanNetworks();
      t[i] = now();
      for(int j = 0; j<numOfNets; j++){
        allBssid[i][j] = WiFi.BSSIDstr(j);
        allRSSIValues[i][j] = WiFi.RSSI(j);
        allSSID[i][j] = WiFi.SSID(j);
      }
    }
    //Use similar for loop structure to fill json array
    for(int i = 0; i<numOfSamples; i++){
      JsonArray& Bssid = root.createNestedArray("Bssid");
      JsonArray& Rssi = root.createNestedArray("Rssi");
      for(int j = 0; j<numOfNets; j++){
        BssidVal = (String)(allBssid[i][j]);
        Bssid.add(BssidVal);
        Rssi.add(allRSSIValues[i][j]);
      }
      root.prettyPrintTo(Serial);
      
      if(true)
      {
        sprintf(params,"temp1=%i",totalCount);    
        if(!postPage(serverName,serverPort,pageName,params)) Serial.print(F("Fail "));
        else Serial.print(F("Pass "));
        totalCount++;
        Serial.println(totalCount,DEC);
      }    
    }
  }
}
//post data funtion
byte postPage(char* domainBuffer,int thisPort,char* page,char* thisData)
{
  int inChar;
  char outBuf[64];

  Serial.print(F("connecting..."));
  //if it connects to the server it will 
  if(client.connect(domainBuffer,thisPort) == 1)
  {
    Serial.println(F("connected"));
    
//    sprintf(outBuf,"POST %s HTTP/1.1",page);
//    client.println(outBuf);
//    sprintf(outBuf,"Host: %s",domainBuffer);
//    client.println(outBuf);
//    client.println(F("Connection: close\r\nContent-Type: application/x-www-form-urlencoded"));
//    sprintf(outBuf,"Content-Length: %u\r\n",strlen(thisData));
//    client.println(outBuf);
      
    const char* request = "/URL?query={request:{Header:{Values: 10:10:10:10}}";
    String encRequest = (String)(URLEncode(request));
    String post = "POST " + encRequest + " HTTP/1.1";
    client.print(post);
  }
  else
  {
    Serial.println(F("failed"));
    return 0;
  }

  int connectLoop = 0;
  //waits to recieve something back from the server or else it will time out
  while(client.connected())
  {
    while(client.available())
    {
      inChar = client.read();
      Serial.write(inChar);
      connectLoop = 0;
    }

    delay(1);
    connectLoop++;
    if(connectLoop > 10000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      client.stop();
    }
  }
  Serial.println();
  Serial.println(F("disconnecting."));
  client.stop();
  return 1;
}

//Used to encode URLs
String URLEncode(const char* msg)
{
    const char *hex = "0123456789abcdef";
    String encodedMsg = "";

    while (*msg!='\0'){
        if( ('a' <= *msg && *msg <= 'z')
                || ('A' <= *msg && *msg <= 'Z')
                || ('0' <= *msg && *msg <= '9') ) {
            encodedMsg += *msg;
        } else {
            encodedMsg += '%';
            encodedMsg += hex[*msg >> 4];
            encodedMsg += hex[*msg & 15];
        }
        msg++;
    }
    return encodedMsg;
}
