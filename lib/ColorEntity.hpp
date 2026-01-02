#pragma once
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

    float getRed() const { return this->color[Config::COLOR_R_INDEX]; }
    float getGreen() const { return this->color[Config::COLOR_G_INDEX]; }
    float getBlue() const { return this->color[Config::COLOR_B_INDEX]; }
    float getAlpha() const { return this->color[Config::COLOR_ALPHA_INDEX]; }
    float getHue() const;
    float getSaturation() const;
    float getValue() const;

    void setRed(float next_r) { this->color[Config::COLOR_R_INDEX] = next_r; }
    void setGreen(float next_g) { this->color[Config::COLOR_G_INDEX] = next_g; }
    void setBlue(float next_b) { this->color[Config::COLOR_B_INDEX] = next_b; }
    void setAlpha(float next_a) { this->color[Config::COLOR_ALPHA_INDEX] = next_a; }
    void setHue(float next_h);
    void setSaturation(float next_s);
    void setValue(float next_v);
};