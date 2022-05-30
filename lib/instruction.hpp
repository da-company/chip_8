#include <array>

#pragma once

enum Instruction {
    CLS = 0x00E0,
    RET = 0x00EE,
    JP_ADDR = 0x1000,
    CALL_ADDR = 0x2000,
    SE_VX_BYTE = 0x3000,
    SNE_VX_BYTE = 0x4000,
    SE_VX_VY = 0x5000,
    LD_VX_BYTE = 0x6000,
    ADD_VX_BYTE = 0x7000,
    LD_VX_VY = 0x8000,
    OR_VX_VY = 0x8001,
    AND_VX_VY = 0x8002,
    XOR_VX_VY = 0x8003,
    ADD_VX_VY_CARRY = 0x8004,
    SUB_VX_VY = 0x8005,
    SHR_VX_VY = 0x8006,
    SUBN_VX_VY = 0x8007,
    SHL_VX = 0x800E,
    SNE_VX_VY = 0x9000,
    LD_I_ADDR = 0xA000,
    JP_V0_ADDR = 0xB000,
    RND_VX_BYTE = 0xC000,
    DRW_VX_VY_N = 0xD000,
    SKP_VX = 0xE09E,
    SKPN_VX = 0xE0A1,
    LD_VX_DT = 0xF007,
    LD_VX_K = 0xF00A,
    LD_DT_VX = 0xF015,
    LD_ST_VX = 0xF018,
    ADD_I_VX = 0xF01E,
    LD_F_VX = 0xF029,
    LD_B_VX = 0xF033,
    LD_I_VX = 0xF055,
    LD_VX_I = 0xF065
};

uint16_t instruction_mask(Instruction instruction) {
    switch (instruction) {
        case ::CLS:
            return 0xFFFF;
        case ::RET:
            return 0xFFFF;
        case ::JP_ADDR:
            return 0xF000;
        case ::CALL_ADDR:
            return 0xF000;
        case ::SE_VX_BYTE:
            return 0xF000;
        case ::SNE_VX_BYTE:
            return 0xF000;
        case ::SE_VX_VY:
            return 0xF00F;
        case ::LD_VX_BYTE:
            return 0xF000;
        case ::ADD_VX_BYTE:
            return 0xF000;
        case ::LD_VX_VY:
            return 0xF00F;
        case ::OR_VX_VY:
            return 0xF00F;
        case ::AND_VX_VY:
            return 0xF00F;
        case ::XOR_VX_VY:
            return 0xF00F;
        case ::ADD_VX_VY_CARRY:
            return 0xF00F;
        case ::SUB_VX_VY:
            return 0xF00F;
        case ::SHR_VX_VY:
            return 0xF00F;
        case ::SUBN_VX_VY:
            return 0xF00F;
        case ::SHL_VX:
            return 0xF00F;
        case ::SNE_VX_VY:
            return 0xF000;
        case ::LD_I_ADDR:
            return 0xF000;
        case ::JP_V0_ADDR:
            return 0xF000;
        case ::RND_VX_BYTE:
            return 0xF000;
        case ::DRW_VX_VY_N:
            return 0xF000;
        case ::SKP_VX:
            return 0xF0FF;
        case ::SKPN_VX:
            return 0xF0FF;
        case ::LD_VX_DT:
            return 0xF00F;
        case ::LD_VX_K:
            return 0xF00F;
        case ::LD_DT_VX:
            return 0xF0FF;
        case ::LD_ST_VX:
            return 0xF0FF;
        case ::ADD_I_VX:
            return 0xF0FF;
        case ::LD_F_VX:
            return 0xF0FF;
        case ::LD_B_VX:
            return 0xF0FF;
        case ::LD_I_VX:
            return 0xF0FF;
        case ::LD_VX_I:
            return 0xF0FF;
    }
}

const auto instructions = std::array<Instruction, 35>{
        CLS, RET, JP_ADDR, CALL_ADDR, SE_VX_BYTE, SNE_VX_BYTE, SE_VX_VY, LD_VX_BYTE, ADD_VX_BYTE, LD_VX_VY, OR_VX_VY,
        AND_VX_VY, XOR_VX_VY, ADD_VX_VY_CARRY, SUB_VX_VY, SHR_VX_VY, SUBN_VX_VY, SHL_VX, SNE_VX_VY, LD_I_ADDR, JP_V0_ADDR, RND_VX_BYTE,
        DRW_VX_VY_N, SKP_VX, SKPN_VX, LD_VX_DT, LD_VX_K, LD_DT_VX, LD_ST_VX, ADD_I_VX, LD_F_VX,
        LD_B_VX, LD_I_VX, LD_VX_I
};