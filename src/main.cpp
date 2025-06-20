#include "animation.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation System");
    sf::Clock clock;

    // Create a triangle
    Animatable triangle;
    triangle.shape.setPointCount(3);
    triangle.shape.setPoint(0, sf::Vector2f(0, 0));
    triangle.shape.setPoint(1, sf::Vector2f(100, 0));
    triangle.shape.setPoint(2, sf::Vector2f(50, 100));
    triangle.shape.setFillColor(sf::Color::Red);

    // Animation for triangle (movement and morphing)
    Animation triAnim;
    triAnim.positionKeyframes.push_back({0, sf::Vector2f(100, 100), false});
    triAnim.positionKeyframes.push_back({2, sf::Vector2f(300, 300), false});
    triAnim.rotationKeyframes.push_back({0, 0, false});
    triAnim.rotationKeyframes.push_back({2, 360, false});
    triAnim.shapeKeyframes.push_back({0, {sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(50, 100)}});
    triAnim.shapeKeyframes.push_back({2, {sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(0, 100)}});
    triAnim.sortKeyframes();
    triangle.animation = triAnim;

    // Create a rectangle
    Animatable rect = createRectangle(80, 50, sf::Color::Blue);

    // Animation for rectangle (relative movement and scaling)
    Animation rectAnim;
    rectAnim.positionKeyframes.push_back({0, sf::Vector2f(0, 0), true});
    rectAnim.positionKeyframes.push_back({2, sf::Vector2f(100, 50), true});
    rectAnim.scaleKeyframes.push_back({0, sf::Vector2f(1, 1), false});
    rectAnim.scaleKeyframes.push_back({2, sf::Vector2f(1.5, 1.5), true});
    rectAnim.sortKeyframes();
    rect.animation = rectAnim;

    // Group the shapes
    Group group;
    group.members.push_back(triangle);
    group.members.push_back(rect);
    Animation groupAnim;
    groupAnim.positionKeyframes.push_back({0, sf::Vector2f(0, 0), false});
    groupAnim.positionKeyframes.push_back({4, sf::Vector2f(200, 0), false});
    groupAnim.sortKeyframes();
    group.animation = groupAnim;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float t = clock.getElapsedTime().asSeconds();
        group.update(t);

        window.clear(sf::Color::Black);
        window.draw(group);
        window.display();
    }

    return 0;
}