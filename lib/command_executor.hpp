#include <memory>
#include <istream>
#include "base_interpreter.hpp"
#include "instruction.hpp"
#include "functions.hpp"

class CommandExecutor {
private:
    BaseInterpreter *interpreter_ptr;

    static const uint16_t NEXT_PC = 2;
    static const uint16_t SKIP_PC = 4;

    void cls();
    void ret();
    void jp_addr(uint16_t opcode);
    void call_addr(uint16_t opcode);
    void se_vx_byte(uint16_t opcode);
    void sne_vx_byte(uint16_t opcode);
    void se_vx_vy(uint16_t opcode);
    void ld_vx_byte(uint16_t opcode);
    void add_byte(uint16_t opcode);
    void ld_vx_vy(uint16_t opcode);
    void or_vx_vy(uint16_t opcode);
    void add_VX_VY(uint16_t opcode);
    void xor_vx_vy(uint16_t opcode);
    void add_vx_vy_carry(uint16_t opcode);
    void sub_vx_vy(uint16_t opcode);
    void shr_vx_vy(uint16_t opcode);
    void subn_vx_vy(uint16_t opcode);
    void shl_vx(uint16_t opcode);
    void sne_vx_vy(uint16_t opcode);
    void ld_i_addr(uint16_t opcode);
    void jp_v0_addr(uint16_t opcode);
    void rnd_vy_byte(uint16_t opcode);
    void drw_vy_vy_n(uint16_t opcode);
    void skp_vx(uint16_t opcode);
    void skpn_vx(uint16_t opcode);
    void ld_vx_dt(uint16_t opcode);
    void ld_vx_k(uint16_t opcode);
    void ld_dt_vx(uint16_t opcode);
    void ld_st_vx(uint16_t opcode);
    void add_i_vx(uint16_t opcode);
    void ld_f_vx(uint16_t opcode);
    void ld_b_vx(uint16_t opcode);
    void ld_i_vx(uint16_t opcode);
    void ld_vx_i(uint16_t opcode);
public:
    CommandExecutor(BaseInterpreter *interpreter);

    void execute(const Instruction *instruction, uint16_t opcode);
};

CommandExecutor::CommandExecutor(BaseInterpreter *interpreter) : interpreter_ptr(interpreter) {
}

void CommandExecutor::execute(const Instruction *instruction, uint16_t opcode) {
    if (instruction == nullptr) {
        std::cout << "Unknown opcode " << to_hex(opcode) << std::endl;
        return;
    }

    switch (*instruction) {
        case ::CLS:
            cls();
            break;
        case ::RET:
            ret();
            break;
        case ::JP_ADDR:
            jp_addr(opcode);
            break;
        case ::CALL_ADDR:
            call_addr(opcode);
            break;
        case ::SE_VX_BYTE:
            se_vx_byte(opcode);
            break;
        case ::SNE_VX_BYTE:
            sne_vx_byte(opcode);
            break;
        case ::SE_VX_VY:
            se_vx_vy(opcode);
            break;
        case ::LD_VX_BYTE:
            ld_vx_byte(opcode);
            break;
        case ::ADD_VX_BYTE:
            add_byte(opcode);
            break;
        case ::LD_VX_VY:
            ld_vx_vy(opcode);
            break;
        case ::OR_VX_VY:
            or_vx_vy(opcode);
            break;
        case ::AND_VX_VY:
            add_VX_VY(opcode);
            break;
        case ::XOR_VX_VY:
            xor_vx_vy(opcode);
            break;
        case ::ADD_VX_VY_CARRY:
            add_vx_vy_carry(opcode);
            break;
        case ::SUB_VX_VY:
            sub_vx_vy(opcode);
            break;
        case ::SHR_VX_VY:
            shr_vx_vy(opcode);
            break;
        case ::SUBN_VX_VY:
            subn_vx_vy(opcode);
            break;
        case ::SHL_VX:
            shl_vx(opcode);
            break;
        case ::SNE_VX_VY:
            sne_vx_vy(opcode);
            break;
        case ::LD_I_ADDR:
            ld_i_addr(opcode);
            break;
        case ::JP_V0_ADDR:
            jp_v0_addr(opcode);
            break;
        case ::RND_VX_BYTE:
            rnd_vy_byte(opcode);
            break;
        case ::DRW_VX_VY_N:
            drw_vy_vy_n(opcode);
            break;
        case ::SKP_VX:
            skp_vx(opcode);
            break;
        case ::SKPN_VX:
            skpn_vx(opcode);
            break;
        case ::LD_VX_DT:
            ld_vx_dt(opcode);
            break;
        case ::LD_VX_K:
            ld_vx_k(opcode);
            break;
        case ::LD_DT_VX:
            ld_dt_vx(opcode);
            break;
        case ::LD_ST_VX:
            ld_st_vx(opcode);
            break;
        case ::ADD_I_VX:
            add_i_vx(opcode);
            break;
        case ::LD_F_VX:
            ld_f_vx(opcode);
            break;
        case ::LD_B_VX:
            ld_b_vx(opcode);
            break;
        case ::LD_I_VX:
            ld_i_vx(opcode);
            break;
        case ::LD_VX_I:
            ld_vx_i(opcode);
            break;
    }
}

