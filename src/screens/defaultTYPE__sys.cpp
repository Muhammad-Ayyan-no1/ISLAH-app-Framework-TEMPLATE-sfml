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

    // so bad , I dont wana use vtables but for sake of api
    virtual void init() {};
    virtual void handleEvent(const sf::Event &event) {};

    bool rendering = 0;
    bool getInit = 0;
    bool getEvents = 0;
};