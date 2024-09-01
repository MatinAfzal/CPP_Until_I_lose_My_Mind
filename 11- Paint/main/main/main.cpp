// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML 2.6 / Paint " + to_string(FRAME_RATE));
	sf::Event event;
	int shapeA = 5, shapeB = 5;
	bool drawMode = false;
	list<sf::CircleShape> points;
	window.setFramerateLimit(FRAME_RATE);

	cout << "Press [C] to clear." << endl;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					drawMode = true;
			if (event.type == sf::Event::MouseButtonReleased)
				if (event.mouseButton.button == sf::Mouse::Left)
					drawMode = false;
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::C)
					points.clear();
		}

		window.clear(sf::Color::Black);

		if (drawMode) {
			sf::CircleShape circle(sf::CircleShape(shapeA, shapeB));
			circle.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x - shapeA,
				(float)sf::Mouse::getPosition(window).y - shapeB));
			points.push_front(circle);
		}

		for (sf::CircleShape point: points)
			window.draw(point);

		window.display();
	}
	return 0;
}
