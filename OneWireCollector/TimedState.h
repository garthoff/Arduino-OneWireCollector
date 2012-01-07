#ifndef TIMEDSTATE_H
#define TIMEDSTATE_H

class TimedState {
private:
    unsigned long last_activated;
    // not needed any more: unsigned long last_tested;
    unsigned long pause;
    unsigned int nr_activations;

protected:
    int state;

public:
    TimedState(unsigned long pause);
    void tick(void);
    virtual void action(void); // must get overloaded
    
    int pause_is_over(void);
    void set_pause(unsigned long pause = 0);
    
    int get_state(void);
    void set_state(int state = 0, unsigned long pause = 0);
    
    unsigned long get_last_activated(void);
    unsigned int get_nr_activations(void);
};

#endif
