#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "common/main.h"

class RedScreen : public defaultScreenTYPE__sys
{
public:
    RedScreen()
    {
        state = std::make_shared<std::vector<std::shared_ptr<sf::Drawable>>>();
        auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(400, 300));
        rect->setFillColor(sf::Color::Red);
        rect->setPosition(100, 100);
        state->push_back(rect);
        rendering = true;
    }
};