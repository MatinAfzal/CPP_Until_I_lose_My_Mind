// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

void updateDVD(void);
void colorUpdate(void);

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML 2.6 / DVD Bouncer");
sf::Event event;
sf::Texture texture;
sf::Sprite dvd;
int speedX = 1.5, speedY = 1.5;
int R = 100, G = 150, B = 170;

int main()
{
	window.setFramerateLimit(120);

	if (!texture.loadFromFile(DVD_PATH)) {
		cerr << "DVD Image not found!" << endl;
		return -1;
	}

	dvd.setTexture(texture);
	dvd.setScale(sf::Vector2f(0.2, 0.2));

	while (window.isOpen()) {
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::Black);
		updateDVD();
		window.display();
	}

	return 0;
}

//*****************************************************************************
void updateDVD(void) {
	float dvdX = dvd.getPosition().x;
	float dvdY = dvd.getPosition().y;
	sf::Color color(R, G, B);

	dvdX += speedX;
	dvdY += speedY;

	float dvdRealPosX = dvd.getLocalBounds().getSize().x * 0.2;
	float dvdRealPosY = dvd.getLocalBounds().getSize().y * 0.2;

	if (dvdX + dvdRealPosX >= SCREEN_WIDTH || dvdX + dvdRealPosX <= dvdRealPosX) {
		speedX *= -1;
		colorUpdate();
	}
	if (dvdY + dvdRealPosY >= SCREEN_HEIGHT || dvdY + dvdRealPosY <= dvdRealPosY) {
		speedY *= -1;
		colorUpdate();
	}

	dvd.setPosition(sf::Vector2f(dvdX, dvdY));
	dvd.setColor(color);
	window.draw(dvd);
}

void colorUpdate(void) {
	R = rand() / 150;
	G = rand() / 150;
	B = rand() / 150;
}