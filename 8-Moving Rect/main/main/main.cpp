// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 2.6 / Moving Rect");
	sf::RectangleShape rectAngle(sf::Vector2f(80, 80));
	double rectLocX = 0, rectLocY = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::W)
					rectLocY -= 1.8;
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::S)
					rectLocY += 1.8;
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::A)
					rectLocX -= 1.8;
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::D)
					rectLocX += 1.8;
		}

		window.clear(sf::Color::Black);
		rectAngle.setPosition(sf::Vector2f((float)rectLocX, (float)rectLocY));
		window.draw(rectAngle);
		window.display();
	}
	return 0;
}