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
        cli.write(this->_content.c_str());
        cli.stop();
        Serial.write("...done!");
    }
}