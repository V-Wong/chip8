#pragma once

#include "stdint.h"
#include <vector>
#include <string>


namespace Parser {
    auto readProgram(std::string filePath) -> std::vector<uint8_t>;
}
