#include <Arduino.h>
#include <SPIFFS.h>
#include "wifi.h"
#include "get_ip.h"
#include "rtc_esp32.h"
#include "ble_adv.h"

void get_fs_details()
{
    // size of the compiled program
    uint32_t program_size = ESP.getSketchSize();
    // size of the file system
    SPIFFS.totalBytes();
    uint32_t file_system_size = SPIFFS.totalBytes();

    // used size of the file system
    uint32_t file_system_used = SPIFFS.usedBytes();

    // free size in the flash memory
    uint32_t free_size = ESP.getFlashChipSize() - program_size - file_system_size + file_system_used;

    Serial.print("Program size: ");
    Serial.print(program_size);
    Serial.println(" bytes");

    Serial.print("File system size: ");
    Serial.print(file_system_size);
    Serial.println(" bytes");

    Serial.print("File system used: ");
    Serial.print(file_system_used);
    Serial.println(" bytes");

    Serial.print("Free space: ");
    Serial.print(free_size);
    Serial.println(" bytes");

}

void setup() {
  // put your setup code here, to run once:
    wifisetup();
    get_ip();
    get_offset();
    get_rtc_time();
    //get_fs_details();
    ble_advert();
}

void loop() {
  // put your main code here, to run repeatedly:

}
