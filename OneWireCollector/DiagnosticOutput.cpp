#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "DiagnosticOutput.h"
#include "SensorReader.h"
#include "DisplaySwitcher.h"
#include "NetworkTransporter.h"

#define noDEBUG

extern SensorReader sensor_reader;
extern DisplaySwitcher display_switcher;
extern NetworkTransporter network_transporter;


DiagnosticOutput::DiagnosticOutput(unsigned long pause) :TimedState(pause) {
    nr_overruns = 0;
    last_checked = 0;
}

void DiagnosticOutput::action(void) {
    #ifdef DEBUG
    Serial.println("DiagnosticOutput - action");
    #endif

    if (last_checked > millis()) {
        nr_overruns++;
    }
    last_checked = millis();

    write_diagnostic_output();
}

void DiagnosticOutput::write_diagnostic_output(void) {
    Serial.print("Millis: ");
    Serial.print(millis(), DEC);
    Serial.print(", Last Activated: ");
    Serial.print(get_last_activated(), DEC);
    Serial.print(", Nr Overruns: ");
    Serial.println(nr_overruns, DEC);
    
    Serial.print("State Switches -  S: ");
    Serial.print(sensor_reader.get_nr_activations(), DEC);
    Serial.print(",  D: ");
    Serial.print(display_switcher.get_nr_activations(), DEC);
    Serial.print(",  N: ");
    Serial.println(network_transporter.get_nr_activations(), DEC);
    
    Serial.println();
}
