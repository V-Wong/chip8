#include <cstdint>
#include <array>

constexpr int MEMORY_LIMIT = 4096;

class Memory {
public:
    Memory(): memory() {};
    auto getByte(std::uint16_t address) -> std::uint8_t;
    auto writeByte(std::uint16_t address, std::uint8_t value) -> void;
private:
    std::array<std::uint8_t, MEMORY_LIMIT> memory;
};
