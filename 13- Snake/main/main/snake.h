#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#define SNAKE_HEAD_R_TEXTURE_PATH "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/13- Snake/main/assets/snake_green_head_32_r.png"
#define SNAKE_HEAD_D_TEXTURE_PATH "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/13- Snake/main/assets/snake_green_head_32_d.png"
#define SNAKE_HEAD_L_TEXTURE_PATH "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/13- Snake/main/assets/snake_green_head_32_l.png"
#define SNAKE_HEAD_U_TEXTURE_PATH "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/13- Snake/main/assets/snake_green_head_32_u.png"
#define SNAKE_BODY_TEXTURE_PATH "C:/Users/pc/Desktop/Desktop/Projects/CPP_Until_I_lose_My_Mind/13- Snake/main/assets/body.png"

class Snake {
public:
	sf::RectangleShape head;
	std::list<sf::RectangleShape> snake; // drawable
	sf::Texture snakeHeadRTexture, snakeHeadDTexture, snakeHeadLTexture, snakeHeadUTexture, snakeBodyTexture;
	const sf::Texture* psnakeHeadRTexture = &snakeHeadRTexture,
		*psnakeHeadDTexture = &snakeHeadDTexture,
		*psnakeHeadLTexture = &snakeHeadLTexture,
		*psnakeHeadUTexture = &snakeHeadUTexture,
		*psnakeBodyTexture = &snakeBodyTexture;
	float bodySizeA, bodySizeB;
	float headPosX, headPosY;
	float speedX, speedY;

	Snake(sf::Vector2f bodySize = sf::Vector2f(20.0f, 20.0f), sf::Vector2f headPos = sf::Vector2f(100.0f, 120.0f),
		sf::Vector2f speed = sf::Vector2f(20.0f, 20.0f));
	void translate(char direction);
	void instantTranslate();
	void addBody();
private:
	void loadTextures(void);
};