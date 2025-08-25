#ifndef BEAM_H
#define BEAM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "playerSprite.h"

class beam
{
public:

    // calculating beam properties
    //sf::RectangleShape createBeam(sf::Vector2i mousePos, sf::Vector2u winSize)
    sf::RectangleShape createBeam(sf::Vector2f circlePos, sf::Vector2u winSize)
    {
        // beam always starts from window center
        sf::Vector2f beamPosition(winSize.x / 2.f, winSize.y / 2.f);

        // mouse version
        //int mousePosX = mousePos.x - beamPosition.x;
        //int mousePosY = mousePos.y - beamPosition.y;		
        //float beamLength = hypot(mousePosX mousePosY);
        //float beamAngle = atan2(mousePosY, mousePosX) * (180 / 3.1415);

        // circle version
        int circlePosX = circlePos.x - beamPosition.x;
        int circlePosY = circlePos.y - beamPosition.y;
        float beamLength = hypot(circlePosX, circlePosY);
        float beamAngle = atan2(circlePosY, circlePosX) * (180 / 3.1415);

        // rectangle beam
        sf::RectangleShape beam({ beamLength, 5.f });
        beam.setPosition(beamPosition);
        beam.setOrigin({ 0.f, 2.5f });
        beam.setRotation(sf::degrees(beamAngle));

        return beam;
    }
};

#endif
