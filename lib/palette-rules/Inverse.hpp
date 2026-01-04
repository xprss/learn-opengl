#pragma once
#include "ColorPaletteRule.hpp"
#include <iostream>

class Inverse : public ColorPaletteRule {
    void react(
        std::array<ColorEntity, Config::COLOR_PALETTE_SIZE> &color_palette,
        ColorEntity *current_color_palette_entity) override
    {
        for (size_t i = 0; i < color_palette.size(); ++i)
        {
            if (&color_palette[i] != current_color_palette_entity)
            {
                color_palette[i].setHue(fmod(current_color_palette_entity->getHue() + (180.0f), 360.0f));
            }
        }
    }
};