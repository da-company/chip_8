#include <vector>

class BaseRender {
public:
    static const uint8_t SCREEN_WIDTH = 64;
    static const uint8_t SCREEN_HEIGHT = 32;

    virtual void draw(const std::vector<uint8_t> &memory) = 0;
};