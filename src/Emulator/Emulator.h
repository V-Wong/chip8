#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <cstdint>

#include "../Stack/Stack.h"
#include "../Memory/Memory.h"
#include "../Display/Display.h"
#include "DecodedInstruction.h"
#include "Fonts.h"


class Emulator {
public:
    Emulator(std::vector<uint8_t> program): memory{}, stack{} {
        load(0x200, program);
        load(0x50, FONTS);
    };
    void load(uint16_t start, std::vector<uint8_t> bytes);
    void run(void);
    bool getPixel(uint8_t x, uint8_t y) { return display.getPixel(x, y); };
    void keyPress(int key) { keysPressed[key] = true; isBlocked = false; };
    void keyUnpress(int key) { keysPressed[key] = false; };
    bool isDisplayUpdated() { return displayUpdated; };
private:
    uint16_t pc = 0x200;
    uint16_t index;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t registers[16];
    uint8_t& flagRegister = registers[16];
    bool isBlocked;

    Stack stack;
    Memory memory;
    Display display;
    bool keysPressed[16];

    uint16_t fetch(void);
    void execute(DecodedInstruction d);
    void updateDisplay(DecodedInstruction d);
    void clearDisplay(void);

    bool displayUpdated;
};


#endif //CHIP8_EMULATOR_H
