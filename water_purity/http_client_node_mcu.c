/**
   PostHTTPClient.ino

    Created on: 21.11.2016

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

#include <SoftwareSerial.h>
SoftwareSerial s(D2,D6); // Rx, Tx

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

/* this can be run with an emulated server on host:
        cd esp8266-core-root-dir
        cd tests/host
        make ../../libraries/ESP8266WebServer/examples/PostServer/PostServer
        bin/PostServer/PostServer
   then put your PC's IP address in SERVER_IP below, port 9080 (instead of default 80):
*/
//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define SERVER_IP "192.168.43.10:4000"

#ifndef STASSID
#define STASSID "OnePlus 6T"
#define STAPSK  "binil@9812"
#endif

void setup() {

  USE_SERIAL.begin(115200);
s.begin(9600);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    USE_SERIAL.print(".");
  }
  USE_SERIAL.println("");
  USE_SERIAL.print("Connected! IP address: ");
  USE_SERIAL.println(WiFi.localIP());

}

void loop() {
  recvWithEndMarker();
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/postplain/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    USE_SERIAL.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST(receivedChars);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);
USE_SERIAL.printf(receivedChars);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
      //  const String& payload = http.getString();
      //  USE_SERIAL.println("received payload:\n<<");
      //  USE_SERIAL.println(payload);
      //  USE_SERIAL.println(">>");
      }
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
showNewData();
   delay(1000);
}

// Reading data
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
   s.flush();
    while (s.available() > 0 && newData == false) {
        rc = s.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}
