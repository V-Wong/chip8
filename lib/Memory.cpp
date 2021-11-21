#include "Memory.hpp"

auto Memory::getByte(std::uint16_t address) -> std::uint8_t {
    return memory.at(address);
}

auto Memory::writeByte(std::uint16_t address, std::uint8_t value) -> void {
    memory.at(address) = value;
}
