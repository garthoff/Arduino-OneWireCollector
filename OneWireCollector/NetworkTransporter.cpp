#include "WProgram.h"
#include <SPI.h>
// #include "/Applications/Arduino.app/Contents/Resources/Java/libraries/Ethernet/Ethernet.h"
#include <Ethernet.h>
#include "NetworkTransporter.h"

extern int nr_sensors;
extern char* names[];
extern int temperatures[];


// Shield's MAC Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
// Shield's IP Address
byte ip[] = { 192, 168, 2, 177 };
// The server to connect to
byte server[] = { 192, 168, 2, 217 };
// our socket
Client socket(server, 80);

NetworkTransporter::NetworkTransporter(unsigned long pause): TimedState(pause) {
    Ethernet.begin(mac, ip);
    sensor = 0;
}

void NetworkTransporter::action(void) {
    switch (state) {
        case NET_STATE_SEND:    send(); break;
        case NET_STATE_RECEIVE: receive(); break;
        default:                set_state(NET_STATE_SEND, NET_WAIT_TIME); break;
    }
}


int _append( int i, char *string, int pos ) {
    if (i < 0) string[pos++] = '-';
    i = abs(i);
    
    if (i >= 100) string[pos++] = '0' + (i / 100) % 10;
    if (i >=  10) string[pos++] = '0' + (i / 10)  % 10;
    string[pos++] = '0' + i % 10;
    
    string[pos] = '\0';
    return pos;
}

int _append( char c, char *string, int pos ) {
    string[pos++] = c;
    
    string[pos] = '\0';
    return pos;
}
 
void NetworkTransporter::send(void) {
    if (socket.connect()) {
        char buffer[100];
        int pos = 0;
        int i;
        
        buffer[0] = '\0';
        for (i = 0; i < nr_sensors; i++) {
            if (i > 0) pos = _append('&', buffer, pos);
            pos = _append(i, buffer, pos);
            pos = _append('=', buffer, pos);
            pos = _append(temperatures[i], buffer, pos);
        }
        
        socket.println("POST /save_measure HTTP/1.0");
        
        socket.println("Host: www.xxx.de");
        socket.println("Content-Type: application/x-www-form-urlencoded");
        socket.print("Content-Length: "); socket.println(pos, DEC);
        socket.println();
        
        socket.print(buffer);
        
        set_state(NET_STATE_RECEIVE);
    }
}

void NetworkTransporter::receive(void) {
    if (socket.connected()) {
        while (socket.available()) {
            char c = socket.read();
        }
   
        if (!socket.connected()) {
            socket.stop();
            set_state(NET_STATE_SEND, NET_WAIT_TIME);
        }
    }
}
