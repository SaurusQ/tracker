#pragma once
#include "Arduino.h"

#define DEBUG_LOG

#define BUFFER_SIZE 256
#define HEADER_SIZE 4

#ifdef DEBUG_LOG
#define LOG(a) Serial.println(a)
#else
#define LOG(a) (void)
#endif
// for syntax highlighter
/*#ifndef uint8_t
    #define uint8_t unsigned char
#endif
#ifndef uint16_t
    #define uint16_t unsigned short
#endif
#ifndef uint32_t
    #define uint32_t unsigned long
#endif
#ifndef int8_t
    #define int8_t signed char
#endif
#ifndef int16_t
    #define int16_t signed short
#endif
#ifndef int32_t
    #define int32_t signed long
#endif*/