#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Display.h"
#include "DisplaySwitcher.h"

#define noDEBUG

extern int nr_sensors;
extern char* names[];
extern int temperatures[];

DisplaySwitcher::DisplaySwitcher(unsigned long pause): TimedState(pause) {
    sensor = 0;
}

void DisplaySwitcher::action(void) {
    #ifdef DEBUG
    Serial.print("DisplaySwitcher - sensor: ");
    Serial.println(sensor, DEC);
    #endif

    display_name_and_temperature(names[sensor], temperatures[sensor]);
    sensor = (sensor + 1) % nr_sensors;
    
    // set_pause(DISPLAY_WAIT_TIME);
}

void DisplaySwitcher::display_name_and_temperature(char *name, int temperature) {
    char line[17];
    byte i;
    char *c;
    boolean is_negative = temperature < 0;
    boolean is_valid    = abs(temperature) < 99;
  
    c = name;
    for (i = 0; i < 16; i++) {
        line[i] = *c ? *c++ : ' ';
    }
  
    i = 16;
    line[i--] = '\0';
  
    if (is_valid) {
        line[i--] = 'C';
        line[i--] = '\337';
        
        if (is_negative) temperature = -temperature;
        
        do {
            line[i--] = '0' + temperature % 10;
            temperature = temperature / 10;
        } while (temperature && i);
        
        if (is_negative) line[i--] = '-';
    } else {
        while (i > 12) {
            line[i--] = '?';
        }
    }
    line[i--] = ' ';
    
    #ifdef DEBUG
    Serial.print("DisplaySwitcher - display: ");
    Serial.println(line);
    #endif
    
    Display.set_cursor_position(0);
    Display.print(line);
}
