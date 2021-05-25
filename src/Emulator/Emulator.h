#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <cstdint>
#include "../Stack/Stack.h"
#include "../Memory/Memory.h"
#include "../Display/Display.h"


class Emulator {
public:
    Emulator(): memory{}, stack{} {};
    void load(std::vector<uint8_t> bytes);
    void run(void);
    bool getPixel(uint8_t x, uint8_t y) { return display.getPixel(x, y); };
    void keyPress(int key) { keysPressed[key] = true; isBlocked = false; };
    void keyUnpress(int key) { keysPressed[key] = false; };
    bool isDisplayUpdated() { return displayUpdated; };
private:
    uint16_t pc;
    uint16_t index;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t registers[16];
    bool isBlocked;

    Stack stack;
    Memory memory;
    Display display;
    bool keysPressed[16];

    uint16_t fetch(void);
    void decodeExecute(uint16_t instruction);

    bool displayUpdated;
};


#endif //CHIP8_EMULATOR_H
