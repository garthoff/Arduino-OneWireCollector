#ifndef TIMEDSTATE_H
#define TIMEDSTATE_H

class TimedState {
private:
    unsigned long last_activated;
    unsigned long last_tested;
    unsigned long pause;

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
};

#endif
