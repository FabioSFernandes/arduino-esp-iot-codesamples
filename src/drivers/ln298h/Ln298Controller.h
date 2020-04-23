
// TODO: CIAR CLASSE DE CONTROLE DE MOTOR
// Criar classe que controla os dois motores
// Setagem de pinagem
// Comandos de direção simplificados - direita esquerda frente e ré 

#include <Arduino.h>
#include "../../interfaces/manager.h"

/*static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/

int IN1 = D8;
int IN2 = D7;
// Pinos de controle motor B
int IN3 = D6;
int IN4 = D5;
 
/*void setupMotor()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
}
*/
//int count = 0;
 
/*
void loopMotor()
{
  if (count<=1) { 
   count++;
   //Gira o Motor A no sentido horario
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
   delay(500); //aguarda 2s
   
   //Para o motor A
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, HIGH);
   delay(500);//aguarda 500 ms
   
   //Gira o Motor B no sentido horario
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
   delay(500); //aguarda 2s
   
   //Para o motor B
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, HIGH);
   delay(500);//aguarda 500 ms
  } 
*/

class Ln298Manager: IDeviceManager { 
public: 
    void* start() { 
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
        whellActivate(0,2);
        whellActivate(1,2);
        return NULL;
    }         // returns a start object info 
    bool stop(){ 
        whellActivate(0,2);
        whellActivate(1,2);
        return true;
   }           // just returns a bool if finished succeed
    bool restartDevice(){ 
         start();
         return true;
   }  // similar to "stop + start"
    void* refresh(){ 
        start();
        return NULL;
    }       // refresh device data to get status  
    int getStatus(){ 
        return 0;
    }     // get current status of the device 
    void* getParameters(){ 
        return NULL;
    } // getParameterSettings for the device 
    bool setParameters(void* parameters){ 
        return true;
    } // setParameterSettings for the device 
    bool gofoward(){ 
        leftWhellTo(true);
        rightWhellTo(true);
        return true;
    }
    bool gobackward(){ 
        leftWhellTo(false);
        rightWhellTo(false);
        return true;
    }
    bool turnLeft(){
        leftWhellTo(false, true);
        rightWhellTo(true, true);
        return true;
    }

    bool turnRight(){ 
        leftWhellTo(true, true);
        rightWhellTo(false, true);
        return true;
    }

private:
    bool rightWhellTo(bool runToFront, bool autoPause=false){ 
        if (runToFront) {             
            // Activates motor to front
            whellActivate(0,0);
            if (autoPause) { 
                // Wait 0,1 sec
                delay(100);
                // Stop whell
                whellActivate(0,2);
            }
        }
        else {
            // Activates motor to front
            whellActivate(0,1);
            if (autoPause) { 
                // Wait 0,1 sec
                delay(100);
                // Stop whell
                whellActivate(0,2);
            }
       }
        return true;
    }

    bool leftWhellTo(bool runToFront, bool autoPause=false){ 
        if (runToFront) {             
            // Activates motor to front
            whellActivate(1,0);
            if (autoPause) { 
                // Wait 0,1 sec
                delay(100);
                // Stop whell
                whellActivate(1,2);
            }
        }
        else {
            // Activates motor to front
            whellActivate(1,1);
            if (autoPause) {
                // Wait 0,1 sec
                delay(100);
                // Stop whell
                whellActivate(1,2);
            }
       }
        return true;
    }

    bool whellActivate(int whell, int direction){ 
        int wPin1, wPin2; 
        int sig1, sig2;
        // DEFINE WITCH WHELL TO ACTIVATE
        if (whell==0){ 
            wPin1 = IN1;
            wPin2 = IN2; 
        }
        else { 
            wPin1 = IN3;
            wPin2 = IN4; 
        }
        // DEFINE THE DIRECTION, FOWARD, BACKWARD OR STOP
        switch(direction){ 
            case 0:
                sig1 = HIGH;
                sig2 = LOW;
                break;
            case 1:
                sig1 = LOW;
                sig2 = HIGH;
                break;
            default:
                sig1 = HIGH;
                sig2 = HIGH;
                break;
        }
        //Gira o Motor B no sentido horario
        digitalWrite(wPin1, sig1);
        digitalWrite(wPin2, sig2);
        //delay(500); 

        return true;
    }
};