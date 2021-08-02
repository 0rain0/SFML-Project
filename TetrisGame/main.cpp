#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>


int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	bool isGameStart = false;
	
	enum class Type {
		None,
		O,
		I,
		L,
		J,
		Z,
		S,
		T,
	};

	Type field[fieldWidth][fieldHeight+1] = {};

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

	sf::Texture homepageTexture;
	if (!homepageTexture.loadFromFile("Tetris.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite homepageSprite(homepageTexture);

	sf::Texture purpleTexture;
	if (!purpleTexture.loadFromFile("purple.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture greenTexture;
	if (!greenTexture.loadFromFile("green.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture redTexture;
	if (!redTexture.loadFromFile("red.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture blueTexture;
	if (!blueTexture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture yellowTexture;
	if (!yellowTexture.loadFromFile("yellow.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture lightBlueTexture;
	if (!lightBlueTexture.loadFromFile("light_blue.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture orangeTexture;
	if (!orangeTexture.loadFromFile("orange.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}

	std::map <Type, std::vector < std::vector<sf::Vector2i>>> shapes{
	//O
		{
			Type::O,
			{
				{
				sf::Vector2i(0,0),
				sf::Vector2i(1, 0),
				sf::Vector2i(0,-1),
				sf::Vector2i(1,-1)
				}
			}
		},
	//I
		{
			Type::I,
			{
				//-
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1,0),
					sf::Vector2i(2,0)
				},
				//|
				{
					sf::Vector2i(0,-2),
					sf::Vector2i(0,-1),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1)
				}
			}
		},
	//L
		{
			Type::L,
			{
				// 
				// (0,-1)* 
				// (0,0) *
				// (0,1) * *(1,1)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1),
					sf::Vector2i(1,1)
				},
				//      *
				//  * * *
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1,0),
					sf::Vector2i(1,-1)
				},
				// * *(0,-1)
				//   *(0,0)
				//   *
				{
					sf::Vector2i(-1,-1),
					sf::Vector2i(0, -1),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1),
				},
				// * * *
				// *
				{
					sf::Vector2i(-1,1),
					sf::Vector2i(-1, 0),
					sf::Vector2i(0,0),
					sf::Vector2i(1,0),
				}
			}
		},
	//J
		{
			Type::J,
			{
				// 
				//          *(0,-1)
				//	        *(0,0)
				//  (-1,1)* *(0,1)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1),
					sf::Vector2i(-1,1)
					},
				//  * * *
				//      *
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1,0),
					sf::Vector2i(1,1)
				},
				//(0,-1)* *(1,-1)
				//      *(0,0)
				//      *
				{
					sf::Vector2i(1,-1),
					sf::Vector2i(0, -1),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1),
				},
				// *
				// * * *
				{
					sf::Vector2i(-1,-1),
					sf::Vector2i(-1, 0),
					sf::Vector2i(0,0),
					sf::Vector2i(1,0),
				}
			}
		},
	//Z
		{
			Type::Z,
			{
				// * *   (-1,-1)(0,-1)
				//   * * (0,0)(1,0)
				{
					sf::Vector2i(1,0),
					sf::Vector2i(0,0),
					sf::Vector2i(0,-1),
					sf::Vector2i(-1,-1)
					},
				//   * (0,-1)
				// * * (-1,0)(0,0)
				// *   (-1,1)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0,-1),
					sf::Vector2i(-1,1)
				}
			}
		},
	//S
		{
			Type::S,
			{
				//  * *  (-1,-1)(0,-1)
				//* *  (0,0)(1,0)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0,0),
					sf::Vector2i(0,-1),
					sf::Vector2i(1,-1)
					},
				//   * (0,-1)
				// * * (-1,0)(0,0)
				// *   (-1,1)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0,1),
					sf::Vector2i(-1,-1)
				}
			}
		},
	//T
		{
			Type::T,
			{
				//* * *  (-1,0)(0,0)(1,0)
				//  *          (0,1)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0,0),
					sf::Vector2i(0,1),
					sf::Vector2i(1,0)
				},
				// *   (0,-1)
				// * * (0,0)(1,0)
				// *   (0,1)
				{
					sf::Vector2i(0,-1),
					sf::Vector2i(0, 0),
					sf::Vector2i(0,1),
					sf::Vector2i(1,0)
				},
				//  *   (-1,0)(0,0)(1,0)
				//* * *       (0,1)
				{
					sf::Vector2i(1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0,-1),
					sf::Vector2i(-1,0)
				},
				//   *       (0,-1)
				// * * (-1,0)(0,0)
				//   *       (0,1)
				{
					sf::Vector2i(-1,0),
					sf::Vector2i(0, 0),
					sf::Vector2i(0,1),
					sf::Vector2i(0,-1)
				}
			}
		},
	};

	std::vector<sf::Vector2i> currentShape;
	srand(time(NULL));
	Type currentType = Type(rand()%7+1);

	int currentIndex = 0;

	const int blockWidth = yellowTexture.getSize().x;
	const int blockHeight = yellowTexture.getSize().y;

	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;

	std::map<Type, sf::Sprite > sprites{
		{Type::O, sf::Sprite(yellowTexture)},
		{Type::I, sf::Sprite(lightBlueTexture)},
		{Type::L, sf::Sprite(orangeTexture)},
		{Type::J, sf::Sprite(blueTexture)},
		{Type::Z, sf::Sprite(redTexture)},
		{Type::S, sf::Sprite(greenTexture)},
		{Type::T, sf::Sprite(purpleTexture)},
	};
	
	backgroundTexture.setRepeated(true);
	sf::Sprite backgroundSprite(
		backgroundTexture,
		sf::IntRect(0, 0, windowWidth, windowHeight));

	
	sf::Sprite currentSprite;

	const sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);


	sf::RenderWindow w(sf::VideoMode(windowWidth, windowHeight), L"«XÃ¹´µ¤è¶ô");

	bool isStraightDown = false;

	sf::Clock clock;
	while (w.isOpen()) {
		
		currentShape = shapes[currentType][currentIndex];
		currentSprite = sprites[currentType];
		
		enum class Action {
			Hold,
			MoveDown,
			MoveLeft,
			MoveRight,
			Rotate,
		};
		Action action = Action::Hold;

		sf::Event evt;
		float currentTime = clock.getElapsedTime().asSeconds();
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (!isGameStart) {
					isGameStart = true;
				}
				switch (evt.key.code) {
				case sf::Keyboard::Left:
					action = Action::MoveLeft;
					break;
				case sf::Keyboard::Right:
					action = Action::MoveRight;
					break;
				case sf::Keyboard::Up:
					action = Action::Rotate;
					break;
				case sf::Keyboard::Down:
					currentTime = 0.3f;
					break;
				case sf::Keyboard::Space:
					isStraightDown = true;
					break;
				}
			}
		}
		
		if (isGameStart) {

			if (currentTime >= 0.3f || isStraightDown) {
				action = Action::MoveDown;
				clock.restart();
			}

			sf::Vector2i nextPos(pos);
			int nextIndex = currentIndex;
			if (action == Action::Rotate) {
				nextIndex = (nextIndex + 1) % shapes[currentType].size();
			}
			std::vector<sf::Vector2i> nextShape = shapes[currentType][nextIndex];

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
			}


			int countEmpty = 0;
			for (const sf::Vector2i& d : nextShape) {
				sf::Vector2i np = nextPos + d;
				if (np.x >= 0 && np.x < fieldWidth && np.y < fieldHeight && (np.y < 0 || field[np.x][np.y] == Type::None)) {
					countEmpty++;
				}
			}

			if (countEmpty == 4) {
				pos = nextPos;
				currentIndex = nextIndex;
				currentShape = nextShape;
			}
			else {
				if (action == Action::MoveDown) {
					for (const sf::Vector2i& d : currentShape) {
						sf::Vector2i np = pos + d;
						if (np.y >= 0) {
							field[np.x][np.y] = currentType;
						}
					}
					for (int x = 0; x < fieldWidth; x++) {
						if (field[x][0] != Type::None) {
							w.clear(sf::Color::Red);
							return EXIT_SUCCESS;
						}
					}

					for (int y = 0; y < fieldHeight + 1; y++) {
						bool isFull = true;
						for (int x = 0; x < fieldWidth; x++) {
							if (field[x][y] == Type::None) {
								isFull = false;
							}
						}
						if (isFull) {
							for (int ty = y; ty > 0; ty--) {
								for (int x = 0; x < fieldWidth; x++) {
									field[x][ty] = field[x][ty - 1];
								}
							}
							for (int x = 0; x < fieldWidth; x++) {
								field[x][0] = Type::None;
							}
							score += 100;
							s.clear();
							s << "Score:" << score;
							s >> score_string;
							score_text.setString(score_string);
						}
					}
					isStraightDown = false;
					currentType = Type(rand() % 7 + 1);
					currentIndex = 0;
					pos = origin;
				}
			}
			w.clear();
			w.draw(backgroundSprite);

			for (int x = 0; x < fieldWidth; x++) {
				for (int y = 0; y < fieldHeight; y++) {
					if (field[x][y] == Type::None) continue;

					sf::Sprite& s = sprites[field[x][y]];

					s.setPosition(float(x * blockWidth), float(y * blockHeight));
					w.draw(s);
				}
			}

			for (const sf::Vector2i& d : currentShape) {
				sf::Vector2i np = pos + d;
				currentSprite.setPosition(float(np.x * blockWidth), float(np.y * blockHeight));
				w.draw(currentSprite);
			}
			w.draw(score_text);
			w.display();
		}
		else {
			w.draw(homepageSprite);
			w.display();
		}
	}
	return EXIT_SUCCESS;
}