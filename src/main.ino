#include <Arduino.h>

// FIXME resolve travis macro problem
#undef max
#undef min

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

void callback(unsigned char device_id, const char * device_name, bool state, unsigned char value) {
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
  fauxmo.onSetState(callback);

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