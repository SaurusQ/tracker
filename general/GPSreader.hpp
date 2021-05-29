#pragma once

#include "definitions.hpp"
#include "UBXmsg.hpp"
#include "Arduino.h"
#include "GPSstartupData.hpp"

class GPSreader
{
    public:
        GPSreader(HardwareSerial* serial);            // start reading messages
        void init();    // configure the messages in the gps
        UBXmsg* process();      // processes one message or part of it depeding on the uart buffer
        bool readMsg();         // reads part of the message, does not block
        bool sync();            // sync the stream, called from readMsg
        bool checksum();        // checks if the checksum on CK_A and CK_B is correct
    private:
        HardwareSerial* serial_;
        uint8_t buff_[BUFFER_SIZE];
        uint8_t c_;                 // class
        uint8_t id_;                // id
        uint16_t len_;              // payload lenght
        uint8_t ck_a_;              // checksum of class, id, lenght and payload
        uint8_t ck_b_;              // 
        bool headerRead = false;    // has the reader been processed
        bool onSync = false;        // is the synch part of header read
};

