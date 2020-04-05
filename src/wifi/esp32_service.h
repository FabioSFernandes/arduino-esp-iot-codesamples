#include <ESP8266WiFi.h>
//#include "WiFiEsp.h"

const char* WIFI_SSID     = "XXXXXX";
const char* WIFI_PASSWORD = "XXXXXX";

byte ip_address[] = { 192, 168, 0, 156 }; // Enforced IP Address 
byte gateway[] = { 192, 168,  0,   1 }; // Enforced Gateway 


class wifi_config
{
    char *_ssid = NULL;
    char *_pwd = NULL;
    byte _ip_addr[4] = {0, 0, 0, 0};
    byte _default_gateway[4] =  {0, 0, 0, 0};

    bool _static_config = 0;

    public:
        wifi_config();
        wifi_config(bool static_config);
        wifi_config(char *ssid, char *pwd, byte ip_address[4], byte default_gateway[4]);
        void SetConfig();
        IPAddress get_ip();
};

void wifi_config::SetConfig()
{
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        return;
    }
    
    Serial.println(_ssid);
    Serial.write(_pwd);
    
    if (!_static_config)
    {
        Serial.write("\nBegining static configuration...");
        WiFi.begin(_ssid, _pwd);
    }
    else
    {
        Serial.write("\nBegining dynamic configuration...");
        IPAddress ip(_ip_addr);
        IPAddress gateway(_default_gateway);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.begin(_ssid, _pwd);
        WiFi.config(ip, gateway, subnet); 
    }
    int fcounter = 0;
    Serial.write("\nWaiting for wi-fi connection...");
    while (WiFi.status() != WL_CONNECTED) { 

        fcounter++;
        delay(1000);
        Serial.write(".");
        if (WiFi.status()==WL_CONNECT_FAILED) //||WiFi.status()==WL_CONNECTION_LOST
        {
            Serial.write("\nConnection Failed! Aborting!");
            break;
        }
        else if (WiFi.status()==WL_CONNECTION_LOST) //||WiFi.status()==WL_CONNECTION_LOST
        {
            Serial.write("\nConnection Lost!");
            break;
        }
        else if ( (fcounter % 10) == 0)
        {
            Serial.println(WiFi.status());
        }
    }
    Serial.write("...ready:  IP ");
    Serial.println(get_ip());
    
}

wifi_config::wifi_config( )
{
    _static_config = false;
}

wifi_config::wifi_config( bool static_config )
{
    _static_config = static_config;

    if (_static_config)
    {
        _ssid = (char *)WIFI_SSID;
        _pwd = (char *)WIFI_PASSWORD;
        _ip_addr[0] = ip_address[0];
        _ip_addr[1] = ip_address[1];
        _ip_addr[2] = ip_address[2];
        _ip_addr[3] = ip_address[3];
        _default_gateway[0] = gateway[0];
        _default_gateway[1] = gateway[1];
        _default_gateway[2] = gateway[2];
        _default_gateway[3] = gateway[3];
        
        char msg[20];
        sprintf(msg,"%0d.%0d.%0d.%0d\n",_ip_addr[0],_ip_addr[1],_ip_addr[2],_ip_addr[3]);
        Serial.write("\nTrying static IP configuration...:");
        Serial.write(msg);
    }
}

wifi_config::wifi_config(char *ssid, char *pwd, byte ip_address[4], byte default_gateway[4] )
{
    _ssid = (char *)ssid;
    _pwd = (char *)pwd;
    _ip_addr[0] = ip_address[0];
    _ip_addr[1] = ip_address[1];
    _ip_addr[2] = ip_address[2];
    _ip_addr[3] = ip_address[3];

    _default_gateway[0] = default_gateway[0];
    _default_gateway[1] = default_gateway[1];
    _default_gateway[2] = default_gateway[2];
    _default_gateway[3] = default_gateway[3];
}

IPAddress wifi_config::get_ip()
{
    return WiFi.localIP();
}
