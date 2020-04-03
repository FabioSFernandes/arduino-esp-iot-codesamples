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