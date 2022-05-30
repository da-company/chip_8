#include "frameworks/SDL2.framework/Headers/SDL.h"
#include "lib/base_render.hpp"

class Render : public BaseRender {
private:
    static const uint8_t PIXEL_SIZE = 12;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect screen_rect;

public:
    Render();
    ~Render();

    void draw(const std::vector<uint8_t> &memory) override;
};

Render::Render() {
    window = SDL_CreateWindow(
            "ship 8",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH * PIXEL_SIZE,
            SCREEN_HEIGHT * PIXEL_SIZE,
            SDL_WINDOW_METAL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    screen_rect.x = 0;
    screen_rect.y = 0;
    screen_rect.h = SCREEN_HEIGHT;
    screen_rect.w = SCREEN_WIDTH;
}

Render::~Render() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Render::draw(const std::vector<uint8_t> &memory) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 170, 169, 255);
    for (auto i = 0; i < screen_rect.w * screen_rect.h; i++) {
        auto x = screen_rect.x + i % screen_rect.w;
        auto y = (screen_rect.y + i / screen_rect.w) * SCREEN_WIDTH;

        if (!memory[x + y]) continue;

        SDL_Rect rect = {
            screen_rect.x * PIXEL_SIZE + (i % screen_rect.w) * PIXEL_SIZE,
            screen_rect.y * PIXEL_SIZE + i / screen_rect.w * PIXEL_SIZE,
            PIXEL_SIZE,
            PIXEL_SIZE
        };

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}
