#include "WProgram.h"
#include "TimedState.h"

#define noDEBUG

TimedState::TimedState(unsigned long p) {
    state = 0;
    last_activated = 0;
    nr_activations = 0;
    set_pause(p);
}

void TimedState::tick(void) {
    #ifdef xDEBUG
    Serial.print(millis());
    Serial.print(" - TimedState - tick, last_activated: ");
    Serial.print(last_activated, DEC);
    Serial.print(", pause: ");
    Serial.println(pause, DEC);
    #endif

    if (pause_is_over()) {
        #ifdef DEBUG
        Serial.print(millis());
        Serial.print("TimedState - action, last_activated: ");
        Serial.print(last_activated, DEC);
        Serial.print(", pause: ");
        Serial.println(pause, DEC);
        #endif

        action();

        nr_activations++;
        last_activated = millis();
    }
}

void TimedState::action(void) {
    // typically overloaded
}

int TimedState::pause_is_over(void) {
    unsigned long m = millis();
    boolean is_over = false;

    unsigned long next_activation_at = last_activated + pause;

        #ifdef DEBUG
        Serial.print(millis());
        Serial.print("TimedState - pause_is_over?, last_activated: ");
        Serial.print(last_activated, DEC);
        Serial.print(", pause: ");
        Serial.print(pause, DEC);
        Serial.print(", next: ");
        Serial.print(next_activation_at, DEC);
        #endif

    if (last_activated <= m) {
        // timer did not overrun
        if (next_activation_at >= last_activated) {
            // calculated time did not overrun
            is_over = (m >= next_activation_at);

                        #ifdef DEBUG
                        Serial.print(" - CASE A");
                        #endif
        } else {
            // calculated time did overrun
            is_over = false;

                        #ifdef DEBUG
                        Serial.print(" - CASE B");
                        #endif
        }
    } else {
        // timer did overrun
        if (next_activation_at > last_activated) {
            // calculated time did not overrun
            is_over = true;
                        #ifdef DEBUG
                        Serial.print(" - CASE C");
                        #endif
        } else {
            // calculated time did overrun
            is_over = (m >= next_activation_at);
                        #ifdef DEBUG
                        Serial.print(" - CASE D");
                        #endif
        }
    }

    // last_tested = m;

        #ifdef DEBUG
        Serial.print(" , is_over: ");
        Serial.println(is_over, DEC);
        #endif

        return is_over;
}

void TimedState::set_pause(unsigned long p) {
    pause = p;
    last_activated = millis();
    // last_tested = last_activated;
}

int TimedState::get_state(void) {
    return state;
}

void TimedState::set_state(int s, unsigned long p) {
    state = s;
    set_pause(p);
}

unsigned long TimedState::get_last_activated(void) {
    return last_activated;
}

unsigned int TimedState::get_nr_activations(void) {
    return nr_activations;
}