// 0x00E0
void CommandExecutor::cls() {
    interpreter_ptr->framebuffer->clean();
    interpreter_ptr->program_counter += 2;
}

// 0x00EE
void CommandExecutor::ret() {
    interpreter_ptr->program_counter = interpreter_ptr->stack[--interpreter_ptr->stack_pointer];
}

// 0x1nnn
void CommandExecutor::jp_addr(uint16_t opcode) {
    uint16_t nnn = opcode & 0x0FFF;

    interpreter_ptr->program_counter = nnn;
}

// 0x2nnn
void CommandExecutor::call_addr(uint16_t opcode) {
    uint16_t nnn = opcode & 0x0FFF;

    interpreter_ptr->stack[interpreter_ptr->stack_pointer++] = interpreter_ptr->program_counter + 2;
    interpreter_ptr->program_counter = nnn;
}

// 0x3xkk
void CommandExecutor::se_vx_byte(uint16_t opcode) {
    uint8_t k = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;

    uint16_t pointer = interpreter_ptr->registers[k] == kk ? 4 : 2;
    interpreter_ptr->program_counter += pointer;
}

// 0x4xkk
void CommandExecutor::sne_vx_byte(uint16_t opcode) {
    uint8_t k = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;

    uint16_t pointer = interpreter_ptr->registers[k] != kk ? 4 : 2;
    interpreter_ptr->program_counter += pointer;
}

// 0x5xy0
void CommandExecutor::se_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];

    uint16_t pointer = vx == vy ? SKIP_PC : NEXT_PC;
    interpreter_ptr->program_counter += pointer;
}

// 0x6xkk
void CommandExecutor::ld_vx_byte(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;

    interpreter_ptr->registers[x] = kk;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x7xkk
void CommandExecutor::add_byte(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;

    interpreter_ptr->registers[x] += kk;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy0
void CommandExecutor::ld_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    interpreter_ptr->registers[x] = interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy1
void CommandExecutor::or_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    interpreter_ptr->registers[x] |= interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy2
void CommandExecutor::add_VX_VY(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    interpreter_ptr->registers[x] &= interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy3
void CommandExecutor::xor_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    interpreter_ptr->registers[x] ^= interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy4
void CommandExecutor::add_vx_vy_carry(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];

    interpreter_ptr->registers[0xF] = vy > (0xFF - vx) ? 1 : 0;
    interpreter_ptr->registers[x] += interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy5
void CommandExecutor::sub_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];

    interpreter_ptr->registers[0xF] = vx > vy ? 1 : 0;
    interpreter_ptr->registers[x] -= interpreter_ptr->registers[y];
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy6
void CommandExecutor::shr_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;

    interpreter_ptr->registers[0xF] = interpreter_ptr->registers[x] & 0x1;
    interpreter_ptr->registers[x] >>= 1;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xy7
void CommandExecutor::subn_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];

    interpreter_ptr->registers[0xF] = vy > vx ? 1 : 0;
    interpreter_ptr->registers[x] = vy - vx;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x8xyE
void CommandExecutor::shl_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;

    interpreter_ptr->registers[0xF] = interpreter_ptr->registers[x] >> 7;
    interpreter_ptr->registers[x] <<= 1;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0x9xy0
void CommandExecutor::sne_vx_vy(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];

    uint16_t pointer = vx != vy ? SKIP_PC : NEXT_PC;
    interpreter_ptr->program_counter += pointer;
}

