#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>

int main() {
	bool isDead = false;
	
	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}

	int score = 0;
	std::string score_string;
	std::stringstream s;
	s << "Score:" << score;
	s >> score_string;

	sf::Text score_text(score_string, font, 20);
	score_text.setFillColor(sf::Color::White);
	score_text.setPosition(0, 0);

	sf::Vector2<int> fieldSize(20, 15);
	
	std::vector<sf::Vector2i> snake = { sf::Vector2i(3, 4) };

	srand(time(NULL));
	sf::Vector2i food(rand() % fieldSize.x, rand() % fieldSize.y);

	sf::Texture blockTexture;
	if (!blockTexture.loadFromFile("block.png")){
		std::cout<<"block.png is not found"<<std::endl;
		return EXIT_FAILURE;
	}

	sf::Sprite block(blockTexture);

	sf::Vector2<float> blockSize(block.getLocalBounds().width, block.getLocalBounds().height);

	sf::VideoMode mode(
		unsigned int(blockSize.x * fieldSize.x), 
		unsigned int(blockSize.y * fieldSize.y));

	sf::RenderWindow w(mode,L"³g¦Y³D");
	
	enum class Direction { UP, DOWN, RIGHT, LEFT };
	Direction direction = Direction::RIGHT;

	sf::Clock clock;

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Up) {
					direction = Direction::UP;
				}else if (evt.key.code == sf::Keyboard::Down) {
					direction = Direction::DOWN;
				}else if(evt.key.code == sf::Keyboard::Right){
					direction = Direction::RIGHT;
				}else if(evt.key.code == sf::Keyboard::Left){
					direction = Direction::LEFT;
				}
				if (isDead) {
					score = 0;
					s.clear();
					s << "Score:" << score;
					s >> score_string;
					score_text.setString(score_string);
					snake = { sf::Vector2i(3, 4) };
					isDead = false;
				}
			}
		}
		
		

		if (clock.getElapsedTime().asSeconds() >= 0.4f) {
			sf::Vector2i head = snake[0];

			if (direction == Direction::UP) {
				head.y--;
			}else if (direction == Direction::DOWN) {
				head.y++;
			}else if (direction == Direction::RIGHT) {
				head.x++;
			}else if (direction == Direction::LEFT) {
				head.x--;
			}

			for (int i = 0; i < snake.size(); i++) {
				if (head == snake[i]) {
					isDead = true;
				}
			}

			if (head.x < 0 || head.x >= fieldSize.x ||
				head.y < 0 || head.y >= fieldSize.y) {
				isDead = true;
			}

			if (!isDead) {
				snake.insert(snake.begin(), head);
				if (head == food) {
					score++;
					s.clear();
					s << "Score:" << score;
					s >> score_string;
					score_text.setString(score_string);
					food = sf::Vector2i(rand() % fieldSize.x, rand() % fieldSize.y);
				}else {
					snake.pop_back();
				}
			}
			
			
			clock.restart();
		}

		if (isDead) {
			w.clear(sf::Color::Red);
		}
		else {
			w.clear();
		}
		

		for (const sf::Vector2i& body : snake) {
			sf::Vector2<float> bodyPos(
				body.x * blockSize.x, 
				body.y * blockSize.y);
			block.setPosition(bodyPos);
			w.draw(block);
		}

		sf::Vector2<float> foodPos(
			food.x* blockSize.x,
			food.y* blockSize.y);
		block.setPosition(foodPos);
		w.draw(block);
		
		w.draw(score_text);
		
		w.display();
	}
	return EXIT_SUCCESS;
}