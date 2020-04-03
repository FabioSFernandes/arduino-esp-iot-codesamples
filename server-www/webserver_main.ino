#include <Arduino.h>
#include "httpserver.h"
#include "..\\..\\nodemcu_wifi_tools\\src\\service.h"
int ENA = D3; //4;
int IN1 = D2; //0;
int IN2 = D4; //2;

int IN3 = D5; //0;
int IN4 = D6; //2;

HttpServer *http;

wifi_config *wifi;
String htmlContent="<html><head><//head><body>" \
                                            "<div>" \ 
                                                 "<form action='/left'>" \ 
                                                     "<input type='submit' value='left'//><br//>" \
                                                 "</form>" \ 
                                                 "<form action='/forward'>" \ 
                                                 "</form>" \ 
                                                 "<form action='/right'>" \ 
                                                     "<input type='submit' value='right'/><br//>" \ 
                                                 "</form>" \ 
                                                 "<form action='/forward'>" \ 
                                                     "<input type='submit' value='forward'//><br//>" \ 
                                                 "</form>" \ 
                                                 "<form action='/backward'>" \ 
                                                     "<input type='submit' value='backward'//><br//>" \ 
                                                 "</form>" \ 
                                            "<//div>" \
                            "<//body><//html>";


void setup() {
    Serial.begin(115200);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Wifi setup for web server 
    wifi = new wifi_config(true);
    wifi->SetConfig();

    // Starts webserver at port 80
    http = new HttpServer(80); 
    // Sets a new html content
    http->set_HTMLContent(htmlContent);
    // Handles a web event as "user action" 
    http->AddEventHandler(&webCommandSent);
}

void loop() {
    http->Loop();
}

void webCommandSent(HttpServer sender, String eventArgs)
{
    Serial.println("Novo evento HTTP:");
    Serial.println(eventArgs);

    // Do something with event
    if (eventArgs!=NULL)
    {
        if (eventArgs.indexOf("forward") >= 0) {
            // do something
        }
        else if (eventArgs.indexOf("backward") >= 0) {
            // do something
        }
        else if (eventArgs.indexOf("left") >= 0) {
            // do something
        }
        else if (eventArgs.indexOf("right") >= 0) {
            // do something
        }
    }
}