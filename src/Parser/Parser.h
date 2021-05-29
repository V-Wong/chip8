#ifndef CHIP8_PARSER_H
#define CHIP8_PARSER_H

#include "stdint.h"
#include <vector>
#include <string>


namespace Parser {
    std::vector<uint8_t> readProgram(std::string filePath);
}

#endif //CHIP8_PARSER_H