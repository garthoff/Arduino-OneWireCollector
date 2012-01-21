#ifndef NETWORK_TRANSPORTER_H
#define NETWORK_TRANSPORTER_H

#include "Arduino.h"
#include "TimedState.h"

#define NET_STATE_SEND 0
#define NET_STATE_RECEIVE 1
#define NET_STATE_CLOSE 2

// send measure every 15 minutes = 900 seconds
// #define NET_WAIT_TIME 900000
#define NET_WAIT_TIME 60000

class NetworkTransporter: public TimedState {
public:
    NetworkTransporter(unsigned long pause);
    virtual void action(void);
    void send(void);
    void receive(void);
};

#endif
