#pragma once

#include "render.hpp"
#include "memory.hpp"
#include "errors.hpp"
#include "chip8-reg.hpp"
#include "tracer.hpp"
#include "config.hpp"

#include <stdint.h>

class Chip8 {
    // Rendering implementation from platform.
    Render &mRender;

    // Memory implementation from platform.
    Memory &mMemory;

    // Tracer implementation.
    Tracer &mTracer;

    EmuState mState;
    
    Config mConfig;

    // read buttons and handle any updates
    inline void handleButtons();

    // handle an error. 
    void handleError(ErrorType errorType, uint16_t inst);

    inline bool readWord(uint16_t addr, uint16_t &result);

    // execute a single fetched chip8 instruction
    // If the instruction results in an error, the type will be passed via the
    // provided errorType param.
    ErrorType exec(uint16_t inst);

    // Instruction groups.
    
    // 0x0XXX - System (see submethods below).
    inline ErrorType groupSys(uint16_t);

    // 0x1nnn jump (no submethods).
    inline void groupJump(uint16_t);
    
    // 02nnn call (no submethods).
    inline ErrorType groupCall(uint16_t);
    
    // 0x3Xnn skip if equal immediate (no submethods).
    inline void groupSeImm(uint16_t);
    
    // 0x4Xnn skip if not equal immediate (no submethods).
    inline void groupSneImm(uint16_t);
    
    // 0x5XY0 skip if two registers hold equal values
    inline void groupSeReg(uint16_t);

    // 0x6Xnn - Load immediate
    inline void groupLdImm(uint16_t);

    // 0x7Xnn - add immediate
    inline void groupAddImm(uint16_t);

    // 0x8XYx - ALU Group
    inline ErrorType groupALU(uint16_t);

    // 0x9XYx   Skip if two registers hold inequal values
    inline void groupSneReg(uint16_t);

    //0xAnnn   load index immediate
    inline void groupLdiImm(uint16_t);

    // 0xBnnn   jump to I + xxx
    inline void groupJpV0Index(uint16_t);

    //0xCXnn   random, with mask.
    inline void groupRand(uint16_t);
    
    //0xDXYL   draw! If you think there's a bug in here, you're probably right.
    inline ErrorType groupGraphics(uint16_t);

    // 0xEX9E / 0xEXA1 - skip if key pressed/not pressed
    inline ErrorType groupKeyboard(uint16_t);

    // 0xFnnn - Load to various internal registers
    inline ErrorType groupLoad(uint16_t);


    // Instruction Sub-Methods
    
    // System group 0x0xxx
    // 0x00EE - Return from the most recently called subroutine.
    inline ErrorType ret();
    
    // 0x00FE/0x00FF - Enabled/Disable SChip8 hires mode.
    inline void setSuperhires(bool);

    // ALU group 0x8xxx

    // 0x8XY0   VX = Vy
    inline void aluLd(uint8_t x, uint8_t y);

    // 0x8XY2   VX = VX AND XY
    inline void aluOr(uint8_t x, uint8_t y);
    
    // 0x8XY1   VX = VX OR VY
    inline void aluAnd(uint8_t x, uint8_t y);

    // 0x8XY3   VX = VX XOR XY
    inline void aluXor(uint8_t x, uint8_t y);

    // 0x8XY4   VX = VX + VY, VF = carry
    inline void aluAdd(uint8_t x, uint8_t y);

    // 0x8XY5   VX = VX - VY, VF = 1 if borrow did not occur
    inline void aluSub(uint8_t x, uint8_t y);
    
    // 0x8XY6   VX = VX SHR VY, VF = bit shifted out
    inline void aluShr(uint8_t x, uint8_t y);

    // 0x8XY7   VX = VY - VX, VF = 1 if borrow did not occur
    inline void aluSubn(uint8_t x, uint8_t y);

    // 0x8XY8   VX = VX SHL VY, VF = bit shifted out
    inline void aluShl(uint8_t x, uint8_t y);


    // Load group 0xFxxx

    // 0xFX07 - Read delay timer into VX.
    inline void readDT(uint8_t);

    // 0xFX0A - Pause execution until a key is pressed.
    inline void waitK(uint8_t);

    // 0xFX15 - Set the delay timer to value in VX.
    inline void setDT(uint8_t);

    // 0xFX18 - Beep for the duration in VX.
    inline void makeBeep(uint16_t);

    // 0xFX1E - Add VX to I
    inline void addI(uint8_t);

    // 0xFX29 - Load low-res font character in VX
    inline void ldiFont(uint8_t);

    // 0xFX30 - Load hi-res font character in VX
    inline void ldiHiFont(uint8_t);

    // 0xFX33 - Write binary coded decimal encoding of VX to memory pointed to by I.
    inline ErrorType writeBCD(uint8_t);

    // 0xFX55 - Store V0-VX starting at I.
    inline ErrorType strReg(uint8_t);

    // 0xFX65 - Read into V0-VX starting at I.
    inline ErrorType ldReg(uint8_t);

    // 0xFX75 - Store registers into special platform storage
    // For example, "RPL" registers that were used in the original
    // SChip8 implementation.
    inline void strR(uint8_t);

    // 0xFX85 - Read registers from special platform storage
    // For example, "RPL" registers that were used in the original
    // SChip8 implementation.
    inline void ldR(uint8_t);


    public:
        // create a new Chip8 emulator with the provided renderer and memory
        // implementations.
        Chip8(Render &render, Memory &memory, Tracer &tracer);

        // Reset all registers and flags for the emulator instance, clear the memory,
        // and begin running.
        void Reset();

        void SetConfig(Config config) { mConfig = config; }
        Config GetConfig() { return mConfig; }

        // Read and execute one Chip8 operation. Instructions will be read from memory
        // using the provided memory implementation.
        // Returns ErrorType, which includes information about running the instruction, like
        // whether it resulted in an error or a halt.
        ErrorType Step();

        // Accept a bitmask of buttons that are pressed. The value will update the
        // internal button state of the emulator. If the emulator is waiting for a
        // keypress, that state will be detected here, and execution will continue.
        void Buttons(uint16_t buttons);

        // Updates any state that gets updated at 60Hz by chip-8
        // namely, beep timer and delay timer. Also triggers screen draw.
        void Tick();

        // returns true if the emulator is running
        bool Running() { return mState.Running; }
 
        // Read a 16-bit word from the memory of this Chip8 emulator at the
        // specified address, handling endian byte swap.
        bool ReadWord(uint16_t addr, uint16_t &result);

        const EmuState& State() { return mState; }
};
