#include "WProgram.h"
#include "SensorReader.h"

#define noDEBUG

extern int nr_sensors;
extern int lines[];
extern int temperatures[];

OneWire wire(42);

SensorReader::SensorReader(unsigned long pause) :TimedState(pause) {
    sensor = 0;
    //wire = ds;
}

void SensorReader::action(void) {
    #ifdef DEBUG
    Serial.println("SensorReader - action");
    #endif

    switch (state) {
        case READ_STATE_SEND: init_line_and_send_command(); break;
        case READ_STATE_READ: receive_and_store_temperature(); break;
        default:              set_state(READ_STATE_SEND, READ_WAIT_TIME); break;
    }
}

void SensorReader::init_line_and_send_command(void) {
    #ifdef DEBUG
    Serial.print("SensorReader - init line, sensor: ");
    Serial.println(sensor, DEC);
    #endif
    
    wire = OneWire(lines[sensor]);
    
    wire.reset();
    wire.skip();
    wire.write(0x44,1);
    
    set_state(READ_STATE_READ, READ_CHARGE_TIME);
}

void SensorReader::receive_and_store_temperature(void) {
    byte data[9];
    int *raw_temp = (int*) data;
    byte i;
    int temperature;

    // read scratchpad command
    wire.reset();
    wire.skip();
    wire.write(0xBE);

    // read 9 bytes
    for (i = 0; i < 9; i++) {
      data[i] = wire.read();
    }

    // check vaidity of buffer -- MAYBE: check CRC
    if (data[5] == 255 && data[7] == 16) {
      temperature = (int)(*raw_temp >> 4);
    } else {
      temperature = -99;
    }

    #ifdef DEBUG
    Serial.print("SensorReader - receive, sensor: ");
    Serial.print(sensor, DEC);
    Serial.print(", temperature: ");
    Serial.println(temperature, DEC);
    #endif

    temperatures[sensor] = temperature;
    sensor = (sensor + 1) % nr_sensors;
    
    set_state(READ_STATE_SEND, READ_WAIT_TIME);
}
