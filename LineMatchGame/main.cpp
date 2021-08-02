#include <SFML/Graphics.hpp>
#include<iostream>

sf::Vector2f getPixelPos(const sf::Vector2i& pos, const sf::Vector2u& blockSize) {
	return sf::Vector2f (float(pos.x * blockSize.x), float(pos.y * blockSize.y));
}

int main() {
	const int fieldWidth = 6;
	const int fieldHeight = 10;
	bool isFinish = false;

	bool field[fieldWidth][fieldHeight] = {};
	srand(time(NULL));
	for (int y = 3; y < fieldHeight; y++) {
		for (int k = 1; k <= 3; k++) {
			field[rand() % fieldWidth][y] = true;
		}
	}

	sf::Texture blockTexture;
	if (!blockTexture.loadFromFile("block.png")) {
		return EXIT_FAILURE;
	}
	
	sf::Vector2u blockSize(blockTexture.getSize());
	const int w_width = blockSize.x * fieldWidth;
	const int w_height = blockSize.y * fieldHeight;
	sf::VideoMode mode(w_width, w_height);
	sf::RenderWindow w(mode, L"簡易消行遊戲");

	sf::Sprite block(blockTexture);
	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);
	block.setPosition(getPixelPos(pos,blockSize));
	sf::Clock clock;
	sf::Event evt;
	enum class Action {
		Hold,
		MoveLeft,
		MoveRight,
		MoveDown,
		StraightDown
	};

	Action action = Action::Hold;

	while (w.isOpen()){
		action = Action::Hold;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Right) {
					action = Action::MoveRight;
				}
				if (evt.key.code == sf::Keyboard::Left) {
					action = Action::MoveLeft;
				}
				if (evt.key.code == sf::Keyboard::Down) {
					action = Action::MoveDown;
				}
				if (evt.key.code == sf::Keyboard::Space) {
					action = Action::StraightDown;
				}
			}
		}
		if (clock.getElapsedTime().asSeconds() >= 0.5) {
			action = Action::MoveDown;
			clock.restart();
		}

		sf::Vector2i nextPos = pos;

		switch (action) {
		case Action::Hold:
			break;
		case Action::MoveDown:
			nextPos.y++;
			break;
		case Action::MoveLeft:
			nextPos.x--;
			break;
		case Action::MoveRight:
			nextPos.x++;
			break;
		case Action::StraightDown:
			while (nextPos.y < fieldHeight && field[nextPos.x][nextPos.y] == false){
				nextPos.y++;
				
			}
			nextPos.y--;
			pos = nextPos;
			break;
		}

		if (nextPos.x >= fieldWidth) {
			nextPos.x = 0;
		}else if (nextPos.x < 0) {
			nextPos.x = fieldWidth - 1;
		}

		if (nextPos.y < fieldHeight && field[nextPos.x][nextPos.y] == false) {
			pos = nextPos;
		}else {
			if (action == Action::MoveDown || action==Action::StraightDown) {
				field[pos.x][pos.y] = true;

				bool isFull = true;
				for (int x = 0; x < fieldWidth; x++) {
					if (field[x][pos.y] == false) {
						isFull = false;
					}
				}
				if (isFull) {
					for (int y = pos.y; y > 0; y--) {
						for (int x = 0; x < fieldWidth; x++) {
							field[x][y] = field[x][y - 1];
						}
					}
					for (int x = 0; x < fieldWidth; x++) {
						field[x][0] = false;
					}
					isFinish = true;
					for (int y = 0; y < fieldHeight; y++) {
						for (int x = 0; x < fieldWidth; x++) {
							if (field[x][y] == true) {
								isFinish = false;
							}
						}
					}
				}
				pos = origin;
			}
		}
		

		w.clear();
		block.setPosition(getPixelPos(pos, blockSize));
		w.draw(block);
		
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (field[x][y]) {
					sf::Vector2i p(x, y);
					block.setPosition(getPixelPos(p, blockSize));
					w.draw(block);
				}
			}
		}

		w.display();
		if (isFinish) {
			w.close();
		}

	}
	return EXIT_SUCCESS;
}