#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include "beam.h"
#include "playerSprite.h"

float textPositionY = 0;

// function defining text properties
sf::Text text(sf::Font* font, bool green)
{
	sf::Vector2f textPosition = { 0.f, (textPositionY) };
	textPositionY += 24;
	sf::Text standardText(*font);
	standardText.setPosition(textPosition);
	standardText.setCharacterSize(24);
	//standardText.setFillColor(sf::Color::Red);
	if (green) 
	{
		standardText.setFillColor(sf::Color::Green);
	}
	else 
	{
		standardText.setFillColor(sf::Color::Red);
	}
	return standardText;
}

int main()
{
	// getting font
	sf::Font roboto;
	roboto.openFromFile(".\\assets\\fonts\\static\\RobotoMono-Regular.ttf");

	// window constructed
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 1200 }), "Window");

	// fps
	sf::Clock clock;
	float fps = 0.f;

	// trackers
	sf::Text mousePosTracker = text(&roboto, false);
	sf::Text circlePosTracker = text(&roboto, false);
	sf::Text beamAngleTracker = text(&roboto, false);
	sf::Text fpsTracker = text(&roboto, false);
	sf::Text resolutionTracker = text(&roboto, false);
	sf::Text beamLenTracker = text(&roboto, false);
	sf::Text isGrabbedTracker = text(&roboto, false);

	// constructing objects
	beam centreBeam(window.getSize());
	playerSprite playerCircle;

	bool isGrabbed = false;

	// main game loop
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			// window close
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			// window resize
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
				window.setView(sf::View(visibleArea));
			}

			// values calculated for trackers
			sf::Vector2u winSize = window.getSize();
			auto beamPosition = sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f);
			auto mousePos = sf::Mouse::getPosition(window);
			int mousePosX = mousePos.x - winSize.x;
			int mousePosY = mousePos.y - winSize.y;
			auto circlePos = playerCircle.getPosition();
			int circlePosX = circlePos.x - beamPosition.x;
			int circlePosY = circlePos.y - beamPosition.y;
			//float beamAngle = atan2(mousePosY, mousePosX) * (180 / 3.1415);
			//float beamLength = sqrt((mousePosX * mousePosX) + (mousePosY * mousePosY));
			float beamAngle = atan2(circlePosY, circlePosX) * (180 / 3.1415);
			float beamLength = sqrt((circlePosX * circlePosX) + (circlePosY * circlePosY));

			// display texts for trackers
			mousePosTracker.setString("Mouse posX: " + std::to_string(mousePosX) + " Mouse posY: " + std::to_string(mousePosY));
			circlePosTracker.setString("Circle posX: " + std::to_string(circlePosX) + " Circle posY: " + std::to_string(circlePosY));
			beamAngleTracker.setString("Line angle: " + std::to_string(beamAngle));
			resolutionTracker.setString("Current Res.: " + std::to_string(winSize.x) + "x" + std::to_string(winSize.y));
			beamLenTracker.setString("Beam Len./Dist. from centre: " + std::to_string(beamLength));
			if (isGrabbed) {
				isGrabbedTracker.setFillColor(sf::Color::Green);  // grabbed = green
				isGrabbedTracker.setString("isGrabbed: true");
			}
			else {
				isGrabbedTracker.setFillColor(sf::Color::Red);    // not grabbed = red
				isGrabbedTracker.setString("isGrabbed: false");
			}
		}

		// movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			playerCircle.move({ 0.f, -2.5f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			playerCircle.move({ -2.5f, 0.f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			playerCircle.move({ 0.f, 2.5f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			playerCircle.move({ 2.5f, 0.f });
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		// detects if mouse is being held on circle
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && 
			playerCircle.getGlobalBounds().contains(mousePosFloat) && !isGrabbed)
		{
			isGrabbed = true;	
		}
		if (isGrabbed)
		{
			playerCircle.setPosition(mousePosFloat);
		}
		if (!(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		{
			isGrabbed = false;
		}

		// graphics settings
		window.setVerticalSyncEnabled(true);
		sf::ContextSettings settings;
		settings.antiAliasingLevel = 8;
		fpsTracker.setString("FPS: " + std::to_string(static_cast<int>(fps)));

		// fps calculations
		float deltaTime = clock.restart().asSeconds();
		fps = 1.f / deltaTime;

		// render
		window.clear(sf::Color::Black);

		//window.draw(centreBeam.createBeam(sf::Mouse::getPosition(window), window.getSize()));
		//window.draw(centreBeam.createBeam(playerCircle.getPosition(), window.getSize()));
		window.draw(playerCircle.createPlayerSprite());
		window.draw(mousePosTracker);
		window.draw(circlePosTracker);
		window.draw(beamAngleTracker);
		window.draw(fpsTracker);
		window.draw(resolutionTracker);
		window.draw(beamLenTracker);
		window.draw(isGrabbedTracker);

		window.display();
	}
}