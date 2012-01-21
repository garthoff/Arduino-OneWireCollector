#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include "NetworkTransporter.h"

#define DEBUG

extern int nr_sensors;
extern char* names[];
extern int temperatures[];

EthernetClient client;
extern IPAddress server;
extern byte port;

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
    
    if (client.connect(server,port) > 0) {
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
        
        
        client.println("POST /save_measures HTTP/1.0");
        
        // client.println("Host: www.xxx.de");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: "); client.println(pos, DEC);
        client.println();
        
        client.print(buffer);
        
        set_state(NET_STATE_RECEIVE);
    } else {
        #ifdef DEBUG
        Serial.println("NetworkTransporter: connect failed");
        Serial.print("  Connected: ");
        Serial.println(client.connected() ? "YES" : "NO");
        Serial.print("  Available: ");
        Serial.println(client.available());
        Serial.print("  Status: ");
        Serial.println(client.status());
        #endif
        client.stop();
    }
}

void NetworkTransporter::receive(void) {
    #ifdef DEBUG
    Serial.println("NetworkTransporter: receive");
    #endif
    if (client.connected()) {
        while (client.available()) {
            char c = client.read();
        }
   
        if (!client.connected()) {
            client.stop();
            set_state(NET_STATE_SEND, NET_WAIT_TIME);
        }
    }
}
