#include <Arduino.h>
#include<time.h>
#include<WiFi.h>
#include "global.h"
#include<ESP32Time.h>
#include "rtc_esp32.h"

const char* ntp_server="pool.ntp.org";
ESP32Time rtc;

void print_local_time()
{
    Serial.println("inside print");
    while (1){
        Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
        delay(1000);
    }
}

void get_rtc_time()
{
    if(WiFi.status()==WL_CONNECTED){
        configTime(RAW_OFFSET, DST_OFFSET, ntp_server);
        struct tm timeinfo;
        if(getLocalTime(&timeinfo)){
            rtc.setTimeStruct(timeinfo);
        }
        //print_local_time();
    }
    else{
        Serial.println("WiFi is not connected");
    }
}