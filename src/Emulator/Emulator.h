#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <cstdint>
#include "../Stack/Stack.h"
#include "../Memory/Memory.h"
#include "../Display/Display.h"


class Emulator {
public:
    Emulator(): memory{}, stack{} {};
    void load(uint16_t instructions[]);
    void run(void);
    bool getPixel(int x, int y) { return display.getPixel(x, y); };
private:
    uint16_t pc;
    uint16_t index;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t registers[16];

    Stack stack;
    Memory memory;
    Display display;

    uint16_t fetch(void);
    void decodeExecute(uint16_t instruction);
};


#endif //CHIP8_EMULATOR_H