// 0xAnnn
void  CommandExecutor::ld_i_addr(uint16_t opcode) {
    uint16_t nnn = opcode & 0x0FFF;

    interpreter_ptr->index_register = nnn;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xBnnn
void CommandExecutor::jp_v0_addr(uint16_t opcode) {
    uint16_t nnn = opcode & 0x0FFF;
    uint8_t vx = interpreter_ptr->registers[0x0];

    interpreter_ptr->program_counter = nnn + vx;
}

// 0xCxkk
void CommandExecutor::rnd_vy_byte(uint16_t opcode) {
    uint8_t k = (opcode & 0x0F00) >> 8;
    uint8_t kk = opcode & 0x00FF;
    uint8_t rnd = rand() % 256;

    interpreter_ptr->registers[k] = rnd & kk;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xDxyn
void CommandExecutor::drw_vy_vy_n(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t vx = interpreter_ptr->registers[x];
    uint8_t vy = interpreter_ptr->registers[y];
    uint8_t len = opcode & 0x000F;
    auto memory = &interpreter_ptr->memory[interpreter_ptr->index_register];

    interpreter_ptr->registers[0xF] = interpreter_ptr->framebuffer->draw(memory, len, vx, vy);
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xEx9E
void CommandExecutor::skp_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    uint16_t pointer = interpreter_ptr->keyboard[vx] ? SKIP_PC : NEXT_PC;
    interpreter_ptr->program_counter += pointer;
}

// 0xExA1
void CommandExecutor::skpn_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    uint16_t pointer = !interpreter_ptr->keyboard[vx] ? SKIP_PC : NEXT_PC;
    interpreter_ptr->program_counter += pointer;
}

// 0xFx07
void CommandExecutor::ld_vx_dt(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;

    interpreter_ptr->registers[x] = interpreter_ptr->delay_timer;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx0A
void CommandExecutor::ld_vx_k(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    interpreter_ptr->stop_execution_flag = 0x1;
    interpreter_ptr->continue_execution_key = vx;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx15
void CommandExecutor::ld_dt_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    interpreter_ptr->delay_timer = vx;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx18
void CommandExecutor::ld_st_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    interpreter_ptr->sound_timer = vx;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx1E
void CommandExecutor::add_i_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];

    interpreter_ptr->registers[0xF] = interpreter_ptr->index_register + vx > 0x0FFF ? 1 : 0;
    interpreter_ptr->index_register += vx;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx29
void CommandExecutor::ld_f_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;

    interpreter_ptr->index_register = interpreter_ptr->registers[x] * 5;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx33
void CommandExecutor::ld_b_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t vx = interpreter_ptr->registers[x];
    uint16_t index = interpreter_ptr->index_register;

    interpreter_ptr->memory[index] = vx / 100;
    interpreter_ptr->memory[index + 1] = (vx / 10) % 10;
    interpreter_ptr->memory[index + 2] = (vx % 100) % 10;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx55
void CommandExecutor::ld_i_vx(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint16_t index = interpreter_ptr->index_register;

    std::memcpy(&interpreter_ptr->registers[index], &interpreter_ptr->memory[index], x);

    interpreter_ptr->index_register += x + 1;
    interpreter_ptr->program_counter += NEXT_PC;
}

// 0xFx65
void CommandExecutor::ld_vx_i(uint16_t opcode) {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint16_t index = interpreter_ptr->index_register;

    std::memcpy(&interpreter_ptr->memory[index], &interpreter_ptr->registers[index], x);

    interpreter_ptr->index_register += x + 1;
    interpreter_ptr->program_counter += NEXT_PC;
}
