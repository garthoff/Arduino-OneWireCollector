#ifndef NETWORK_TRANSPORTER_H
#define NETWORK_TRANSPORTER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "TimedState.h"

#define NET_STATE_SEND 0
#define NET_STATE_RECEIVE 1
#define NET_STATE_CLOSE 2

// send measure every 15 minutes = 900 seconds
#define NET_WAIT_TIME 900000

class NetworkTransporter: public TimedState {
public:
    NetworkTransporter(unsigned long pause);
    virtual void action(void);
    void send(void);
    void receive(void);
};

#endif
