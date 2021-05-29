#include "Parser.h"

#include <fstream>


namespace Parser {
    std::vector<uint8_t> readProgram(std::string filePath) {
        std::ifstream input(filePath, std::ios::binary);

        std::vector<uint8_t> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        return bytes;
    }
}
