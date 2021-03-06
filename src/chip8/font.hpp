// If using this for Arduino target, add 
// 
// #define FONT_STORAGE_MODIFIER PROGMEM
//
// Before including the file.

#ifndef FONT_STORAGE_MODIFIER 
#define FONT_STORAGE_MODIFIER 
#endif

const uint8_t font[] FONT_STORAGE_MODIFIER = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};

const uint8_t fonthi[] FONT_STORAGE_MODIFIER = {
    0x78, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x78, // 0
    0x30, 0x70, 0xF0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0xFC, // 1
    0x78, 0xFC, 0x0C, 0x0C, 0xFC, 0xFC, 0xC0, 0xC0, 0xFC, 0x78, // 2
    0x78, 0xFC, 0x0C, 0x0C, 0x38, 0x38, 0x0C, 0x0C, 0xFC, 0x78, // 3
    0x48, 0xCC, 0xCC, 0xCC, 0xFC, 0x7C, 0x0C, 0x0C, 0x0C, 0x08, // 4
    0x78, 0xFC, 0xC0, 0xC0, 0xFC, 0xFC, 0x0C, 0x0C, 0xFC, 0x78, // 5
    0x78, 0xFC, 0xC0, 0xC0, 0xF8, 0xFC, 0xCC, 0xCC, 0xFC, 0x78, // 6
    0x78, 0xFC, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x30, 0x30, 0x30, // 7
    0x78, 0xFC, 0xCC, 0xCC, 0x78, 0x78, 0xCC, 0xCC, 0xFC, 0x78, // 8
    0x78, 0xFC, 0xCC, 0xCC, 0xFC, 0x7C, 0x0C, 0x0C, 0xFC, 0x78, // 9
    0x78, 0xFC, 0xCC, 0xCC, 0xFC, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, // A
    0xF8, 0xFC, 0xCC, 0xCC, 0xF8, 0xF8, 0xCC, 0xCC, 0xFC, 0xF8, // B
    0x78, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFC, 0x78, // C
    0xF8, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0xF8, // D
    0x78, 0xFC, 0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0xFC, 0x78, // E
    0x78, 0xFC, 0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0xC0, 0xC0, // F
};

