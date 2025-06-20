#include "animation.hpp"

class button
{
private:
    Animatable bg;
    Animatable text;

public:
    button(sf::String text, auto size, auto txtColor = sf::Color::Black, sf::Font font, auto c = sf::Color::Yellow, auto position = {0, 0}, auto scale = {100, 100}, auto rotation = 360)
    {
        bg = createRectangle(scale.x, scale.y, c);
        bg.shape.setPosition(position);
        // bg.shape.setScale(scale);
        bg.shape.setRotation(rotation);
        text = createText(text, font, size, txtColor)
    }
};
