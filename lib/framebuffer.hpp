#include <bitset>
#include <array>
#include "src/render.hpp"

class Framebuffer {
private:
    typedef BaseRender Render;

    Render *render;
    std::vector<uint8_t> buffer;

    bool draw_pixel(uint16_t x, uint16_t y);

public:
    Framebuffer(Render *render);

    void clean();
    uint8_t draw(uint8_t *memory, uint8_t len, uint8_t x, uint8_t y);
};

Framebuffer::Framebuffer(Render *render) : render(render) {
    buffer.resize(Render::SCREEN_WIDTH * Render::SCREEN_HEIGHT);
}

void Framebuffer::clean() {
    buffer.clear();
    render->draw(buffer);
}

uint8_t Framebuffer::draw(uint8_t *memory, uint8_t len, uint8_t x, uint8_t y) {
    bool is_cleared = false;

    for (auto n = 0; n < len; n++) {
        auto pixel = memory[n];

        for (auto b = 0; b < 8; b++) {
            if (pixel & 0x80) {
                is_cleared = draw_pixel(x + b, y + n) || is_cleared;
            }

            pixel = pixel << 1;
        }
    }

    render->draw(buffer);
    return is_cleared ? 1 : 0;
}

bool Framebuffer::draw_pixel(uint16_t x, uint16_t y) {
    while (x > Render::SCREEN_WIDTH - 1) x -= Render::SCREEN_WIDTH;
    while (x < 0) x += Render::SCREEN_WIDTH;
    while (y > Render::SCREEN_HEIGHT - 1) y -= Render::SCREEN_HEIGHT;
    while (y < 0) y += Render::SCREEN_HEIGHT;

    size_t position = y * Render::SCREEN_WIDTH + x;
    buffer[position] ^= 0x1;

    return !buffer[position];
}


