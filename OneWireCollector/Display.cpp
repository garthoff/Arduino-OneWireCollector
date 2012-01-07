#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Display.h"

#define display Serial1

DisplayClass Display;

DisplayClass::DisplayClass(void) {
    display.begin(9600);
}

void DisplayClass::clear(void) {
    control_sequence(0x01);
}

void DisplayClass::set_cursor_position(byte pos) {
    if (pos >= 16) {
        pos = 64 + pos - 16;
    }
    control_sequence( 0x80 + pos );
}

void DisplayClass::control_sequence(byte b) {
#if defined(ARDUINO) && ARDUINO >= 100
    display.write(0xfe);
    display.write(b);
#else
    display.print( 0xfe, BYTE );
    display.print( b, BYTE );
#endif
}

void DisplayClass::print(char x)          { display.print(x); }
void DisplayClass::print(const char x[])  { display.print(x); }
void DisplayClass::print(uint8_t x)       { display.print(x); }
void DisplayClass::print(int x)           { display.print(x); }
void DisplayClass::print(unsigned int x)  { display.print(x); }
void DisplayClass::print(long x)          { display.print(x); }
void DisplayClass::print(unsigned long x) { display.print(x); }
void DisplayClass::print(long x, int i)   { display.print(x, i); }

