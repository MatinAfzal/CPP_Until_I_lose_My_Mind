// main.cpp : Defines the entry point for the application.
//

#include "main.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAME_RATE 60

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML 2.6 / Boucing Ball");
	sf::Event event;
	sf::CircleShape ball(sf::CircleShape::CircleShape(50, 50));
	float ballX = WINDOW_WIDTH / 2, ballY = 10;
	bool lock = true;
	sf::Color color(0, 255, 255);
	ball.setPosition(sf::Vector2f(ballX, ballY));
	window.setFramerateLimit(FRAME_RATE);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		ball.setFillColor(color);

		if (!(ball.getPosition().y >= WINDOW_HEIGHT - 107) && lock) {
			ball.setPosition(ballX, (float)(ballY += 9.8));
			color.r += 1;
			color.g += 1;
		}
		else if (!(ball.getPosition().y <= 7)) {
			lock = false;
			ball.setPosition(ballX, (float)(ballY -= 9.8));
			color.r += 1;
			color.g += 1;
		}
		else {
			lock = true;
		}

		window.draw(ball);
		window.display();
	}

	return 0;
}