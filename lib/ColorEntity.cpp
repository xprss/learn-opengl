#include "ColorEntity.hpp"

float ColorEntity::getHue() const
{
    float r = this->getRed();
    float g = this->getGreen();
    float b = this->getBlue();

    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float delta = max - min;

    if (delta == 0)
        return 0.0f; // Undefined hue

    float hue;
    if (max == r)
        hue = 60.0f * fmod(((g - b) / delta), 6.0f);
    else if (max == g)
        hue = 60.0f * (((b - r) / delta) + 2.0f);
    else // max == b
        hue = 60.0f * (((r - g) / delta) + 4.0f);

    if (hue < 0)
        hue += 360.0f;

    return hue;
}
float ColorEntity::getSaturation() const
{
    float r = this->getRed();
    float g = this->getGreen();
    float b = this->getBlue();

    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float delta = max - min;

    if (max == 0)
        return 0.0f;

    return delta / max;
}
float ColorEntity::getValue() const
{
    float r = this->getRed();
    float g = this->getGreen();
    float b = this->getBlue();

    return std::max({r, g, b});
}

void ColorEntity::setHue(float next_h)
{
    float s = this->getSaturation();
    float v = this->getValue();

    float c = v * s;
    float x = c * (1 - fabs(fmod(next_h / 60.0f, 2) - 1));
    float m = v - c;

    float r_prime, g_prime, b_prime;

    if (0 <= next_h && next_h < 60)
    {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    }
    else if (60 <= next_h && next_h < 120)
    {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    }
    else if (120 <= next_h && next_h < 180)
    {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    }
    else if (180 <= next_h && next_h < 240)
    {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    }
    else if (240 <= next_h && next_h < 300)
    {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    }
    else
    { // 300 <= next_h < 360
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    }

    this->setRed(r_prime + m);
    this->setGreen(g_prime + m);
    this->setBlue(b_prime + m);
};
void ColorEntity::setSaturation(float next_s)
{
    float h = this->getHue();
    float v = this->getValue();

    float c = v * next_s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    float r_prime, g_prime, b_prime;

    if (0 <= h && h < 60)
    {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    }
    else if (60 <= h && h < 120)
    {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    }
    else if (120 <= h && h < 180)
    {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    }
    else if (180 <= h && h < 240)
    {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    }
    else if (240 <= h && h < 300)
    {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    }
    else
    { // 300 <= h < 360
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    }

    this->setRed(r_prime + m);
    this->setGreen(g_prime + m);
    this->setBlue(b_prime + m);
};
void ColorEntity::setValue(float next_v)
{
    float h = this->getHue();
    float s = this->getSaturation();

    float c = next_v * s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = next_v - c;

    float r_prime, g_prime, b_prime;

    if (0 <= h && h < 60)
    {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    }
    else if (60 <= h && h < 120)
    {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    }
    else if (120 <= h && h < 180)
    {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    }
    else if (180 <= h && h < 240)
    {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    }
    else if (240 <= h && h < 300)
    {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    }
    else
    { // 300 <= h < 360
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    }

    this->setRed(r_prime + m);
    this->setGreen(g_prime + m);
    this->setBlue(b_prime + m);
};