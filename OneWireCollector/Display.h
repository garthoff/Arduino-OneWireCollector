#ifndef DISPLAY_H
#define DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class DisplayClass {
public:
    DisplayClass(void);
    void clear(void);
    void set_cursor_position(byte pos);
    void control_sequence(byte b);
    
    void print(char c);
    void print(const char str[]);
    void print(uint8_t c);
    void print(int i);
    void print(unsigned int i);
    void print(long l);
    void print(unsigned long l);
    void print(long l, int i);
};

extern DisplayClass Display;

#endif
