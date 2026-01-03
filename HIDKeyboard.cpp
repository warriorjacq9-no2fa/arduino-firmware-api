#include "HIDKeyboard.h"

keypress_t _Keyboard::fromChar(char c) {
    uint8_t modifier = 0;
    uint8_t scancode = 0;

    // Letters
    if (c >= 'a' && c <= 'z') {
        scancode = KEY_A + (c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
        scancode = KEY_A + (c - 'A');
        modifier = MOD_LEFTSHIFT;
    }

    // Numbers
    else if (c >= '1' && c <= '9') {
        scancode = KEY_1 + (c - '1');
    } else if (c == '0') {
        scancode = KEY_0;
    }

    // Shifted numbers / symbols
    else {
        switch (c) {
            case '!': scancode = KEY_1; modifier = MOD_LEFTSHIFT; break;
            case '@': scancode = KEY_2; modifier = MOD_LEFTSHIFT; break;
            case '#': scancode = KEY_3; modifier = MOD_LEFTSHIFT; break;
            case '$': scancode = KEY_4; modifier = MOD_LEFTSHIFT; break;
            case '%': scancode = KEY_5; modifier = MOD_LEFTSHIFT; break;
            case '^': scancode = KEY_6; modifier = MOD_LEFTSHIFT; break;
            case '&': scancode = KEY_7; modifier = MOD_LEFTSHIFT; break;
            case '*': scancode = KEY_8; modifier = MOD_LEFTSHIFT; break;
            case '(': scancode = KEY_9; modifier = MOD_LEFTSHIFT; break;
            case ')': scancode = KEY_0; modifier = MOD_LEFTSHIFT; break;

            case '\n': scancode = KEY_ENTER; break;

            // Punctuation
            case ' ': scancode = KEY_SPACE; break;
            case '-': scancode = KEY_MINUS; break;
            case '_': scancode = KEY_MINUS; modifier = MOD_LEFTSHIFT; break;
            case '=': scancode = KEY_EQUALS; break;
            case '+': scancode = KEY_EQUALS; modifier = MOD_LEFTSHIFT; break;
            case '[': scancode = KEY_LEFTBRACE; break;
            case '{': scancode = KEY_LEFTBRACE; modifier = MOD_LEFTSHIFT; break;
            case ']': scancode = KEY_RIGHTBRACE; break;
            case '}': scancode = KEY_RIGHTBRACE; modifier = MOD_LEFTSHIFT; break;
            case '\\': scancode = KEY_BACKSLASH; break;
            case '|': scancode = KEY_BACKSLASH; modifier = MOD_LEFTSHIFT; break;
            case ';': scancode = KEY_SEMICOLON; break;
            case ':': scancode = KEY_SEMICOLON; modifier = MOD_LEFTSHIFT; break;
            case '\'': scancode = KEY_APOSTROPHE; break;
            case '"': scancode = KEY_APOSTROPHE; modifier = MOD_LEFTSHIFT; break;
            case '`': scancode = KEY_GRAVE; break;
            case '~': scancode = KEY_GRAVE; modifier = MOD_LEFTSHIFT; break;
            case ',': scancode = KEY_COMMA; break;
            case '<': scancode = KEY_COMMA; modifier = MOD_LEFTSHIFT; break;
            case '.': scancode = KEY_DOT; break;
            case '>': scancode = KEY_DOT; modifier = MOD_LEFTSHIFT; break;
            case '/': scancode = KEY_SLASH; break;
            case '?': scancode = KEY_SLASH; modifier = MOD_LEFTSHIFT; break;

            default:
                scancode = KEY_SPACE; break; // Default to space
        }
    }
    keypress_t ret;
    ret.key = scancode;
    ret.modifier = modifier;
    return ret;
}

void _Keyboard::press(uint8_t key, uint8_t modifier = MOD_NONE) {
    Serial.write(CMD_KBD_REPORT);
    Serial.write(modifier);

    if(this->index < 6) {
        this->keys[this->index] = key;
        this->index++;
    }

    for(int i = 0; i < 6; i++) Serial.write(this->keys[i]);
}

void _Keyboard::press(keypress_t key) {
    Serial.write(CMD_KBD_REPORT);
    Serial.write(key.modifier);

    if(this->index < 6) {
        this->keys[this->index] = key.key;
        this->index++;
    }

    for(int i = 0; i < 6; i++) Serial.write(this->keys[i]);
}

void _Keyboard::release(uint8_t key, uint8_t modifier = MOD_NONE) {
    Serial.write(CMD_KBD_REPORT);
    Serial.write(modifier);

    for(int i = 0; i < 6; i++) {
        if(this->keys[i] == key){
            this->keys[i] = 0;
            // Shift keys to the left so that index logic still works
            for(int j = i; j < this->index - 1; j++) {
                this->keys[j] = this->keys[j + 1];
            }
            this->keys[5] = 0;
            this->index--;
            break;
        }
    }

    for(int i = 0; i < 6; i++) Serial.write(this->keys[i]);
}

void _Keyboard::release(keypress_t key) {
    Serial.write(CMD_KBD_REPORT);
    Serial.write(key.modifier);

    for(int i = 0; i < 6; i++) {
        if(this->keys[i] == key.key){
            this->keys[i] = 0;
            // Shift keys to the left so that index logic still works
            for(int j = i; j < this->index - 1; j++) {
                this->keys[j] = this->keys[j + 1];
            }
            this->keys[5] = 0;
            this->index--;
            break;
        }
    }

    for(int i = 0; i < 6; i++) Serial.write(this->keys[i]);
}

void _Keyboard::write(const char* s) {
    char c;
    
    Serial.write(CMD_KBD_STRING);
    Serial.write(strlen(s) * 2);

    while((c = *s++)) {
        keypress_t key = fromChar(c);
        Serial.write(key.modifier);
        Serial.write(key.key);
    }
}

void _Keyboard::write(char c) {
    Serial.write(CMD_KBD_STRING);
    Serial.write(2);
    keypress_t key = fromChar(c);
    Serial.write(key.modifier);
    Serial.write(key.key);
}