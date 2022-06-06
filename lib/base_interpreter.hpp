#include <array>

#pragma once
class BaseInterpreter {
public:
    std::array<uint8_t, 4096> memory;
    std::array<uint8_t, 16> registers;
    std::array<uint16_t, 16> stack;
    std::array<bool, 16> keyboard;

    uint8_t stack_pointer;
    uint8_t sound_timer;
    uint8_t delay_timer;

    uint16_t index_register;
    uint16_t program_counter;

    uint8_t stop_execution_flag;
    uint8_t continue_execution_key;

    Framebuffer *framebuffer;
};