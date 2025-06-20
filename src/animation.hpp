#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

// Keyframe structures for different properties
struct PositionKeyFrame
{
    float time;
    sf::Vector2f position;
    bool isRelative;
};

struct RotationKeyFrame
{
    float time;
    float rotation;
    bool isRelative;
};

struct ScaleKeyFrame
{
    float time;
    sf::Vector2f scale;
    bool isRelative;
};

struct ShapeKeyFrame
{
    float time;
    std::vector<sf::Vector2f> points;
};

// Animation class to manage keyframes and interpolation
class Animation
{
public:
    std::vector<PositionKeyFrame> positionKeyframes;
    std::vector<RotationKeyFrame> rotationKeyframes;
    std::vector<ScaleKeyFrame> scaleKeyframes;
    std::vector<ShapeKeyFrame> shapeKeyframes;

    void sortKeyframes()
    {
        std::sort(positionKeyframes.begin(), positionKeyframes.end(), [](const auto &a, const auto &b)
                  { return a.time < b.time; });
        std::sort(rotationKeyframes.begin(), rotationKeyframes.end(), [](const auto &a, const auto &b)
                  { return a.time < b.time; });
        std::sort(scaleKeyframes.begin(), scaleKeyframes.end(), [](const auto &a, const auto &b)
                  { return a.time < b.time; });
        std::sort(shapeKeyframes.begin(), shapeKeyframes.end(), [](const auto &a, const auto &b)
                  { return a.time < b.time; });
    }

    sf::Vector2f getPositionAt(float t, sf::Vector2f current) const
    {
        if (positionKeyframes.empty())
            return current;
        auto it = std::lower_bound(positionKeyframes.begin(), positionKeyframes.end(), t,
                                   [](const auto &kf, float time)
                                   { return kf.time < time; });
        if (it == positionKeyframes.begin())
            return it->isRelative ? current + it->position : it->position;
        if (it == positionKeyframes.end())
        {
            const auto &last = positionKeyframes.back();
            return last.isRelative ? current + last.position : last.position;
        }
        auto next = it;
        auto prev = std::prev(it);
        float alpha = (t - prev->time) / (next->time - prev->time);
        sf::Vector2f p1 = prev->isRelative ? current + prev->position : prev->position;
        sf::Vector2f p2 = next->isRelative ? p1 + next->position : next->position;
        return p1 + alpha * (p2 - p1);
    }

    float getRotationAt(float t, float current) const
    {
        if (rotationKeyframes.empty())
            return current;
        auto it = std::lower_bound(rotationKeyframes.begin(), rotationKeyframes.end(), t,
                                   [](const auto &kf, float time)
                                   { return kf.time < time; });
        if (it == rotationKeyframes.begin())
            return it->isRelative ? current + it->rotation : it->rotation;
        if (it == rotationKeyframes.end())
        {
            const auto &last = rotationKeyframes.back();
            return last.isRelative ? current + last.rotation : last.rotation;
        }
        auto next = it;
        auto prev = std::prev(it);
        float alpha = (t - prev->time) / (next->time - prev->time);
        float r1 = prev->isRelative ? current + prev->rotation : prev->rotation;
        float r2 = next->isRelative ? r1 + next->rotation : next->rotation;
        return r1 + alpha * (r2 - r1);
    }

    sf::Vector2f getScaleAt(float t, sf::Vector2f current) const
    {
        if (scaleKeyframes.empty())
            return current;
        auto it = std::lower_bound(scaleKeyframes.begin(), scaleKeyframes.end(), t,
                                   [](const auto &kf, float time)
                                   { return kf.time < time; });
        if (it == scaleKeyframes.begin())
            return it->isRelative ? sf::Vector2f(current.x * it->scale.x, current.y * it->scale.y) : it->scale;
        if (it == scaleKeyframes.end())
        {
            const auto &last = scaleKeyframes.back();
            return last.isRelative ? sf::Vector2f(current.x * last.scale.x, current.y * last.scale.y) : last.scale;
        }
        auto next = it;
        auto prev = std::prev(it);
        float alpha = (t - prev->time) / (next->time - prev->time);
        sf::Vector2f s1 = prev->isRelative ? sf::Vector2f(current.x * prev->scale.x, current.y * prev->scale.y) : prev->scale;
        sf::Vector2f s2 = next->isRelative ? sf::Vector2f(s1.x * next->scale.x, s1.y * next->scale.y) : next->scale;
        return s1 + alpha * (s2 - s1);
    }

