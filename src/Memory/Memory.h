#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <cstdint>


class Memory {
public:
    Memory();
    std::uint8_t getByte(std::uint8_t address);
    std::uint8_t writeByte(std::uint16_t address, std::uint8_t value);
};


#endif //CHIP8_MEMORY_H
