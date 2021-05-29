#ifndef CHIP8_PARSER_H
#define CHIP8_PARSER_H

#include "stdint.h"
#include <vector>


namespace Parser {
    std::vector<uint8_t> readProgram();
}

#endif //CHIP8_PARSER_H