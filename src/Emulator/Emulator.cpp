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
        case 0:
            if (nnn = 0xEE)
                // clear screen
            if (nnn = 0xEE)
                pc = stack.pop();
            break;
        case 1: 
            pc = nnn;
            break;
        case 2:
            stack.push(pc);
            pc = nnn;
            break;
        case 3:
            if (registers[x] == nn) pc += 1;
            break;
        case 4:
            if (registers[x] != nn) pc += 1;
            break;
        case 5:
            if (n == 0 && registers[x] == registers[y]) pc += 1;
            break;
        case 6:
            registers[x] = nn;
            break;
        case 7:
            registers[x] += nn;
            break;
        case 8:
            if (n == 0) registers[x] = registers[y];
            if (n == 1) registers[x] |= registers[y];
            if (n == 2) registers[x] &= registers[y];
            if (n == 3) registers[x] ^= registers[y];
            if (n == 4) {
                int val = registers[x];
                if (val + registers[y] > 255) registers[15] = 1;
                else registers[15] = 0;

                registers[x] += registers[y];
            }
            if (n == 5) {
                int val = registers[x];
                if (val > registers[y]) registers[15] = 1;
                else registers[15] = 0;

                registers[x] -= registers[y];
            }
            if (n == 7) {
                int val = registers[x];
                if (val > registers[y]) registers[15] = 1;
                else registers[15] = 0;

                registers[x] = registers[y] - registers[x];
            }
            if (n == 6) {
                registers[x] = registers[y];
                if (registers[x] & 1 == 1) registers[15] = 0;
                else registers[15] = 1;
                registers[x] >>= 1;
            }
            if (n == 0xE) {
                registers[x] = registers[y];
                if ((registers[x] >> 15) & 1 == 1) registers[15] = 0;
                else registers[15] = 1;
                registers[x] <<= 1;
            }
        case 9:
            if (n == 0 && registers[x] != registers[y]) pc += 1;
            break;
        case 0xA:
            index = nnn;
        case 0xB:
            pc = nnn + registers[0];
        case 0xC:
            // generate random number

    }
}