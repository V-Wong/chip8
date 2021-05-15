#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <cstdint>


class Memory {
public:
    Memory() = default;
    std::uint8_t getByte(std::uint8_t address) const;
    std::uint8_t writeByte(std::uint16_t address, std::uint8_t value) const;
};


#endif //CHIP8_MEMORY_H
