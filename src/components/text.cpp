#include "common/main.h"
class COMP_text
{
private:
    std::function<void(sf::Event)> onClick;
    std::function<void(sf::Event)> onHover;
    std::function<void(sf::Event)> onClickStart;
    std::function<void(sf::Event)> onClickEnd;
    std::function<void(sf::Event)> onHoverStart;
    std::function<void(sf::Event)> onHoverEnd;

    bool isHovered = false;
    bool isClicked = false;
    sf::Window *windowOpt = nullptr;

public:
    sf::Text text;
    std::size_t maxLineLength = 0;

    COMP_text(
        const sf::String &text_str, const sf::Font &font, sf::Color color, sf::Window *window = nullptr,
        std::function<void(sf::Event)> onClick = nullptr,
        std::function<void(sf::Event)> onHover = nullptr,
        std::function<void(sf::Event)> onClickStart = nullptr,
        std::function<void(sf::Event)> onClickEnd = nullptr,
        std::function<void(sf::Event)> onHoverStart = nullptr,
        std::function<void(sf::Event)> onHoverEnd = nullptr)
        : onClick(onClick), onHover(onHover),
          onClickStart(onClickStart), onClickEnd(onClickEnd),
          onHoverStart(onHoverStart), onHoverEnd(onHoverEnd),
          windowOpt(window)
    {
        text.setFont(font);
        text.setString(text_str);
        text.setFillColor(color);
    }

    void draw(sf::RenderTarget &target) const
    {
        target.draw(text);
    }

    std::tuple<sf::Text &> getDrawComps()
    {
        return {text};
    }

    void autoLineBreak()
    {
        if (maxLineLength == 0)
            return;

        sf::String str = text.getString();
        sf::String newStr;
        std::size_t lineLength = 0;
        std::size_t lastSpace = sf::String::InvalidPos;

        for (std::size_t i = 0; i < str.getSize(); ++i)
        {
            sf::Uint32 c = str[i];
            newStr += c;

            if (c == ' ')
            {
                lastSpace = newStr.getSize() - 1;
            }

            if (c == '\n')
            {
                lineLength = 0;
                lastSpace = sf::String::InvalidPos;
            }
            else
            {
                lineLength++;
            }

            if (lineLength >= maxLineLength)
            {
                if (lastSpace != sf::String::InvalidPos)
                {
                    newStr[lastSpace] = '\n';
                    lineLength = newStr.getSize() - lastSpace - 1;
                    lastSpace = sf::String::InvalidPos;
                }
                else
                {
                    newStr += '\n';
                    lineLength = 0;
                }
            }
        }

        text.setString(newStr);
    }

    void onevent(sf::Event event)
    {
        sf::Vector2f pointerPosition;

        if (event.type == sf::Event::MouseMoved ||
            event.type == sf::Event::MouseButtonPressed ||
            event.type == sf::Event::MouseButtonReleased)
        {
            // pointerPosition = windowOpt ? static_cast<sf::Vector2f>(sf::Mouse::getPosition(*windowOpt))
            // : static_cast<sf::Vector2f>(sf::Mouse::getPosition());
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

        // Hover detection
        if (event.type == sf::Event::MouseMoved || event.type == sf::Event::TouchMoved)
        {
            sf::FloatRect bounds = text.getGlobalBounds();
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
                onHover(event);
        }

        // Click Begin
        if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) ||
            event.type == sf::Event::TouchBegan)
        {
            if (text.getGlobalBounds().contains(pointerPosition))
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
            if (isClicked && text.getGlobalBounds().contains(pointerPosition))
            {
                if (onClick)
                    onClick(event);
            }

            if (onClickEnd)
                onClickEnd(event);

            isClicked = false;
        }
    }
};
