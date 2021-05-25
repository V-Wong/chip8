#ifndef CHIP8_DECODED_INSTRUCTION_H
#define CHIP8_DECODED_INSTRUCTION_H

#include <cstdint>


struct DecodedInstruction {
    DecodedInstruction(uint16_t instruction) {
        type = instruction >> 12;
        x = (instruction >> 8) & 0xf;
        y = (instruction >> 4) & 0xf;
        n = instruction & 0xf;
        nn = instruction & 0xff;
        nnn = instruction & 0xfff;
    }

    uint8_t type;
    uint8_t x;
    uint8_t y;
    uint8_t n;
    uint8_t nn;
    uint16_t nnn;
};


#endif //CHIP8_DECODED_INSTRUCTION_H
