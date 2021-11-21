#include "lib/Emulator.hpp"

#include <iostream>
#include <stdlib.h>

#include "lib/OPCodes.hpp"

auto constexpr BYTE_SIZE = 8;
auto constexpr INSTRUCTION_INCREMENT = 2;


auto joinBytes(uint8_t msb, uint8_t lsb) -> uint16_t {
    return (static_cast<uint16_t>(msb) << BYTE_SIZE) | lsb;
}

auto Emulator::load(uint16_t start, std::vector<uint8_t> bytes) -> void {
    for (auto i = 0; i < bytes.size(); i++)
        memory.writeByte(start + i, bytes.at(i));
}

auto Emulator::run(void) -> void {
    auto instruction = fetch();
    pc += INSTRUCTION_INCREMENT;
    displayUpdated = false;
    execute({instruction});
    lastPressedKey = -1;
    decrementTimer();
}

auto Emulator::fetch(void) -> uint16_t {
    auto instruction = joinBytes(memory.getByte(pc), memory.getByte(pc + 1));
    return instruction;
}

auto Emulator::decrementTimer(void) -> void {
    if (steps % 8 == 0) {
        delayTimer -= 1;
        steps = 0;
    } else {
        steps += 1;
    }
}

auto Emulator::execute(DecodedInstruction d) -> void {
    switch (d.type) {
        case OPCodes::INITIAL:
            if (d.nnn == OPCodes::CLEAR_DISPLAY) clearDisplay();
            if (d.nnn == OPCodes::POP_PC) {
                pc = stack.top();
                stack.pop();
            }
            break;
        case OPCodes::SET_PC_EQ_NNN:
            pc = d.nnn;
            break;
        case OPCodes::PUSH_PC:
            stack.push(pc);
            pc = d.nnn;
            break;
        case OPCodes::X_EQ_NN_PC_INC:
            if (registers[d.x] == d.nn) pc += INSTRUCTION_INCREMENT;
            break;
        case OPCodes::X_NEQ_NN_PC_INC:
            if (registers[d.x] != d.nn) pc += INSTRUCTION_INCREMENT;
            break;
        case OPCodes::X_EQ_Y_PC_INC:
            if (d.n == 0 && registers[d.x] == registers[d.y]) pc += INSTRUCTION_INCREMENT;
            break;
        case OPCodes::X_NEQ_Y_PC_INC:
            if (d.n == 0 && registers[d.x] != registers[d.y]) pc += INSTRUCTION_INCREMENT;
            break;
        case OPCodes::SET_X_NN:
            registers[d.x] = d.nn;
            break;
        case OPCodes::ADD_X_NN:
            registers[d.x] += d.nn;
            break;
        case OPCodes::ARITH_LOGIC:
            if (d.n == OPCodes::SET_X_EQ_Y) registers[d.x] = registers[d.y];
            if (d.n == OPCodes::SET_X_OR_Y) registers[d.x] |= registers[d.y];
            if (d.n == OPCodes::SET_X_AND_Y) registers[d.x] &= registers[d.y];
            if (d.n == OPCodes::SET_X_XOR_Y) registers[d.x] ^= registers[d.y];
            if (d.n == OPCodes::SET_X_ADD_Y) {
                flagRegister = registers[d.x] + registers[d.y] > UINT8_MAX;
                registers[d.x] += registers[d.y];
            }
            if (d.n == OPCodes::SET_X_SUB_Y) {
                flagRegister = registers[d.x] >= registers[d.y];
                registers[d.x] -= registers[d.y];
            }
            if (d.n == OPCodes::SET_X_EQ_Y_SUB_X) {
                flagRegister = registers[d.y] >= registers[d.x];
                registers[d.x] = registers[d.y] - registers[d.x];
            }
            if (d.n == OPCodes::SET_X_RSHIFT) {
                flagRegister = registers[d.x] & 1;
                registers[d.x] >>= 1;
            }
            if (d.n == OPCodes::SET_X_LSHIFT) {
                flagRegister = registers[d.x] >> (BYTE_SIZE - 1);
                registers[d.x] <<= 1;
            }
            break;
        case OPCodes::SET_IDX_NN:
            index = d.nnn;
            break;
        case OPCodes::SET_PC_EQ_V0_ADD_NNN:
            pc = d.nnn + registers[0];
            break;
        case OPCodes::RAND_INT:
            registers[d.x] = (rand() % 0xffff) & d.nn;
            break;
        case OPCodes::DRAW:
            updateDisplay(d);
            break;
        case OPCodes::READ_KEY:
            if (d.nn == OPCodes::KEY_PRESSED && keysPressed[registers[d.x]]) 
                pc += INSTRUCTION_INCREMENT;
            if (d.nn == OPCodes::KEY_NPRESSED && !keysPressed[registers[d.x]]) 
                pc += INSTRUCTION_INCREMENT;
            break;
        case OPCodes::OTHER:
            if (d.nn == OPCodes::SET_X_EQ_DELAY) registers[d.x] = delayTimer;
            if (d.nn == OPCodes::SET_DELAY_EQ_X) delayTimer = registers[d.x];
            if (d.nn == OPCodes::SET_SOUND_EQ_X) soundTimer = registers[d.x];
            if (d.nn == OPCodes::SET_IDX_ADD_X) index += registers[d.x];
            if (d.nn == OPCodes::BLOCK_KEY_READ) {
                if (isBlocked && lastPressedKey != -1)
                    registers[d.x] = lastPressedKey;
                else
                    isBlocked = true;
            }
            if (d.nn == OPCodes::SET_IDX_FONT) index = registers[d.x] * 5;
            if (d.nn == OPCodes::CONVERT_BINARY) convertBinary(d);
            if (d.nn == OPCodes::WRITE_MEMORY) writeMemory(d);
            if (d.nn == OPCodes::READ_MEMORY) readMemory(d);
            break;
    }
}

