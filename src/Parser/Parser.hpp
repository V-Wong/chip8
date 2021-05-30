#pragma once

#include "stdint.h"
#include <vector>
#include <string>


namespace Parser {
    std::vector<uint8_t> readProgram(std::string filePath);
}
