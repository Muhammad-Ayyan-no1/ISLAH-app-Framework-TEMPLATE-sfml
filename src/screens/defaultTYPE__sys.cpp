#pragma once

#include "common/main.h"
#include "components.h"

class defaultScreenTYPE__sys
{
public:
    std::shared_ptr<std::vector<std::shared_ptr<sf::Drawable>>> state;

    defaultScreenTYPE__sys()
    {
    }
    // void init()
    // {
    // }
    void init();

    bool rendering = 0;
};