# FauxmoMKR
[![Build Status](https://travis-ci.com/iregon/fauxmo_mkr1010.svg?branch=master)](https://travis-ci.com/iregon/fauxmo_mkr1010)

Amazon Alexa support for Arduino MKR 1010.

This is a library for Arduino MKR 1010 and Arduino WiFi devices that emulates Philips Hue lights and thus allows you to control them using this protocol, in particular from Alexa-powered devices like the Amazon Echo or the Dot.

## Usage

The library is very easy to use, basically instantiate an object, connect to the Wifi, add one or more virtual devices and bind the callback to get the messages. An schematic example could be:

```cpp
#include <fauxmoMKR.h>

fauxmoMKR fauxmo;

void setup() {

    Serial.begin(115200);

    ... connect to wifi ...

    fauxmo.addDevice("light one");
    fauxmo.addDevice("light two");
    fauxmo.addDevice("light three");
    fauxmo.addDevice("light four");

    fauxmo.setPort(80); // required for gen3 devices
    fauxmo.enable(true);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    });

}

void loop() {
    fauxmo.handle();
}

```

Then run the "discover devices" option from your Alexa app or web (in the Smart Home section). A new device with the name you have configured should appear. Tell Alexa to switch it on or off and check your terminal ;)

## License

FAUXMO MKR

Copyright (C) 2019 by Alessandro Tornesello <alessadnro dot tornesello99 at gmail dot com>

Copyright (C) 2016-2018 by Xose Pérez <xose dot perez at gmail dot com>

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
