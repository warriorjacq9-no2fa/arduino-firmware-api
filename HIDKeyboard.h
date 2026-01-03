#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include "Arduino.h"
#include "keys.h"

#define CMD_KBD_STRING 0xFE
#define CMD_KBD_REPORT 0xFD

typedef struct {
    uint8_t modifier;
    uint8_t key;
} keypress_t;

typedef struct {
    uint8_t modifier;
    uint8_t keys[6];
} report_t;

class Keyboard {
    public:
        keypress_t fromChar(char c);
        void press(uint8_t key, uint8_t modifier);
        void press(keypress_t key);
        void release(uint8_t key, uint8_t modifier);
        void release(keypress_t key);
        void write(const char *s);
        void write(char c);
    
    private:
        uint8_t keys[6] = {0};
        uint8_t index = 0;
};

#endif