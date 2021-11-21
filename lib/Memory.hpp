#include <cstdint>
#include <array>

constexpr int MEMORY_LIMIT = 4096;

class Memory {
public:
    Memory(): memory() {};
    std::uint8_t getByte(std::uint16_t address);
    void writeByte(std::uint16_t address, std::uint8_t value);
private:
    std::array<std::uint8_t, MEMORY_LIMIT> memory;
};
