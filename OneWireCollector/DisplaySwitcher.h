#ifndef DISPLAY_SWITCHER_H
#define DISPLAY_SWITCHER_H

#include "Arduino.h"
#include "TimedState.h"

#define DISPLAY_WAIT_TIME 2000

class DisplaySwitcher: public TimedState {
public:
    DisplaySwitcher(unsigned long pause);
    virtual void action(void);
    
    void display_name_and_temperature(char *name, int temperature);

protected:
    int sensor;
};

#endif
