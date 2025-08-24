#ifndef BEAM_H
#define BEAM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class beam
{
public:
	sf::Vector2f beamPosition;

	beam(sf::Vector2u winSize)
	{
		beamPosition = sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f);
	}

	// calculating beam properties
	sf::RectangleShape createBeam(sf::Vector2i mousePos)
	{
		int mousePosX = mousePos.x - beamPosition.x;
		int mousePosY = mousePos.y - beamPosition.y;
		float beamLength = sqrt((mousePosX * mousePosX) + (mousePosY * mousePosY));
		float beamAngle = atan2(mousePosY, mousePosX) * (180 / 3.1415);
		sf::Vector2f beamPosition = this->beamPosition;

		sf::RectangleShape beam({ beamLength, 5.f });
		beam.setPosition(beamPosition);
		beam.setOrigin({ 0.f, 2.5f });
		beam.setRotation(sf::degrees(beamAngle));

		return beam;
	}
};

#endif

