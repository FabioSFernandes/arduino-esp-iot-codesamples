#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "esp32_service.h"
#include "../interfaces/manager.h"

/*int ENA = D3; //4;
int IN1 = D2; //0;
int IN2 = D4; //2;

int IN3 = D5; //0;
int IN4 = D6; //2;
*/
//wifi_config *wifi;

/*
IDeviceManager{ 
    virtual void* start();         // returns a start object info 
    virtual bool stop();           // just returns a bool if finished succeed
    virtual bool restartDevice();  // similar to "stop + start"
    virtual void* refresh();       // refresh device data to get status  
    virtual void* getStatus();     // get current status of the device 
    virtual void* getParameters(); // getParameterSettings for the device 
    virtual bool setParameters(void* parameters); // setParameterSettings for the device 
}
*/

class WifiManager: IDeviceManager { 
    wifi_config *wifi;

public: 
    WifiManager(){ 
        wifi = new wifi_config(true); 
    }
    virtual void* start(){
        wifi->start();
        return NULL;
        };  

    virtual bool stop(){
        wifi->stop();
        return true;
        }; 
    virtual bool restartDevice(){
        wifi->stop();
        wifi->start();
        return true;
        }; 
    virtual void* refresh(){
        // Wifi devices work on-line so this one doesn't have
        // sensors readers to update current values 
        return NULL;
        };    
    virtual int getStatus(){
        return wifi->status();
        };    
    virtual void* getParameters(){
        IPAddress ip = wifi->get_ip();
        return (void*)&ip;
        };  
    virtual bool setParameters(void* parameters){
        return true;
        }; 
};
/*
void wifiSetup() {
    Serial.begin(115200);
    wifi = new wifi_config(true); 
    wifi->SetConfig();
}
*/