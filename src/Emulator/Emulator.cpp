#include "Emulator.h"

#include <iostream>
#include <stdlib.h>

#include "DecodedInstruction.h"

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
        case 0:
            if (d.nnn == 0xE0) clearDisplay();
            if (d.nnn == 0xEE) pc = stack.pop();
            break;
        case 1:
            pc = d.nnn;
            break;
        case 2:
            stack.push(pc);
            pc = d.nnn;
            break;
        case 3:
            if (registers[d.x] == d.nn) pc += 2;
            break;
        case 4:
            if (registers[d.x] != d.nn) pc += 2;
            break;
        case 5:
            if (d.n == 0 && registers[d.x] == registers[d.y]) pc += 2;
            break;
        case 9:
            if (d.n == 0 && registers[d.x] != registers[d.y]) pc += 2;
            break;
        case 6:
            registers[d.x] = d.nn;
            break;
        case 7:
            registers[d.x] += d.nn;
            break;
        case 8:
            if (d.n == 0) registers[d.x] = registers[d.y];
            if (d.n == 1) registers[d.x] |= registers[d.y];
            if (d.n == 2) registers[d.x] &= registers[d.y];
            if (d.n == 3) registers[d.x] ^= registers[d.y];
            if (d.n == 4) {
                flagRegister = registers[d.x] + registers[d.y] > UINT8_MAX;
                registers[d.x] += registers[d.y];
            }
            if (d.n == 5) {
                flagRegister = registers[d.x] >= registers[d.y];
                registers[d.x] -= registers[d.y];
            }
            if (d.n == 7) {
                flagRegister = registers[d.y] >= registers[d.x];
                registers[d.x] = registers[d.y] - registers[d.x];
            }
            if (d.n == 6) {
                flagRegister = registers[d.x] & 1;
                registers[d.x] >>= 1;
            }
            if (d.n == 0xE) {
                flagRegister = registers[d.x] >> 7;
                registers[d.x] <<= 1;
            }
            break;
        case 0xA:
            index = d.nnn;
            break;
        case 0xB:
            pc = d.nnn + registers[0];
            break;
        case 0xC:
            registers[d.x] = (rand() % 0xffff) & d.nn;
            break;
        case 0xD:
            updateDisplay(d);
            break;
        case 0xE:
            if (d.nn == 0x9E && keysPressed[registers[d.x]]) pc += 2;
            if (d.nn == 0xA1 && !keysPressed[registers[d.x]]) pc += 2;
            break;
        case 0xF:
            if (d.nn == 0x7) registers[d.x] = delayTimer;
            if (d.nn == 0x15) delayTimer = registers[d.x];
            if (d.nn == 0x18) soundTimer = registers[d.x];
            if (d.nn == 0x1E) index += registers[d.x];
            if (d.nn == 0xA) {
                if (isBlocked && lastPressedKey != -1)
                    registers[d.x] = lastPressedKey;
                else
                    isBlocked = true;
            }
            if (d.nn == 0x29) index = registers[d.x] * 5;
            if (d.nn == 0x33) {
                memory.writeByte(index, (registers[d.x] / 100) % 10);
                memory.writeByte(index + 1, (registers[d.x] / 10) % 10);
                memory.writeByte(index + 2, registers[d.x] % 10);
            }
            if (d.nn == 0x55)
                for (int i = 0; i <= d.x; i++)
                    memory.writeByte(index + i, registers[i]);
            if (d.nn == 0x65)
                for (int i = 0; i <= d.x; i++)
                    registers[i] = memory.getByte(index + i);
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