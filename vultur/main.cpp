#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
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

int main()
{
	// getting font
	sf::Font roboto;
	if (!roboto.openFromFile(".\\assets\\fonts\\static\\RobotoMono-Regular.ttf"))
	{
		std::cerr << ".Error while loading font" << std::endl;
		return -1;
	}

	// window constructed
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 1200 }), "Window");

	// mouse pos tracker
	sf::Text mousePosTracker(roboto);
	mousePosTracker.setPosition({ 0.f, 0.f });
	mousePosTracker.setFont(roboto);
	mousePosTracker.setCharacterSize(24);
	mousePosTracker.setFillColor(sf::Color::Red);

	// beam angle tracker
	sf::Text beamAngleTracker(roboto);
	beamAngleTracker.setPosition({ 0.f, 24.f });
	beamAngleTracker.setFont(roboto);
	beamAngleTracker.setCharacterSize(24);
	beamAngleTracker.setFillColor(sf::Color::Red);

	// fps tracker
	sf::Clock clock;
	float fps = 0.f;
	sf::Text fpsTracker(roboto);
	fpsTracker.setPosition({ 0.f, 48.f });
	fpsTracker.setFont(roboto);
	fpsTracker.setCharacterSize(24);
	fpsTracker.setFillColor(sf::Color::Red);

	// resolution tracker
	sf::Text resolutionTracker(roboto);
	resolutionTracker.setPosition({ 0.f, 72.f });
	resolutionTracker.setFont(roboto);
	resolutionTracker.setCharacterSize(24);
	resolutionTracker.setFillColor(sf::Color::Red);

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
		// beam constructed
		beam centreBeam(window.getSize());

		// graphics settings
		window.setVerticalSyncEnabled(true);
		sf::ContextSettings settings;
		settings.antiAliasingLevel = 8;
		fpsTracker.setString("FPS: " + std::to_string(static_cast<int>(fps)));

		// fps
		float deltaTime = clock.restart().asSeconds();
		fps = 1.f / deltaTime;

		// render
		window.clear(sf::Color::Black);
		window.draw(centreBeam.createBeam(sf::Mouse::getPosition(window)));
		window.draw(mousePosTracker);
		window.draw(beamAngleTracker);
		window.draw(fpsTracker);
		window.draw(resolutionTracker);
		window.display();
	}
}