#pragma once

#include <SFML/Graphics.hpp>

class Brick {
public:
	bool live = true;
	float brickWidth = 64;
	float brickHeight = 64;
	float brickPosX = 0;
	float brickPosY = 0;
	sf::RectangleShape brick;
	sf::Texture brickTexture;
	Brick(sf::Vector2f, const sf::Texture*);
	void liveSwap(void);
};