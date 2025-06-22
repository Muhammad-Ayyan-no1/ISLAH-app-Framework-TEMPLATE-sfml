#pragma once
#include "SCREENS_SETUP.hpp" // just because vscode is complaining

sf::Font defaultFont;

void loadDefaults()
{
    if (!defaultFont.loadFromFile("include/arial/arial.ttf"))
    {
        LOG_custom("DEFAULT-Error", "Default font not loaded");
    }
    else
    {
        LOG_custom("PROCESS", "Loaded default font");
    }
}