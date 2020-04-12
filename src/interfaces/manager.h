
class IDeviceManager{ 
    virtual void* start();         // returns a start object info 
    virtual bool  stop();           // just returns a bool if finished succeed
    virtual bool  restartDevice();  // similar to "stop + start"
    virtual void* refresh();       // refresh device data to get status  
    virtual int   getStatus();     // get current status of the device 
    virtual void* getParameters(); // getParameterSettings for the device 
    virtual bool  setParameters(void* parameters); // setParameterSettings for the device 
};