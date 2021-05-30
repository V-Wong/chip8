#include "Emulator.hpp"

#include <iostream>
#include <stdlib.h>

#include "../OPCodes/OPCodes.h"


uint16_t joinBytes(uint8_t msb, uint8_t lsb) {
    return ((uint16_t)msb << 8) | lsb;
}

void Emulator::load(uint16_t start, std::vector<uint8_t> bytes) {
    for (int i = 0; i < bytes.size(); i++)
        memory.writeByte(start + i, bytes.at(i));
}

void Emulator::run(void) {
    uint16_t instruction = fetch();
    pc += 2;
    displayUpdated = false;
    execute({instruction});
    lastPressedKey = -1;
    decrementTimer();
}

uint16_t Emulator::fetch(void) {
    uint16_t instruction = joinBytes(memory.getByte(pc), memory.getByte(pc + 1));
    return instruction;
}

void Emulator::decrementTimer(void) {
    if (steps % 8 == 0) {
        delayTimer -= 1;
        steps = 0;
    } else {
        steps += 1;
    }
}

void Emulator::execute(DecodedInstruction d) {
    switch (d.type) {
        case OPCodes::INITIAL:
            if (d.nnn == OPCodes::CLEAR_DISPLAY) clearDisplay();
            if (d.nnn == 0xEE) {
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
            if (registers[d.x] == d.nn) pc += 2;
            break;
        case OPCodes::X_NEQ_NN_PC_INC:
            if (registers[d.x] != d.nn) pc += 2;
            break;
        case OPCodes::X_EQ_Y_PC_INC:
            if (d.n == 0 && registers[d.x] == registers[d.y]) pc += 2;
            break;
        case OPCodes::X_NEQ_Y_PC_INC:
            if (d.n == 0 && registers[d.x] != registers[d.y]) pc += 2;
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
                flagRegister = registers[d.x] >> 7;
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
            if (d.nn == OPCodes::KEY_PRESSED && keysPressed[registers[d.x]]) pc += 2;
            if (d.nn == OPCodes::KEY_NPRESSED && !keysPressed[registers[d.x]]) pc += 2;
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

void Emulator::updateDisplay(DecodedInstruction d) {
    uint8_t xCoordinate = registers[d.x] % DisplaySpecs::PIXEL_WIDTH;
    uint8_t yCoordinate = registers[d.y] % DisplaySpecs::PIXEL_HEIGHT;
    flagRegister = 0;

    for (int i = 0; i < d.n; i++) {
        uint8_t spriteData = memory.getByte(index + i);

        xCoordinate = registers[d.x] % DisplaySpecs::PIXEL_WIDTH;
        for (int j = 0; j < 8; j++) {
            bool isBitSet = (spriteData >> (8 - j - 1)) & 1;

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

void Emulator::clearDisplay(void) {
    for (int i = 0; i < DisplaySpecs::PIXEL_WIDTH; i++)
        for (int j = 0; j < DisplaySpecs::PIXEL_HEIGHT; j++)
            display.unset(i, j);
}

void Emulator::writeMemory(DecodedInstruction d) {
    for (int i = 0; i <= d.x; i++)
        memory.writeByte(index + i, registers[i]);
}

void Emulator::readMemory(DecodedInstruction d) {
    for (int i = 0; i <= d.x; i++)
        registers[i] = memory.getByte(index + i);
}

void Emulator::convertBinary(DecodedInstruction d) {
    memory.writeByte(index, (registers[d.x] / 100) % 10);
    memory.writeByte(index + 1, (registers[d.x] / 10) % 10);
    memory.writeByte(index + 2, registers[d.x] % 10);
}
