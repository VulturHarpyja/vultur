#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include "beam.h"
#include "playerSprite.h"

// function defining text properties
sf::Text text(sf::Vector2f pos, sf::Font* font)
{
	sf::Text standardText(*font);
	standardText.setPosition(pos);
	standardText.setCharacterSize(24);
	standardText.setFillColor(sf::Color::Red);
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
	sf::Text mousePosTracker = text({ 0.f, 0.f }, &roboto);
	sf::Text beamAngleTracker = text({ 0.f, 24.f }, &roboto);
	sf::Text fpsTracker = text({ 0.f, 48.f }, &roboto);
	sf::Text resolutionTracker = text({ 0.f, 72.f }, &roboto);

	// constructing
	beam centreBeam(window.getSize());
	playerSprite playerCircle;

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
			float beamAngle = atan2(mousePosY, mousePosX) * (180 / 3.1415);

			mousePosTracker.setString("Mouse posX: " + std::to_string(mousePosX) + " Mouse posY: " + std::to_string(mousePosY));
			beamAngleTracker.setString("Line angle: " + std::to_string(beamAngle));
			resolutionTracker.setString("Current Res.: " + std::to_string(winSize.x) + "x" + std::to_string(winSize.y));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			playerCircle.move({ 0.f, -5.f });
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			playerCircle.move({ -5.f, 0.f });
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			playerCircle.move({ 0.f, 5.f });
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			playerCircle.move({ 5.f, 0.f });
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

		//window.draw(centreBeam.createBeam(sf::Mouse::getPosition(window)));
		window.draw(centreBeam.createBeam(playerCircle.getPosition()));
		window.draw(playerCircle.createPlayerSprite());
		window.draw(mousePosTracker);
		window.draw(beamAngleTracker);
		window.draw(fpsTracker);
		window.draw(resolutionTracker);

		window.display();
	}
}