// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML 2.6 / Snake");
sf::Event event;
sf::Texture wallTexture, appleTexture32, appleTexture64;
const sf::Texture* pwallTexture = &wallTexture, *pappleTexture32 = &appleTexture32, *pappleTexture64 = &appleTexture64;
list<sf::RectangleShape> walls;
list<sf::RectangleShape> applesList;
sf::RectangleShape apple;
Snake snake;
Snake reset = snake;
int score = 0;

void createWalls();
bool checkSnake();
void gameRestart();
void apples();

int main()
{
	if (!wallTexture.loadFromFile(WALL_TEXTURE_PATH))
		cerr << "Can't open texture file at " << WALL_TEXTURE_PATH;
	wallTexture.setSmooth(true);
	createWalls();

	if (!appleTexture32.loadFromFile(APPLE_TEXTURE_32_PATH))
		cerr << "Can't open texture file at " << APPLE_TEXTURE_32_PATH;
	appleTexture32.setSmooth(true);

	if (!appleTexture64.loadFromFile(APPLE_TEXTURE_64_PATH))
		cerr << "Can't open texture file at " << APPLE_TEXTURE_64_PATH;
	appleTexture64.setSmooth(true);

	apples();

	sf::Font FontArial;
	sf::Text gameOver;
	if (!FontArial.loadFromFile(ARIAL_FONT_PATH))
		cerr << "Can't open font file at " << ARIAL_FONT_PATH;

	gameOver.setFont(FontArial);
	gameOver.setColor(sf::Color::Red);
	gameOver.setCharacterSize(20);
	gameOver.setStyle(sf::Text::Bold);
	gameOver.setPosition(((float)SCREEN_WIDTH - 220) / 2, ((float)SCREEN_HEIGHT - 60) / 2);

	bool start = false;
	bool game = true;
	char direction = 'D';
	window.setFramerateLimit(FRAME_RATE);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				start = true;
				if (game) {
					if (event.key.code == sf::Keyboard::W) {
						if (direction != 'S')
							direction = 'W';
					}
					if (event.key.code == sf::Keyboard::A) {
						if (direction != 'D')
							direction = 'A';
					}
					if (event.key.code == sf::Keyboard::S) {
						if (direction != 'W')
							direction = 'S';
					}
					if (event.key.code == sf::Keyboard::D) {
						if (direction != 'A')
							direction = 'D';
					}
				}
				if (!game)
					if (event.key.code == sf::Keyboard::Space) {
						gameRestart();
						game = true;
						direction = 'D';
						score = 0;
					}
				if (event.key.code == sf::Keyboard::Z) {
					snake.addBody();
					score += 1;
				}
			}
		}

		window.clear(sf::Color::Black);

		if (start && game)
			snake.translate(direction);

		if (!checkSnake())
			game = false;
		
		if (!game) {
			gameOver.setString("\tGAME OVER!\n\nYour Score: " + to_string(score) + "\nPress Space To Continue");
			window.draw(gameOver);
		}

		for (sf::RectangleShape body : snake.snake)
			window.draw(body);

		for (sf::RectangleShape wall : walls)
			window.draw(wall);

		for (sf::RectangleShape apple : applesList)
			window.draw(apple);

		window.display();
	}
	return 0;
}

//****************************************************************************
void createWalls() {
	for (int i = 0; i < SCREEN_WIDTH + WALL_SIZE_A; i += WALL_SIZE_A) {
		for (int j = 0; j < SCREEN_HEIGHT + WALL_SIZE_A; j += WALL_SIZE_A) {
			sf::RectangleShape wall(sf::Vector2f(WALL_SIZE_A, WALL_SIZE_B));
			if (i == 0)
				wall.setPosition(sf::Vector2f(i, j - WALL_SIZE_A));
			else if (j == 0)
				wall.setPosition(sf::Vector2f(i - WALL_SIZE_A, j));
			else if (i == SCREEN_WIDTH)
				wall.setPosition(sf::Vector2f(i - WALL_SIZE_A, j));
			else if (j == SCREEN_HEIGHT)
				wall.setPosition(sf::Vector2f(i, j - WALL_SIZE_A));

			wall.setTexture(pwallTexture);
			walls.push_back(wall);
		}
	}
}

bool checkSnake(void) {
	std::list<sf::RectangleShape>::iterator it = snake.snake.begin();
	std::advance(it, 0); // grab head coordinates.
	sf::Vector2f snakeHeadPos = it->getPosition();
	bool first = false; // lazy wat to crate range-based-for-loops.
	
	// check collision with walls.
	if (snakeHeadPos.x >= SCREEN_WIDTH - (snake.bodySizeA * 2) || snakeHeadPos.x <= 0 + (snake.bodySizeA * 1))
		return false;
	if (snakeHeadPos.y >= SCREEN_HEIGHT - (snake.bodySizeA * 2) || snakeHeadPos.y <= 0 + (snake.bodySizeA * 1))
		return false;

	//check collision with body.
	for (sf::RectangleShape body : snake.snake) {
		if (!first) {
			first = true;
			continue;
		}
		if (it->getGlobalBounds().intersects(body.getGlobalBounds()))
			return false;
	}

	// check collision with apples.
	if (applesList.size() != 0)
		for (sf::RectangleShape apple: applesList)
			if (apple.getGlobalBounds().intersects(it->getGlobalBounds())) {
				applesList.clear();
				snake.addBody();
				apples();
				return true;
			}

	return true;
}

void gameRestart() {
	applesList.clear();
	apples();
	snake = reset;
}

void apples() {
	if (applesList.size() == 0) {
		int appleTypeChance = rand() % 10;
		float posX = (rand() % ((SCREEN_WIDTH - 32 * 3 + 1)) + 32);
		float posY = (rand() % ((SCREEN_HEIGHT - 32 * 3 + 1)) + 32);
		apple.setPosition(sf::Vector2f(posX, posY));
		if (appleTypeChance >= 7) {// 3 in 10
			apple.setSize(sf::Vector2f(APPLE_SIZE_A * 2, APPLE_SIZE_B * 2));
			apple.setTexture(pappleTexture64, true);

			for (int i = 0; i < 4; i++) {// add 4 bodys
				snake.addBody();
				score += 1;
			}
		}
		else {
			apple.setSize(sf::Vector2f(APPLE_SIZE_A, APPLE_SIZE_B));
			apple.setTexture(pappleTexture32, true);
			score += 1;
		}
		applesList.push_back(apple);
	}
}