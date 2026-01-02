#pragma once

class ColorPaletteRule
{
public:
    // React to a change in the color palette
    virtual void react(
        std::array<ColorEntity, Config::COLOR_PALETTE_SIZE>& color_palette, 
        ColorEntity *current_color_palette_entity) = 0;

    virtual ~ColorPaletteRule() {}
};
