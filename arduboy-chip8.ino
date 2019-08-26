#include <Arduboy2.h>

#include "src/chip8/chip8.hpp"

#include "programs.h"
#include "arduboy-render.hpp"
#include "chip8-mem.hpp"


Arduboy2 boy;
ArduMem memory;

ArduboyRender render(boy);
Chip8 emu(render, memory);

void setup() {
    boy.begin();
    boy.initRandomSeed();
    Serial.begin(115200);
    boy.setFrameRate(60);
}

uint8_t pidx;
const Program *program;
bool super = false;
uint8_t keymap[3] = {0x12, 0x3C, 0xAB};

unsigned long next = 0;
void runEmu() {
    if(boy.nextFrame()) {
        render.tick();
        emu.Tick();
    }
    
    unsigned long t = micros();
    if(t < next) {
        return;
    }
    next = t + (super ? 100 : 1000);
    if(boy.pressed(UP_BUTTON) &&
            boy.pressed(DOWN_BUTTON) && 
            boy.pressed(LEFT_BUTTON) && 
            boy.pressed(RIGHT_BUTTON)) {
        emu.Reset();
        program = NULL;
    }


    boy.pollButtons();
    uint16_t buttons = 0;
    if(boy.pressed(UP_BUTTON)) buttons |= (1 << (keymap[0] >> 4));
    if(boy.pressed(DOWN_BUTTON)) buttons |= (1 << (keymap[0] & 0xF));
    if(boy.pressed(LEFT_BUTTON)) buttons |= (1 << (keymap[1] >> 4));
    if(boy.pressed(RIGHT_BUTTON)) buttons |= (1 << (keymap[1] & 0xF));
    if(boy.pressed(A_BUTTON)) buttons |= (1 << (keymap[2] >> 4));
    if(boy.pressed(B_BUTTON)) buttons |= (1 << (keymap[2] & 0xF));

    emu.Buttons(buttons);
    if(emu.Running()) {
        emu.Step();
    } else if(boy.justPressed(A_BUTTON)) {
        emu.Reset();
    }
}

void runLoader() {
    boy.clear();
    boy.setCursor(0,0);
    super = pgm_read_byte(&programs[pidx].super);
    boy.print(F("Select: "));
    boy.setCursor(0,30);
    boy.print(pidx);
    boy.setCursor(16,30);
    char buffer[16];
    strcpy_P(buffer, (const char*)pgm_read_ptr(&programs[pidx].name));
    boy.println(buffer);
    if(super) {
        boy.println(F("SCHIP-8"));
    } else {
        boy.println(F("CHIP-8"));
    }
    strcpy_P(buffer, (const char*)pgm_read_ptr(&programs[pidx].info));
    boy.println(buffer);
    boy.display();

    boy.pollButtons();
    if(boy.justPressed(DOWN_BUTTON)) {
        pidx++;
        if(pidx >= PROGRAM_COUNT) {
            pidx = 0;
        }
    }
    if(boy.justPressed(UP_BUTTON)) {
        pidx--;
        if(pidx >= PROGRAM_COUNT) {
            pidx = PROGRAM_COUNT-1;
        }
    }
    if(boy.justPressed(A_BUTTON)) {
        program = &programs[pidx];
        uint16_t size = pgm_read_word(&(program->size));
        const uint8_t* code = pgm_read_ptr(&(program->code));
        for(int i = 0; i < 3; i++) {
            keymap[i] = pgm_read_byte(&(program->keymap[i]));
            Serial.print(keymap[i], HEX);
            Serial.print("   ");
        }
        Serial.println("");
        memory.load(code, size);
        emu.Reset();

    }
}

void loop() {
    if (program == NULL) {
        runLoader(); 
    } else {
        runEmu();
    }
}
