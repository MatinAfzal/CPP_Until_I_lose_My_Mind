#include "bricks.h"

Brick::Brick(sf::Vector2f position, const sf::Texture* texture) {
	brickPosX = position.x;
	brickPosY = position.y;
	brickTexture.setSmooth(true);
	brick.setSize(sf::Vector2f(brickWidth, brickHeight));
	brick.setPosition(sf::Vector2f(brickPosX, brickPosY));
	brick.setTexture(texture, true);
}

void Brick::liveSwap(void) {
	live = false;
}