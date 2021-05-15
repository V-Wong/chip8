#ifndef CHIP8_STACK_H
#define CHIP8_STACK_H

#include <cstdint>


class Stack {
public:
    Stack() = default;
    void push(std::uint16_t value);
    std::uint16_t pop(void);
};


#endif //CHIP8_STACK_H
