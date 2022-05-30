#include <array>
#include <string>
#include <fstream>
#include <algorithm>
#include "framebuffer.hpp"
#include "base_interpreter.hpp"
#include "command_executor.hpp"
#include "instruction.hpp"
#include "fonts.hpp"

class Interpreter : public BaseInterpreter {
private:
    CommandExecutor executor = CommandExecutor(this);

public:
    Interpreter(Framebuffer *framebuffer) noexcept;

    void load(std::string &&filename);

    uint16_t fetch_opcode();
    const Instruction* decode(uint16_t opcode);
    void execute(const Instruction *instruction, uint16_t opcode);
    void update_timers();

    const bool is_stop_execution();

    void key_pressed(uint8_t code);
    void key_released(uint8_t code);
};

Interpreter::Interpreter(Framebuffer *framebuffer) noexcept {
    this->framebuffer = framebuffer;

    std::fill(memory.begin(), memory.end(), 0x0);
    std::fill(registers.begin(), registers.end(), 0x0);
    std::fill(stack.begin(), stack.end(), 0x0);
    std::fill(keyboard.begin(), keyboard.end(), false);

    std::copy(fonts.begin(), fonts.end(), memory.begin());

    stack_pointer = 0;
    sound_timer = 0;
    delay_timer = 0;

    index_register = 0;
    program_counter = 0x200;

    stop_execution_flag = 0x0;
    continue_execution_key = 0x0;
}

void Interpreter::load(std::string &&filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (file.is_open()) {
        auto begin = std::istreambuf_iterator<char>(file);
        auto end = std::istreambuf_iterator<char>();
        std::copy(begin, end, memory.begin() + program_counter);

        file.close();
    }
}

uint16_t Interpreter::fetch_opcode() {
    return memory[program_counter] << 8 | memory[program_counter + 1];
}

const Instruction* Interpreter::decode(uint16_t opcode) {
    auto predicate = [&](const Instruction &instruction) {
        return instruction == (opcode & instruction_mask(instruction));
    };
    auto it = std::find_if(instructions.begin(), instructions.end(), predicate);
    if (it == instructions.end()) {
        std::cout << to_hex(opcode >> 12) << std::endl;
        return nullptr;
    }

    return it;
}

void Interpreter::execute(const Instruction *instruction, uint16_t opcode) {
    executor.execute(instruction, opcode);
}

void Interpreter::update_timers() {
    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
    }
}

const bool Interpreter::is_stop_execution() {
    return stop_execution_flag == 0x1;
}

void Interpreter::key_pressed(uint8_t code) {
    keyboard[code] = true;

    if (stop_execution_flag == 0x1) {
        registers[continue_execution_key] = code;
        stop_execution_flag = 0x0;
    }
}

void Interpreter::key_released(uint8_t code) {
    keyboard[code] = false;
}
