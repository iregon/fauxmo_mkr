//********************************************************************************************
// 
// This program is one of two programs that connects the Amazon Alexa using WiFi to a Arduino MKR 1010
// Development Board (NDB). The NDB uses the coded unique devices to trap unique characters and 
// TX them to the Arduino Uno for processing. A Voltage Converter is necessary to up-convert the 
// NDB's 3 volt pinout to the 5 volt Arduino Uno's pin voltage. Depending on the character sent 
// to the Arduino Uno the EasyVR 3 module will say a verbal Alexa command..."Alexa, Turn Light One On".
// The device "Light One" is defined when the NDB logs into and connects the local WiFi network and 
// the Amazon Alexa. A device list can be displayed using the Amazon Alexa phone app. Once a verbal
// command is given the Alexa WiFi's the command including the device id to the NDB to start 
// the entire process over.
//
// Two (2) programs are required:  Generated_EasyVR_Audio_Sketch.ino and Final_NodeMCU_TX_Sketch.ino
//
// Watch my videos on YouTube and search by entering "Scott Mon". Thanks.
//
// Notes:
// Github MQTT libararies for Arduino...
// 
// https://github.com/knolleary/pubsubclient
// 
// https://github.com/mqtt/mqtt.github.io/wiki/software?id=software
// ________________________________________________________________________________
//********************************************************************************************
//------------------------------------------------------------------------------
// Say for lights 1-4: ... "Alexa, light 2 off."
//                         "Alexa, light 2 on."
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <WiFiNINA.h> //Required for Arduino MKR 1010 WiFi commnunication.
#include "fauxmoMKR.h"    //This is the library that creates Amazon Alexa device ids and connects to Alexa.
//#include "credentials.h"  //This was hard coded below and this #include was removed. It contained the SSID and Password.

#define SERIAL_BAUDRATE                 9600
#define LED                             LED_BUILTIN  //was 2.
#define WIFI_SSID ""      //WiFi router ID.
#define WIFI_PASS ""      //WiFi router password.

//WiFiClient client = WiFiClient();

fauxmoMKR fauxmo; //Create fauxmo entity.

int HoldDevID = 999; //Used to pass the device_id value outside the function call. This allows it to be used inside the loop process.

// -----------------------------------------------------------------------------
// Wifi
// This is the handshaking required to connect the Arduino MKR 1010 dev. board to the Amazon Alexa.
// -----------------------------------------------------------------------------

void wifiSetup() {

  // Connect to local WiFi.
  Serial.print("[WIFI] Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait for connected status.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.print("[WIFI] STATION Mode, SSID: ");
  Serial.print(WiFi.SSID);
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP);
}

void callback(unsigned char device_id, const char * device_name, bool state) {
  Serial.print("[MAIN] Device #");
  Serial.print(device_id);
  Serial.print(" (");
  Serial.print(device_name);
  Serial.print(") state: %s"); 
  Serial.println(state ? "ON" : "OFF"); //Each device can be ON or OFF.
  HoldDevID = device_id; //Use device_id as a control code. Must store device_id value to use in LOOP. 
}

void setup() {

  // Init serial ports. 
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // Wifi initialization.
  wifiSetup();

  // LED setup. Did not use.
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  // Fauxmo device id setup.
  fauxmo.addDevice("light one");  //This is device id=0.
  fauxmo.addDevice("light two");  //This is device id=1.
  fauxmo.addDevice("light three"); //This is device id=2.
  fauxmo.addDevice("light four"); //This is device id=3.

  // fauxmoMKR 2.0.0 has changed the callback signature to add the device_id, this WARRANTY
  // it's easier to match devices to action without having to compare strings.
  fauxmo.onMessage(callback);

}

void loop() {

  fauxmo.handle();

  // TODO 
  // Print out Arduino MKR 1010 status.
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    // Serial.print("[MAIN] Free heap: %d bytes\n");
    // Serial.println(ESP.getFreeHeap())

  }// End if.
  
// Check if the device is Light One. If it is then send an "A" to the Arduino Uno.
  if (HoldDevID == 0) {
    Serial.println("Now sending 'A'...");
    // Serial1.print('A');
    delay(2000);
  }//End if.

// Check if the device is Light Two. If it is then send a "B" to the Arduino Uno.
  if (HoldDevID == 1) {
    Serial.println("Now sending 'B'...");
    // Serial1.print('B');
    delay(2000);
  }//End if.

}//End Loop.