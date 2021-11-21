#include <cstdint>
#include <stack>

#include "lib/Memory.hpp"
#include "lib/Display.hpp"
#include "lib/DecodedInstruction.hpp"
#include "lib/Fonts.hpp"


class Emulator {
public:
    Emulator(std::vector<uint8_t> program): memory{}, stack{} {
        load(0x200, program);
        load(0x00, chip8Fonts);
    };
    auto load(uint16_t start, std::vector<uint8_t> bytes) -> void;
    auto run(void) -> void;
    auto getPixel(uint8_t x, uint8_t y) -> bool { return display.getPixel(x, y); };
    auto keyPress(int key) -> void { keysPressed[key] = true; lastPressedKey = key; isBlocked = false; };
    auto keyUnpress(int key) -> void { keysPressed[key] = false; };
    auto isDisplayUpdated() -> bool { return displayUpdated; };
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

    auto fetch(void) -> uint16_t;
    auto execute(DecodedInstruction d) -> void;
    auto updateDisplay(DecodedInstruction d) -> void;
    auto writeMemory(DecodedInstruction d) -> void;
    auto readMemory(DecodedInstruction d) -> void;
    auto convertBinary(DecodedInstruction d) -> void;
    auto clearDisplay(void) -> void;
    auto decrementTimer(void) -> void;

    bool displayUpdated;
    uint16_t lastPressedKey = -1;
    uint16_t steps = 0;
};
