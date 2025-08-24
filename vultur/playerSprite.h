#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class playerSprite
{
public:
	sf::Vector2f playerSpritePosition;

	playerSprite(sf::Vector2u winSize)
	{
		playerSpritePosition = sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f);
	};

	// calculating playerSprite properties
	sf::CircleShape createPlayerSprite()
	{
		sf::CircleShape playerSprite({ 15.f });
		playerSprite.setPosition(playerSpritePosition);
		playerSprite.setOrigin({ 15.f, 15.f });

		return playerSprite;
	}
};

#endif

