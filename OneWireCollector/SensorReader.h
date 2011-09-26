#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include "WProgram.h"
#include <OneWire.h>
#include "TimedState.h"

#define READ_STATE_SEND 0
#define READ_STATE_READ 1

#define READ_WAIT_TIME 1000
#define READ_CHARGE_TIME 1000


class SensorReader: public TimedState {
public:
    SensorReader(unsigned long pause);
    virtual void action(void);
    void init_line_and_send_command(void);
    void receive_and_store_temperature(void);

protected:
    int sensor;
};

#endif
