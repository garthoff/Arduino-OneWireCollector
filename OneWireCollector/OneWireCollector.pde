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

// Location: one of these must be set
#define LOCATION_ER   1
#define LOCATION_TRM  2
#define LOCATION_TEST 3

#define LOCATION LOCATION_TEST

// our client --> defined in NetworkTransporter.cpp
// EthernetClient client(server, 81);
// EthernetClient client;

#if LOCATION == LOCATION_TRM
    int nr_sensors     = 5;
    int lines[]        = { 40, 41, 42, 43, 44 };
    char* names[]      = { "Heizraum", "Heizung", "Hobbyraum", "Flur", "Aussen" };
    int temperatures[] = { -99, -99, -99, -99, -99 };

    byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
    byte ip[]      = { 192,168,2,178 };
    byte gateway[] = { 192,168,2,1 };
    byte subnet[]  = { 255,255,255,0 };
    byte server[]  = { 93,186,200,140 };
    byte port      = 81;
#elif LOCATION == LOCATION_ER
    int nr_sensors     = 5;
    int lines[]        = { 40, 41, 42, 43, 44 };
    char* names[]      = { "Buero", "Heizung", "Waschkueche", "Fremdenzimmer", "Aussen" };
    int temperatures[] = { -99, -99, -99, -99, -99 };

    byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    byte ip[]      = { 192,168,2,177 };
    byte gateway[] = { 192,168,2,1 };
    byte subnet[]  = { 255,255,255,0 };
    byte server[]  = { 93,186,200,140 };
    byte port      = 81;
#else
    int nr_sensors     = 2;
    int lines[]        = { 40, 42 };
    char* names[]      = { "Foo", "Bar" };
    int temperatures[] = { -99, -99 };

    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
    IPAddress ip(192,168,2,176);
    IPAddress gateway(192,168,2,1);
    IPAddress subnet(255,255,255,0);
    IPAddress server(192,168,2,24);
    byte port = 3000;
#endif

DiagnosticOutput diagnostic_output(IDLE_WAIT_TIME);
SensorReader sensor_reader(READ_WAIT_TIME);
DisplaySwitcher display_switcher(DISPLAY_WAIT_TIME);
NetworkTransporter network_transporter(NET_WAIT_TIME);

void setup() {
    Ethernet.begin(mac, ip, gateway, subnet);
    Serial.begin(9600);  // DEBUG output

    #ifdef DEBUG
    Serial.println("main - setup");
    #endif


    // delay(1000);
    // int status;
    // if (client.connect(server, port) > 0) {
    //     Serial.println("Connected");
    // } else {
    //     Serial.print("Connect failed, status = ");
    //     Serial.print(status);
    // }

    Display.clear();
}

void loop() {
    diagnostic_output.tick();
    sensor_reader.tick();
    display_switcher.tick();
    network_transporter.tick();
}
