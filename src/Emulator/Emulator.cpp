#include "Emulator.h"

uint16_t joinBytes(uint8_t msb, uint8_t lsb) {
    return ((uint16_t)msb << 8) | lsb;
}

void Emulator::run(void) {
    while (true) {
        uint16_t instruction = fetch();
        decodeEexcute(instruction);
    }
}

uint16_t Emulator::fetch(void) {
    uint16_t instruction = joinBytes(memory.getByte(pc), memory.getByte(pc + 1));
    pc += 2;
    return instruction;
}