auto Emulator::updateDisplay(DecodedInstruction d) -> void {
    auto xCoordinate = registers[d.x] % DisplaySpecs::PIXEL_WIDTH;
    auto yCoordinate = registers[d.y] % DisplaySpecs::PIXEL_HEIGHT;
    flagRegister = 0;

    for (auto i = 0; i < d.n; i++) {
        uint8_t spriteData = memory.getByte(index + i);

        xCoordinate = registers[d.x] % DisplaySpecs::PIXEL_WIDTH;
        for (auto j = 0; j < BYTE_SIZE; j++) {
            auto isBitSet = (spriteData >> (BYTE_SIZE - j - 1)) & 1;

            if (isBitSet) {
                display.flip(xCoordinate, yCoordinate);
                flagRegister = display.getPixel(xCoordinate, yCoordinate);
                displayUpdated = true;
            }

            if (xCoordinate == DisplaySpecs::PIXEL_WIDTH - 1) break;
            xCoordinate += 1;
        }

        yCoordinate += 1;
        if (yCoordinate == DisplaySpecs::PIXEL_HEIGHT - 1) break;
    }
}

auto Emulator::clearDisplay(void) -> void {
    for (auto i = 0; i < DisplaySpecs::PIXEL_WIDTH; i++)
        for (auto j = 0; j < DisplaySpecs::PIXEL_HEIGHT; j++)
            display.unset(i, j);
}

auto Emulator::writeMemory(DecodedInstruction d) -> void {
    for (auto i = 0; i <= d.x; i++)
        memory.writeByte(index + i, registers[i]);
}

auto Emulator::readMemory(DecodedInstruction d) -> void {
    for (auto i = 0; i <= d.x; i++)
        registers[i] = memory.getByte(index + i);
}

auto Emulator::convertBinary(DecodedInstruction d) -> void {
    memory.writeByte(index, (registers[d.x] / 100) % 10);
    memory.writeByte(index + 1, (registers[d.x] / 10) % 10);
    memory.writeByte(index + 2, registers[d.x] % 10);
}
