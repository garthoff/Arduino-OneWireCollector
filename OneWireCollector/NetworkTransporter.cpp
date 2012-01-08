#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include "NetworkTransporter.h"

#define DEBUG

extern int nr_sensors;
extern char* names[];
extern int temperatures[];

EthernetClient socket;
extern byte server[];

NetworkTransporter::NetworkTransporter(unsigned long pause): TimedState(pause) {
}

void NetworkTransporter::action(void) {
    #ifdef DEBUG
    Serial.println("NetworkTransporter: action");
    #endif
    
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

int _append( char *c, char *string, int pos ) {
    while (*c) {
        string[pos++] = *c++;
    }
    string[pos] = '\0';
    return pos;
}
 
void NetworkTransporter::send(void) {
    #ifdef DEBUG
    Serial.println("NetworkTransporter: send");
    #endif
    
    if (socket.connect(server,81)) {
        char buffer[200];
        int pos = 0;
        int i;
        
        buffer[0] = '\0';
        for (i = 0; i < nr_sensors; i++) {
            if (i > 0) pos = _append('&', buffer, pos);
            pos = _append(names[i], buffer, pos);
            pos = _append('=', buffer, pos);
            pos = _append(temperatures[i], buffer, pos);
        }
        
        #ifdef DEBUG
        Serial.print("NetworkTransporter: ");
        Serial.println(buffer);
        #endif
        
        
        socket.println("POST /save_measures HTTP/1.0");
        
        // socket.println("Host: www.xxx.de");
        socket.println("Content-Type: application/x-www-form-urlencoded");
        socket.print("Content-Length: "); socket.println(pos, DEC);
        socket.println();
        
        socket.print(buffer);
        
        set_state(NET_STATE_RECEIVE);
    }
}

void NetworkTransporter::receive(void) {
    #ifdef DEBUG
    Serial.println("NetworkTransporter: receive");
    #endif
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
