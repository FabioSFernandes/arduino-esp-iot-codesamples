/**
 * @file server.h
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2020, Fabio Fernandes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * @section Description
 * Start server and runs on specific port 
 */

#include <Arduino.h>
#include "./httpserver.h"
//#include "../wifi/esp32_service.h"

/*int ENA = D3; //4;
int IN1 = D2; //0;
int IN2 = D4; //2;

int IN3 = D5; //0;
int IN4 = D6; //2;
*/

HttpServer *http;

//wifi_config *wifi;
String htmlContent="<html><head><//head><body>"\
                                            "<div>"\ 
                                                 "<form action='/left'>"\ 
                                                     "<input type='submit' value='left'//><br//>"\
                                                 "</form>"\ 
                                                 "<form action='/forward'>"\ 
                                                 "</form>"\ 
                                                 "<form action='/right'>"\ 
                                                     "<input type='submit' value='right'/><br//>"\ 
                                                 "</form>"\ 
                                                 "<form action='/forward'>"\ 
                                                     "<input type='submit' value='forward'//><br//>"\ 
                                                 "</form>"\ 
                                                 "<form action='/backward'>"\ 
                                                     "<input type='submit' value='backward'//><br//>"\ 
                                                 "</form>"\ 
                                            "<//div>"\
                            "<//body><//html>";


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

void webSetup() {
    Serial.begin(115200);

    //pinMode(ENA, OUTPUT);
    //pinMode(IN1, OUTPUT);
    //pinMode(IN2, OUTPUT);
    //pinMode(IN3, OUTPUT);
    //pinMode(IN4, OUTPUT);

    // Wifi setup for web server 
    //wifi = new wifi_config(true);
    //wifi->SetConfig();

    // Starts webserver at port 80
    http = new HttpServer(80); 
    // Sets a new html content
    http->set_HTMLContent(htmlContent);
    // Handles a web event as "user action" 
    http->AddEventHandler(&webCommandSent);
}

void webLoop() {
    http->Loop();
}



