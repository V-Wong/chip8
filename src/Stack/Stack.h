#ifndef CHIP8_STACK_H
#define CHIP8_STACK_H

#include <cstdint>
#include <vector>


class Stack {
public:
    Stack(): stack() {};
    void push(std::uint16_t value);
    std::uint16_t pop(void);
private:
    std::vector<std::uint16_t> stack;
};


#endif //CHIP8_STACK_H
