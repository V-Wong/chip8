#include "Stack.h"

void Stack::push(std::uint16_t value) {
    stack.push_back(value);
}

std::uint16_t Stack::pop(void) {
    std::uint16_t value = stack.back();
    stack.pop_back();
    return value;
}