// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

void platformUpdate(char);
void ballUpdate(void);
void resetGame(void);
void createBricks(void);

bool plMove = false;
bool start = false, game = true;
bool blFirstHit = false;
int scoreVal = 0;
float platformX = (SCREEN_WIDTH - PLATFORM_SIZE_A) / 2, platformY = SCREEN_HEIGHT - 50;
float ballX = platformX + PLATFORM_SIZE_A / 2, ballY = platformY - 40;
float ballSpeedX = BALL_SPEED, ballSpeedY = BALL_SPEED;
list<Brick> bricks;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML 2.6 / Brick Breaker");
const sf::RenderWindow* pwindow = &window;
sf::Event event;
sf::RectangleShape platform(sf::Vector2f(PLATFORM_SIZE_A, PLATFORM_SIZE_B));
sf::CircleShape ball(sf::CircleShape(BALL_SIZE_A, BALL_SIZE_B));

sf::Texture brickTexture;
sf::Texture brickTexture0;
sf::Texture brickTexture1;
sf::Texture brickTexture2;
const sf::Texture* pbrickTexture = &brickTexture;

int main()
{
	char lastDirection = 'N'; // R, L, N

	sf::Text gameOver, score;
	sf::Font font;
	if (!font.loadFromFile(FONT_PATH))
		cerr << "Cant load font!";
	else {
		gameOver.setFont(font);
		score.setFont(font);
	}
	gameOver.setString("Game Over!\nPress Space To Continue...");
	gameOver.setPosition(sf::Vector2f(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 + 30));
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setCharacterSize(25);
	gameOver.setStyle(sf::Text::Bold);

	score.setString(to_string(scoreVal));
	score.setPosition(sf::Vector2f(10.f, 10.f));
	score.setFillColor(sf::Color::Red);
	score.setCharacterSize(20);
	score.setStyle(sf::Text::Bold);

	sf::Texture ballTexture, platformTexture;
	const sf::Texture* pballTexture = &ballTexture;
	const sf::Texture* pplatformTexture = &platformTexture;
	
	if (!ballTexture.loadFromFile(BALL_TEXTURE_PATH))
		cerr << "Cant load ball texture!";
	if (!platformTexture.loadFromFile(PLATFORM_TEXTURE_PATH))
		cerr << "Cant load platform texture!";

	ballTexture.setSmooth(true);
	ball.setTexture(pballTexture);

	platformTexture.setSmooth(true);
	platform.setTexture(pplatformTexture);

	window.setFramerateLimit(FRAME_RATE);
	platform.setPosition(sf::Vector2f(platformX, platformY));
	ball.setPosition(sf::Vector2f(ballX, ballY));
	createBricks();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::D) {
					plMove = true;
					lastDirection = 'R';
				}
				if (event.key.code == sf::Keyboard::A) {
					plMove = true;
					lastDirection = 'L';
				}
				if (event.key.code == sf::Keyboard::Space) {
					if (game)
						start = true;
					else {
						resetGame();
						game = true;
						blFirstHit = false;
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::D) {
					plMove = false;
					lastDirection = 'N';
				}
				if (event.key.code == sf::Keyboard::A) {
					plMove = false;
					lastDirection = 'N';
				}
			}
		}

		window.clear(sf::Color::Black);
		
		if (start) {
			platformUpdate(lastDirection);
			ballUpdate();
		}

		if (!game)
			window.draw(gameOver);

		window.draw(ball);
		window.draw(platform);
		score.setString(to_string(scoreVal));
		window.draw(score);

		for (Brick& instance : bricks) {
			if (instance.live) {
				window.draw(instance.brick);
				if (instance.brick.getGlobalBounds().intersects(ball.getGlobalBounds())) {
					ballSpeedY *= -1;
					instance.live = false;
					scoreVal += 1;
				}
			}
		}

		window.display();
	}
	return 0;
}

//*******************************
void platformUpdate(char direction) {
	if (direction == 'R' && platform.getPosition().x + PLATFORM_SIZE_A <= SCREEN_WIDTH)
		platformX += PLATFORM_SPEED;
	else if (direction == 'L' && (platform.getPosition().x + PLATFORM_SIZE_A) - PLATFORM_SIZE_A >= 0)
		platformX -= PLATFORM_SPEED;

	platform.setPosition(sf::Vector2f(platformX, platformY));
}

void ballUpdate(void) {
	float ballXPos = ball.getPosition().x;
	float ballYPos = ball.getPosition().y;

	if (ballXPos + BALL_SIZE_A * 2 >= SCREEN_WIDTH || ballXPos <= 0 && blFirstHit)
		ballSpeedX *= -1;
	if (ballYPos <= 0) {
		ballSpeedY *= -1;
		blFirstHit = true;
	}
	if (ballYPos + BALL_SIZE_A * 2 >= SCREEN_HEIGHT) {
		game = false;
		start = false;
		scoreVal = 0;
	}

	// check for collision with platform.
	if (ball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
		ballSpeedY *= -1;
		blFirstHit = true;
	}

	// update ball coordinates and position.
	ballY -= ballSpeedY;
	if (blFirstHit)
		ballX -= ballSpeedX;

	ball.setPosition(sf::Vector2f(ballX, ballY));
}

void resetGame(void) {
	platformX = (SCREEN_WIDTH - PLATFORM_SIZE_A) / 2;
	platformY = SCREEN_HEIGHT - 50;
	ballX = platformX + PLATFORM_SIZE_A / 2;
	ballY = platformY - 40;
	platform.setPosition(sf::Vector2f(platformX, platformY));
	ball.setPosition(sf::Vector2f(ballX, ballY));
}

void createBricks(void) {
	bricks.clear();

	if (!(brickTexture0.loadFromFile(BRICK_0_PATH) && brickTexture1.loadFromFile(BRICK_1_PATH) && 
		brickTexture2.loadFromFile(BRICK_2_PATH)))
		cerr << "Cant load brick textures!";

	for (int i = 1; i < BRICK_ROWS; i++)
		for (int j = 1; j < BRICK_COULMNS; j++) {

			brickTexture = brickTexture1;
			bricks.push_front(Brick(sf::Vector2f(j * BRICK_H_GAP, i * BRICK_V_GAP), pbrickTexture));
		}
}