    std::vector<sf::Vector2f> getShapePointsAt(float t) const
    {
        if (shapeKeyframes.empty())
            return {};
        auto it = std::lower_bound(shapeKeyframes.begin(), shapeKeyframes.end(), t,
                                   [](const auto &kf, float time)
                                   { return kf.time < time; });
        if (it == shapeKeyframes.begin())
            return it->points;
        if (it == shapeKeyframes.end())
            return shapeKeyframes.back().points;
        auto next = it;
        auto prev = std::prev(it);
        float alpha = (t - prev->time) / (next->time - prev->time);
        const auto &p1 = prev->points;
        const auto &p2 = next->points;
        std::vector<sf::Vector2f> points;
        for (size_t i = 0; i < p1.size(); ++i)
        {
            points.push_back(p1[i] + alpha * (p2[i] - p1[i]));
        }
        return points;
    }
};

// Animatable class for individual shapes
class Animatable : public sf::Drawable, public sf::Transformable
{
public:
    sf::ConvexShape shape;
    Animation animation;

    void update(float t)
    {
        shape.setPosition(getPositionAt(t));
        shape.setRotation(getRotationAt(t));
        shape.setScale(getScaleAt(t));
        if (!animation.shapeKeyframes.empty())
        {
            auto points = animation.getShapePointsAt(t);
            shape.setPointCount(points.size());
            for (size_t i = 0; i < points.size(); ++i)
            {
                shape.setPoint(i, points[i]);
            }
        }
    }

    sf::Vector2f getPositionAt(float t) { return animation.getPositionAt(t, getPosition()); }
    float getRotationAt(float t) { return animation.getRotationAt(t, getRotation()); }
    sf::Vector2f getScaleAt(float t) { return animation.getScaleAt(t, getScale()); }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(shape, states);
    }
};
class TextAnimatable : public sf::Drawable, public sf::Transformable
{
public:
    sf::Text text;
    Animation animation;

    void update(float t)
    {
        text.setPosition(animation.getPositionAt(t, getPosition()));
        text.setRotation(animation.getRotationAt(t, getRotation()));
        text.setScale(animation.getScaleAt(t, getScale()));
    }

    sf::Vector2f getPositionAt(float t) { return animation.getPositionAt(t, getPosition()); }
    float getRotationAt(float t) { return animation.getRotationAt(t, getRotation()); }
    sf::Vector2f getScaleAt(float t) { return animation.getScaleAt(t, getScale()); }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(text, states);
    }
};

// Group class for grouping shapes
class Group : public sf::Drawable, public sf::Transformable
{
public:
    std::vector<Animatable> members;
    Animation animation;

    void update(float t)
    {
        setPosition(animation.getPositionAt(t, getPosition()));
        setRotation(animation.getRotationAt(t, getRotation()));
        setScale(animation.getScaleAt(t, getScale()));
        for (auto &member : members)
        {
            member.update(t);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        for (const auto &member : members)
        {
            target.draw(member, states);
        }
    }
};

// Helper function to create a rectangle
Animatable createRectangle(float width, float height, sf::Color color)
{
    Animatable rect;
    rect.shape.setPointCount(4);
    rect.shape.setPoint(0, sf::Vector2f(0, 0));
    rect.shape.setPoint(1, sf::Vector2f(width, 0));
    rect.shape.setPoint(2, sf::Vector2f(width, height));
    rect.shape.setPoint(3, sf::Vector2f(0, height));
    rect.shape.setFillColor(color);
    return rect;
}
TextAnimatable createText(const sf::String &content, const sf::Font &font, unsigned int size, sf::Color color)
{
    TextAnimatable txt;
    txt.text.setFont(font);
    txt.text.setString(content);
    txt.text.setCharacterSize(size);
    txt.text.setFillColor(color);
    return txt;
}
