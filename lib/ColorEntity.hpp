#include "Config.hpp"
#include <array>

class ColorEntity
{
public:
    ColorEntity(
        float r = Config::CLEAR_R,
        float g = Config::CLEAR_G,
        float b = Config::CLEAR_B,
        float a = Config::CLEAR_ALPHA)
        : color{r, g, b, a} {}

    std::array<float, 4> color;
};