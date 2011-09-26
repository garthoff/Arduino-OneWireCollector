/*
Messung und Anzeige der Temperatur eines Sensors an *einem* Draht (Parasite-Modus)

wenn DEBUG macro gesetzt --> Diagnose Ausgaben am seriellen Port

*/

#include <OneWire.h>   // needed to avoid linker messages
#include <SPI.h>       // needed to avoid linker messages
#include <Ethernet.h>  // needed to avoid linker messages

#include "Display.h"

#include "SensorReader.h"
#include "DisplaySwitcher.h"
#include "NetworkTransporter.h"

#define DEBUG

int nr_sensors     = 5;
int lines[]        = { 40, 41, 42, 43, 44 };
char* names[]      = { "Buero", "Heizung", "Waschkueche", "Fremdenzimmer", "Aussen" };
int temperatures[] = { -99, -99, -99, -99, -99 };


SensorReader sensor_reader(READ_WAIT_TIME);
DisplaySwitcher display_switcher(DISPLAY_WAIT_TIME);
//NetworkTransporter network_transporter(NET_WAIT_TIME);

void setup() {
    Serial.begin(9600);  // DEBUG output
    
    #ifdef DEBUG
    Serial.println("main - setup");
    #endif

    Display.clear();
}

void loop() {
    sensor_reader.tick();
    display_switcher.tick();
    // network_transporter.tick();
}


