#include "Memory.hpp"

std::uint8_t Memory::getByte(std::uint16_t address) {
    return memory.at(address);
}

void Memory::writeByte(std::uint16_t address, std::uint8_t value) {
    memory.at(address) = value;
}
