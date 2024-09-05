#include "snake.h"

Snake::Snake(sf::Vector2f bodySize, sf::Vector2f headPos, sf::Vector2f speed) {
	loadTextures();
	bodySizeA = bodySize.x;
	bodySizeB = bodySize.y;
	headPosX = headPos.x;
	headPosY = headPos.y;
	speedX = speed.x;
	speedY = speed.y;

	head.setSize(bodySize);
	head.setPosition(headPos);
	head.setTexture(psnakeHeadRTexture);
	snake.push_front(head);

	// inital body.
	addBody();
	addBody();
	addBody();
}

void Snake::loadTextures(void) {
	if (!snakeHeadRTexture.loadFromFile(SNAKE_HEAD_R_TEXTURE_PATH))
		std::cerr << "Can't open texture file at " << SNAKE_HEAD_R_TEXTURE_PATH;
	snakeHeadRTexture.setSmooth(true);

	if (!snakeHeadDTexture.loadFromFile(SNAKE_HEAD_D_TEXTURE_PATH))
		std::cerr << "Can't open texture file at " << SNAKE_HEAD_D_TEXTURE_PATH;
	snakeHeadDTexture.setSmooth(true);

	if (!snakeHeadLTexture.loadFromFile(SNAKE_HEAD_L_TEXTURE_PATH))
		std::cerr << "Can't open texture file at " << SNAKE_HEAD_L_TEXTURE_PATH;
	snakeHeadLTexture.setSmooth(true);

	if (!snakeHeadUTexture.loadFromFile(SNAKE_HEAD_U_TEXTURE_PATH))
		std::cerr << "Can't open texture file at " << SNAKE_HEAD_U_TEXTURE_PATH;
	snakeHeadDTexture.setSmooth(true);

	if (!snakeBodyTexture.loadFromFile(SNAKE_BODY_TEXTURE_PATH))
		std::cerr << "Can't open texture file at " << SNAKE_BODY_TEXTURE_PATH;
	snakeBodyTexture.setSmooth(true);
}

void Snake::translate(char direction) {
	std::list<sf::RectangleShape>::iterator it = snake.begin();
	std::advance(it, 0); // grab head coordinates.
	sf::Vector2f currentPos = it->getPosition();
	bool firstPassed = false; // lazy way to create range-based-for-loop.

	if (direction == 'W') {
		it->setPosition(sf::Vector2f(it->getPosition().x, it->getPosition().y - speedY));
		it->setTexture(psnakeHeadUTexture);
	}
	if (direction == 'A') {
		it->setPosition(sf::Vector2f(it->getPosition().x - speedX, it->getPosition().y));
		it->setTexture(psnakeHeadLTexture);
	}
	if (direction == 'S') {
		it->setPosition(sf::Vector2f(it->getPosition().x, it->getPosition().y + speedY));
		it->setTexture(psnakeHeadDTexture);
	}
	if (direction == 'D') {
		it->setPosition(sf::Vector2f(it->getPosition().x + speedX, it->getPosition().y));
		it->setTexture(psnakeHeadRTexture);
	}

	for (sf::RectangleShape& body : snake) {
		if (!firstPassed) {
			firstPassed = true;
			continue;
		}
		sf::Vector2f temp = body.getPosition();
		body.setPosition(currentPos);
		currentPos = temp;
	}
}

void Snake::instantTranslate() {
	head.setPosition(sf::Vector2f(headPosX, headPosY));
}

void Snake::addBody() {
	sf::RectangleShape newBody;
	newBody.setSize(sf::Vector2f(bodySizeA, bodySizeB));
	std::list<sf::RectangleShape>::iterator it = snake.begin();
	std::advance(it, snake.size() - 1);
	sf::Vector2f tailPos = it->getPosition();
	newBody.setPosition(sf::Vector2f(tailPos.x - bodySizeA, tailPos.y));
	newBody.setTexture(psnakeBodyTexture);
	snake.push_back(newBody);
}