#include "common/main.h"

class COMP_button
{
private:
    sf::Vector2f textMarginStore;
    sf::Vector2f originalScale;

    std::function<void(sf::Event)> onClick;
    std::function<void(sf::Event)> onHover;
    std::function<void(sf::Event)> onFocus;
    std::function<void(sf::Event)> onClickEnd;
    std::function<void(sf::Event)> onClickStart;
    std::function<void(sf::Event)> onHoverStart;
    std::function<void(sf::Event)> onHoverEnd;
    std::function<void(sf::Event)> onFocusStart;
    std::function<void(sf::Event)> onFocusEnd;

    bool isHovered = false;
    bool isClicked = false;
    bool isFocused = false;

    sf::Window *windowOpt;

    void adjustText(sf::Vector2f textMargin)
    {
        text.setPosition(background.getPosition() + textMargin);
    }

public:
    sf::RectangleShape background;
    sf::Text text;

    COMP_button(const sf::String &textStr, sf::Vector2f position, sf::Vector2f scale, float rotation,
                sf::Vector2f textMargin, unsigned int textSize,
                sf::Color bgColor, sf::Color textColor, const sf::Font &font, sf::Window *window,
                std::function<void(sf::Event)> onClick,
                std::function<void(sf::Event)> onHover,
                std::function<void(sf::Event)> onFocus,
                std::function<void(sf::Event)> onClickEnd,
                std::function<void(sf::Event)> onClickStart,
                std::function<void(sf::Event)> onHoverStart,
                std::function<void(sf::Event)> onHoverEnd,
                std::function<void(sf::Event)> onFocusStart,
                std::function<void(sf::Event)> onFocusEnd)
        : onClick(onClick), onHover(onHover), onFocus(onFocus),
          onClickEnd(onClickEnd), onClickStart(onClickStart),
          onHoverStart(onHoverStart), onHoverEnd(onHoverEnd),
          onFocusStart(onFocusStart), onFocusEnd(onFocusEnd)
    {
        textMarginStore = textMargin;
        originalScale = scale;

        setPosition(position);
        background.setScale(scale);
        setRotation(rotation);
        background.setFillColor(bgColor);
        text.setFillColor(textColor);
        text.setCharacterSize(textSize);
        text.setFont(font);
        text.setString(textStr);
        windowOpt = window;
    }

    void setPosition(sf::Vector2f position)
    {
        background.setPosition(position);
        adjustText(textMarginStore);
    }

    void setRotation(float r)
    {
        background.setRotation(r);
        text.setRotation(r);
    }

    void setScale(sf::Vector2f scale)
    {
        background.setScale(scale);
        originalScale = scale;
        // unsigned int newSize = static_cast<unsigned int>((scale.x + scale.y) * 10);
        unsigned int newSize = static_cast<unsigned int>(text.getCharacterSize() * ((scale.x + scale.y) / 2));

        text.setCharacterSize(newSize);
    }

    void setTextMargin(sf::Vector2f newMargins)
    {
        textMarginStore = newMargins;
        adjustText(newMargins);
    }

    // std::tuple<sf::RectangleShape, sf::Text> getDrawComps()
    std::tuple<sf::RectangleShape &, sf::Text &> getDrawComps()
    {
        return {background, text};
    }
    void draw(sf::RenderTarget &target) const
    {
        target.draw(background);
        target.draw(text);
    }

    void onevent(sf::Event event)
    {
        sf::Vector2f pointerPosition;

        // Handle both mouse and touch inputs
        if (event.type == sf::Event::MouseMoved ||
            event.type == sf::Event::MouseButtonPressed ||
            event.type == sf::Event::MouseButtonReleased)
        {
            if (windowOpt)
            {
                pointerPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*windowOpt));
            }
            else
            {
                LOG_custom("WARNING", "Using fallback screen cursor position instead of window");
                pointerPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
            }
        }
        else if (event.type == sf::Event::TouchBegan ||
                 event.type == sf::Event::TouchMoved ||
                 event.type == sf::Event::TouchEnded)
        {
            pointerPosition = sf::Vector2f(event.touch.x, event.touch.y);
        }

        // Hover / Touch Move detection
        if (event.type == sf::Event::MouseMoved || event.type == sf::Event::TouchMoved)
        {
            sf::FloatRect bounds = background.getGlobalBounds();
            bool nowHovered = bounds.contains(pointerPosition);

            if (nowHovered && !isHovered)
            {
                isHovered = true;
                if (onHoverStart)
                    onHoverStart(event);
            }
            else if (!nowHovered && isHovered)
            {
                isHovered = false;
                if (onHoverEnd)
                    onHoverEnd(event);
            }

            if (isHovered && onHover)
            {
                onHover(event);
            }
        }

        // Click / Touch Begin
        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) ||
            event.type == sf::Event::TouchBegan)
        {
            if (background.getGlobalBounds().contains(pointerPosition))
            {
                isClicked = true;
                if (onClickStart)
                    onClickStart(event);
            }
        }

        // Click Release
        if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) ||
            event.type == sf::Event::TouchEnded)
        {
            if (isClicked && background.getGlobalBounds().contains(pointerPosition))
            {
                if (onClick)
                    onClick(event);
            }
            if (onClickEnd)
                onClickEnd(event);
            isClicked = false;
        }

        // Focus handling (may not apply on mobile)
        if (event.type == sf::Event::GainedFocus)
        {
            isFocused = true;
            if (onFocusStart)
                onFocusStart(event);
        }
        else if (event.type == sf::Event::LostFocus)
        {
            isFocused = false;
            if (onFocusEnd)
                onFocusEnd(event);
        }
        else if (isFocused && onFocus)
        {
            onFocus(event);
        }
    }
};
