#include <string>
#include <map>
#include "lib/interpreter.hpp"

class Application {
private:
    std::unique_ptr<Interpreter> interpreter_ptr;
    std::unique_ptr<Render> render_ptr;
    std::unique_ptr<Framebuffer> framebuffer_ptr;

    bool is_running = true;
    Uint32 last_update_frame;

    std::map<SDL_Keycode, uint8_t> keyboard = {
        {SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3}, {SDLK_4, 0xC},
        {SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_r, 0xD},
        {SDLK_a, 0x7}, {SDLK_s, 0x8}, {SDLK_d, 0x9}, {SDLK_f, 0xE},
        {SDLK_z, 0xA}, {SDLK_x, 0x0}, {SDLK_c, 0xB}, {SDLK_v, 0xF}
    };

    void handle(SDL_Event &event);
    void execute_opcode();
    void quit_event();
    void keyboard_down_event(SDL_KeyboardEvent &event);
    void keyboard_up_event(SDL_KeyboardEvent &event);
public:
    Application(std::string &&filename);

    const int run();
};

Application::Application(std::string &&filename) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("SDL can't initialize.");
    }

    render_ptr = std::make_unique<Render>();
    framebuffer_ptr = std::make_unique<Framebuffer>(render_ptr.get());
    interpreter_ptr = std::make_unique<Interpreter>(framebuffer_ptr.get());

    interpreter_ptr->load(std::move(filename));
}

const int Application::run() {
    SDL_Event event;

    while (is_running) {
        auto begin_frame = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            handle(event);
        }

        if (!interpreter_ptr->is_stop_execution()) {
            execute_opcode();
        }

        auto end_frame = SDL_GetTicks();
        if (end_frame - begin_frame < 1000 / 500) {
            SDL_Delay(1000 / 500 - (end_frame - begin_frame));
        }
    }
    
    SDL_Quit();
    
    return 0;
}

void Application::handle(SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        quit_event();
    } else if (event.type == SDL_KEYDOWN) {
        keyboard_down_event(event.key);
    } else if (event.type == SDL_KEYUP) {
        keyboard_up_event(event.key);
    }
}

void Application::execute_opcode() {
    auto current_frame = SDL_GetTicks();

    if (current_frame - last_update_frame < 2) {
        return;
    }

    auto opcode = interpreter_ptr->fetch_opcode();
    auto instruction = interpreter_ptr->decode(opcode);

    interpreter_ptr->execute(instruction, opcode);
    interpreter_ptr->update_timers();

    last_update_frame = SDL_GetTicks();
}

void Application::quit_event() {
    is_running = false;
}

void Application::keyboard_down_event(SDL_KeyboardEvent &event) {
    auto keycode = event.keysym.sym;

    if (keycode == SDLK_ESCAPE) {
        quit_event();
        return;
    }

    if (keyboard.find(keycode) == keyboard.end()) {
        return;
    }

    interpreter_ptr->key_pressed(keyboard[keycode]);
}

void Application::keyboard_up_event(SDL_KeyboardEvent &event) {
    auto keycode = event.keysym.sym;

    if (keyboard.find(keycode) == keyboard.end()) {
        return;
    }

    interpreter_ptr->key_released(keyboard[keycode]);
}

