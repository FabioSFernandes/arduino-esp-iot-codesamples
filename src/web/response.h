/**
 * @file response.h
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
 * Http response object to handle consumers requests
 */

#include <ESP8266WiFi.h>

class HttpResponse
{
    private:
        WiFiClient _r;
    public:
        HttpResponse(WiFiClient r);
        void Write(char* sAppend);
        void Header();
};

HttpResponse::HttpResponse(WiFiClient r)
{
    _r = r;
}

void HttpResponse::Write(char* aAppend)
{
    _r.write(aAppend);
}

void HttpResponse::Header()
{
    _r.println("HTTP/1.1 200 OK");
    _r.println("Content-type:text/html");
    _r.println("Connection: close");
    _r.println();
}