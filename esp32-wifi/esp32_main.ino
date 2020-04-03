#include <Arduino.h>
#include "service.h"


int ENA = D3; //4;
int IN1 = D2; //0;
int IN2 = D4; //2;

int IN3 = D5; //0;
int IN4 = D6; //2;


wifi_config *wifi;

void setup() {
    Serial.begin(115200);

    // ensure motors are turned off
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);    

    wifi = new wifi_config(true); 
    wifi->SetConfig();

}

void loop() {
    // put your main code here, to run repeatedly:
    //http->
}