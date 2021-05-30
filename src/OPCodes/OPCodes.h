#pragma once


namespace OPCodes {
    constexpr int INITIAL = 0;
    constexpr int CLEAR_DISPLAY = 0xE0;
    constexpr int POP_PC = 0xEE;

    constexpr int SET_PC_EQ_NNN = 1;
    constexpr int PUSH_PC = 2;
    constexpr int X_EQ_NN_PC_INC = 3;
    constexpr int X_NEQ_NN_PC_INC = 4;
    constexpr int X_EQ_Y_PC_INC = 5;
    constexpr int X_NEQ_Y_PC_INC = 9;

    constexpr int SET_X_NN = 6;
    constexpr int ADD_X_NN = 7;

    constexpr int ARITH_LOGIC = 8;
    constexpr int SET_X_EQ_Y = 0;
    constexpr int SET_X_OR_Y = 1;
    constexpr int SET_X_AND_Y = 2;
    constexpr int SET_X_XOR_Y = 3;
    constexpr int SET_X_ADD_Y = 4;
    constexpr int SET_X_SUB_Y = 5;
    constexpr int SET_X_EQ_Y_SUB_X = 7;
    constexpr int SET_X_RSHIFT = 6;
    constexpr int SET_X_LSHIFT = 0xE;

    constexpr int SET_IDX_NN = 0xA;
    constexpr int SET_PC_EQ_V0_ADD_NNN = 0xB;
    constexpr int RAND_INT = 0xC;
    constexpr int DRAW = 0xD;

    constexpr int READ_KEY = 0xE;
    constexpr int KEY_PRESSED = 0x9E;
    constexpr int KEY_NPRESSED = 0xA1;

    constexpr int OTHER = 0xF;
    constexpr int SET_X_EQ_DELAY = 0x7;
    constexpr int SET_DELAY_EQ_X = 0x15;
    constexpr int SET_SOUND_EQ_X = 0x18;
    constexpr int SET_IDX_ADD_X = 0x1E;
    constexpr int BLOCK_KEY_READ = 0xA;
    constexpr int SET_IDX_FONT = 0x29;
    constexpr int CONVERT_BINARY = 0x33;
    constexpr int WRITE_MEMORY = 0x55;
    constexpr int READ_MEMORY = 0x65;
}