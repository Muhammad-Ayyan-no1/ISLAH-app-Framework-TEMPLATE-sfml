#include "common/main.h"
#include "components.h"
#include "screenImports.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

int main()
{
    std::vector<std::unique_ptr<defaultScreenTYPE__sys>> renderingScreens;
    renderingScreens.reserve(10); // should be enough
    renderingScreens.push_back(std::make_unique<RedScreen>());

    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "SFML Window");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        for (const auto &screen : renderingScreens)
        {
            if (screen->rendering)
            {
                for (const auto &drawable : *screen->state)
                {
                    window.draw(*drawable);
                }
            }
        }

        window.display();
    }

    return 0;
}
