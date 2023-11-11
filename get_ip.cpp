#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "Arduino_JSON.h"
#include "global.h"
#include "get_ip.h"


String public_ip_addr;

long RAW_OFFSET;
int DST_OFFSET;

void get_ip()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        const String ip_endpoint = "https://ipapi.co/ip/"; // It will return the public IP
        HTTPClient http;
        http.begin(ip_endpoint);
        // To capture the response of the HTTP resonse code,
        // if the value is less than 0, then there is an error in the
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            // Check for the returning code
            String payload = http.getString();
            String public_ip_addr = payload;
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
        http.end(); // Free the resource
    }
    else
    {
        Serial.println("WIFI is not connected");
    }
}

void get_offset()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        const String offset_endpoint = "https://worldtimeapi.org/api/ip/"; // It will return json data
        HTTPClient http;
        http.begin(offset_endpoint + public_ip_addr);
        // To capture the response of the HTTP resonse code,
        // if the value is less than 0, then there is an error in the
        int httpCode = http.GET();

        if (httpCode > 0)
        {
            // Check for the returning code
            String payload = http.getString();
            JSONVar time_object=JSON.parse(payload);
            RAW_OFFSET=time_object["raw_offset"];
            DST_OFFSET=time_object["dst_offset"];
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
        http.end(); // Free the resource
    }
    else
    {
        Serial.println("WiFi is not connected");
    }
}