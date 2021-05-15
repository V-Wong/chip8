#include "Emulator.h"

uint16_t joinBytes(uint8_t msb, uint8_t lsb) {
    return ((uint16_t)msb << 8) | lsb;
}

void Emulator::run(void) {
    while (true) {
        uint16_t instruction = fetch();
        decodeExecute(instruction);
    }
}

uint16_t Emulator::fetch(void) {
    uint16_t instruction = joinBytes(memory.getByte(pc), memory.getByte(pc + 1));
    pc += 2;
    return instruction;
}

void Emulator::decodeExecute(uint16_t instruction) {
    uint8_t type = instruction >> 12;
    uint8_t x = (instruction >> 8) & 0xf;
    uint8_t y = (instruction >> 4) & 0xf;
    uint8_t n = instruction & 0xf;
    uint8_t nn = instruction & 0xff;
    uint16_t nnn = instruction & 0xfff;

    switch(type) {
        // rest of implementation
    }
}