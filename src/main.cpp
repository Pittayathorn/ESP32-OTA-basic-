
#include <Arduino.h>

#include <WiFi.h>

#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

#define USE_SERIAL Serial

void setup() {

    USE_SERIAL.begin(115200);
    // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.begin("sunny-ap", "6626754555");
    USE_SERIAL.println("version 1.01");

}

void loop() {
    // wait for WiFi connection
    
    if((WiFi.status() == WL_CONNECTED)) {

        t_httpUpdate_return ret = ESPhttpUpdate.update("http://github.com/Pittayathorn/ESP32-OTA-basic-/raw/main/.pio/build/esp32dev/firmware.bin");

        switch(ret) {
            case HTTP_UPDATE_FAILED:
                USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                USE_SERIAL.println("HTTP_UPDATE_OK");
                break;
        }
    }
}