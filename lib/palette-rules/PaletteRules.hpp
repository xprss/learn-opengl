#pragma once
#include "ColorPaletteRule.hpp"
#include "ArmonicTriad.hpp"
#include "Inverse.hpp"
#include <array>

namespace Palette
{
    enum class PaletteRuleType
    {
        ARMONIC_TRIAD,
        INVERSE
    };

    constexpr std::array<PaletteRuleType, 2> paletteRuleTypes = {{PaletteRuleType::ARMONIC_TRIAD,
                                                                  PaletteRuleType::INVERSE}};

    inline ColorPaletteRule *createPaletteRule(PaletteRuleType type)
    {
        switch (type)
        {
        case PaletteRuleType::ARMONIC_TRIAD:
            return new ArmonicTriad();
        case PaletteRuleType::INVERSE:
            return new Inverse();
        default:
            throw std::invalid_argument("Unknown PaletteRuleType");
        }
    }

    constexpr std::string_view to_string(PaletteRuleType t)
    {
        switch (t)
        {
        case PaletteRuleType::ARMONIC_TRIAD:
            return "Armonic Triad";
        case PaletteRuleType::INVERSE:
            return "Inverse";
        }
        return "UNKNOWN";
    }
}