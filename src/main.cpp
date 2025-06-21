#include "SCREENS_SETUP.hpp"

int main()
{
    sf::Font defaultFont;
    if (!defaultFont.loadFromFile("include/arial/arial.ttf"))
    {
        return -1;
    }
    else
    {
        LOG_custom("PROCESS", "Loaded default font");
    }
    std::vector<std::unique_ptr<defaultScreenTYPE__sys>> renderingScreens;
    setupRenderingScreens(renderingScreens);

    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "ISLAH Framework");
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
