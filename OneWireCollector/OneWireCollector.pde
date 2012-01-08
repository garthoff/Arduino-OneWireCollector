/*
Measure and display of values using OneWire sensors
*/

#include <OneWire.h>   // needed to avoid linker messages
#include <SPI.h>       // needed to avoid linker messages
#include <Ethernet.h>  // needed to avoid linker messages

#include "Display.h"

#include "DiagnosticOutput.h"
#include "SensorReader.h"
#include "DisplaySwitcher.h"
#include "NetworkTransporter.h"

#define noDEBUG

int nr_sensors     = 5;
int lines[]        = { 40, 41, 42, 43, 44 };
char* names[]      = { "Buero", "Heizung", "Waschkueche", "Fremdenzimmer", "Aussen" };
int temperatures[] = { -99, -99, -99, -99, -99 };

// Shield's MAC Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  

// Shield's IP Address
byte ip[] = { 192,168,2,177 };

// Router
byte gateway[] = { 192,168,2,1 };

// Network mask
byte subnet[] = { 255,255,255,0 };
// The server to connect to

byte server[] = { 93,186,200,140 };

// our socket --> defined in NetworkTransporter.cpp
// EthernetClient socket(server, 81);

DiagnosticOutput diagnostic_output(IDLE_WAIT_TIME);
SensorReader sensor_reader(READ_WAIT_TIME);
DisplaySwitcher display_switcher(DISPLAY_WAIT_TIME);
NetworkTransporter network_transporter(NET_WAIT_TIME);

void setup() {
    Serial.begin(9600);  // DEBUG output
    
    #ifdef DEBUG
    Serial.println("main - setup");
    #endif

    Ethernet.begin(mac, ip, gateway, subnet);

    Display.clear();
}

void loop() {
    diagnostic_output.tick();
    sensor_reader.tick();
    display_switcher.tick();
    network_transporter.tick();
}
