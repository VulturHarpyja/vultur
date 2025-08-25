#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class playerSprite
{
public:
    playerSprite()
    {
        circle.setRadius(15.f);
        circle.setOrigin({ 15.f, 15.f }); // center origin
        circle.setFillColor(sf::Color::Green);
        circle.setPosition({ 600.f, 600.f }); // initial position
    }

    // movement
    void move(const sf::Vector2f& offset)
    {
        circle.move(offset);
    }

    // custom set position
    void setPosition(const sf::Vector2f& pos)
    {
        circle.setPosition(pos);
    }

    // custom get position
    sf::Vector2f getPosition() const
    {
        return circle.getPosition();
    }

    // custom get global bounds
    sf::FloatRect getGlobalBounds() const
    {
        return circle.getGlobalBounds();
    }


    // returns circle when called in main
    const sf::CircleShape& createPlayerSprite() const
    {
        return circle;
    }

private:
    sf::CircleShape circle;
};

#endif
