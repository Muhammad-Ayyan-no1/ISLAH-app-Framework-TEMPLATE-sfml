#include "SCREENS_SETUP.hpp"

void handleScreenDraw(
    const std::vector<std::unique_ptr<defaultScreenTYPE__sys>> &renderingScreens,
    sf::RenderWindow &window)
{
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
}
void handleScreenInit(
    std::vector<std::unique_ptr<defaultScreenTYPE__sys>> &renderingScreens)
{
    for (auto &screen : renderingScreens)
    {
        if (screen->getInit)
        {
            screen->init();
        }
    }
}
void handleScreenEvents(
    const std::vector<std::unique_ptr<defaultScreenTYPE__sys>> &renderingScreens,
    const sf::Event &event)
{
    for (const auto &screen : renderingScreens)
    {
        if (screen->getEvents)
        {
            screen->handleEvent(event);
        }
    }
}
int main()
{
    std::vector<std::unique_ptr<defaultScreenTYPE__sys>> renderingScreens;
    setupRenderingScreens(renderingScreens);

    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "ISLAH Framework");
    window.setFramerateLimit(144);
    loadDefaults();
    handleScreenInit(renderingScreens);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            handleScreenEvents(renderingScreens, event);
        }

        window.clear();
        handleScreenDraw(renderingScreens, window);
        window.display();
    }

    return 0;
}
