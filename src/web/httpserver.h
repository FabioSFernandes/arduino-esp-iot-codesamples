/**
 * @file httpserver.h
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
 * Http Server to handle consumers requests
 */

#include <ESP8266WiFi.h>
#include "response.h"

class HttpServer
{
    private: 
        WiFiServer *srv;
        String request;
        String _content;
        void(*delegate)(HttpServer sender, String eventArgs) = NULL;

    public:
        HttpServer();
        HttpServer(int port);
        void AddEventHandler(void(*eventMethod)(HttpServer sender, String eventArgs));
        void Loop();
        void set_HTMLContent(String content);
        void set_header(String key, String value);
};


HttpServer::HttpServer(int port) 
{
    Serial.println("Starting Server...");
    this->srv = new WiFiServer(port);
    this->srv->begin(port);
    Serial.write("...done!");
}



HttpServer::HttpServer() 
{
    Serial.println("Starting Server...");
    int port = 80;
    this->srv = new WiFiServer(port);
    this->srv->begin(port);
    Serial.write("...done!");
}

void HttpServer::AddEventHandler(void(*eventMethod)(HttpServer sender, String eventArgs))
{
    Serial.println("Add event handler");
    this->delegate = eventMethod;
    Serial.write("...done!");
}

void HttpServer::set_HTMLContent(String newContent)
{
    Serial.println("Set HTML Content");
    this->_content = newContent;
    //this->srv->
    Serial.println(this->_content);
    Serial.write("...done!");
}

void HttpServer::Loop()
{
    //Serial.println("HTTP Loop");
    WiFiClient cli = this->srv->available();
    if (cli) {
        Serial.println("New client available...");
        // A new client making a request 
        while (cli.connected()) {
            Serial.println("HTTP Client Connected");
            // Read the mesage from client 
            request = cli.readString();
            if (request.length() > 0)
            {
                Serial.println("String from client:" + request);
                if (delegate!=NULL)
                {
                    Serial.println("Call Delegate");
                    delegate(*this, request);
                }
                
            }
            break;
        }
        Serial.println("Send content to client...");
        //cli.write("Content-Type: text/html");
        //cli.
         
        cli.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
        cli.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
        cli.println("");
        cli.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML

        cli.write(this->_content.c_str());
        cli.stop();
        Serial.write("...done!");
    }
}