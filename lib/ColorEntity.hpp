#include "Config.hpp"
#include <array>

class ColorEntity
{
public:
    ColorEntity(float r = Config::CLEAR_R, float g = Config::CLEAR_G, float b = Config::CLEAR_B, float a = Config::CLEAR_ALPHA)
        : red(r), green(g), blue(b), alpha(a) {}

    float green;
    float red;
    float blue;
    float alpha;

    std::array<float, 4> to_array() const
    {
        return {this->red, this->green, this->blue, this->alpha};
    }
};