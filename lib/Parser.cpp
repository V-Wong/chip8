#include "Parser.hpp"

#include <fstream>


namespace Parser {
    auto readProgram(std::string filePath) -> std::vector<uint8_t> {
        auto input = std::ifstream(filePath, std::ios::binary);

        auto bytes = std::vector<uint8_t> {
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>())
        };

        input.close();

        return bytes;
    }
}
