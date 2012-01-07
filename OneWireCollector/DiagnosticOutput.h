#ifndef DIANOSTIC_OUTPUT_H
#define DIANOSTIC_OUTPUT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "TimedState.h"

#define IDLE_WAIT_TIME 10000


class DiagnosticOutput: public TimedState {
public:
    DiagnosticOutput(unsigned long pause);
    virtual void action(void);
    void write_output(void);

protected:
    unsigned long last_checked;
    int nr_overruns;

    void write_diagnostic_output(void);
};


#endif
