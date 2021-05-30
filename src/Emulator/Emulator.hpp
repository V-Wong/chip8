#pragma once

#include <cstdint>
#include <stack>

#include "../Memory/Memory.hpp"
#include "../Display/Display.hpp"
#include "../DecodedInstruction/DecodedInstruction.hpp"
#include "../Fonts/Fonts.hpp"


class Emulator {
public:
    Emulator(std::vector<uint8_t> program): memory{}, stack{} {
        load(0x200, program);
        load(0x00, FONTS);
    };
    void load(uint16_t start, std::vector<uint8_t> bytes);
    void run(void);
    bool getPixel(uint8_t x, uint8_t y) { return display.getPixel(x, y); };
    void keyPress(int key) { keysPressed[key] = true; lastPressedKey = key; isBlocked = false; };
    void keyUnpress(int key) { keysPressed[key] = false; };
    bool isDisplayUpdated() { return displayUpdated; };
private:
    uint16_t pc = 0x200;
    uint16_t index;
    uint8_t delayTimer = UINT8_MAX;
    uint8_t soundTimer;
    uint8_t registers[16] = {0};
    uint8_t& flagRegister = registers[15];
    bool isBlocked;

    std::stack<uint16_t> stack;
    Memory memory;
    Display display;
    bool keysPressed[16];

    uint16_t fetch(void);
    void execute(DecodedInstruction d);
    void updateDisplay(DecodedInstruction d);
    void writeMemory(DecodedInstruction d);
    void readMemory(DecodedInstruction d);
    void convertBinary(DecodedInstruction d);
    void clearDisplay(void);
    void decrementTimer(void);

    bool displayUpdated;
    uint16_t lastPressedKey = -1;
    uint16_t steps = 0;
};
