#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>


int main() {
	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}
	std::ifstream in("input.txt");
	std::string s;
	std::getline(in, s);
	sf::Text text(s, font, 200);
	text.setFillColor(sf::Color(0,255,0));
	sf::Text text2;
	text2 = text;
	sf::RenderWindow w(sf::VideoMode(1000, 200), "Hi");
	float window_w = float(w.getSize().x);

	sf::CircleShape circle(2);
	circle.setFillColor(sf::Color(20, 20, 20));

	enum class Direction { RIGHT_TO_LEFT, LEFT_TO_RIGHT };
	//enum class Speed { FAST, SLOW , speed_1 , speed_2 , speed_3 ,speed_4 , speed_5 };

	Direction direction = Direction::RIGHT_TO_LEFT;
	//Speed speed = Speed::FAST;
	float diff = 1.f;

	bool isTextEnable = true;
	bool isText2Enable = false; 
	
	sf::Rect<float> text_w;
	text_w = text.getLocalBounds();

	switch (direction) {
	case Direction::RIGHT_TO_LEFT:
		text.setPosition(float(w.getSize().x), 0);
		text2.setPosition(float(w.getSize().x), 0);
		break;

	case Direction::LEFT_TO_RIGHT:
		text.setPosition(-text_w.width, 0);
		text2.setPosition(-text_w.width, 0);
		break;
	default:
		return EXIT_FAILURE;
	}

	
	
	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Key::Left) {
					direction = Direction::RIGHT_TO_LEFT;
				}else if (evt.key.code == sf::Keyboard::Key::Right) {
					direction = Direction::LEFT_TO_RIGHT;
				}else if (evt.key.code == sf::Keyboard::Key::F) {
					diff = 8.f;
				}else if (evt.key.code == sf::Keyboard::Key::Num5 || evt.key.code == sf::Keyboard::Key::Numpad5) {
					diff = 8.f;
				}else if (evt.key.code == sf::Keyboard::Key::Num4 || evt.key.code ==  sf::Keyboard::Key::Numpad4) {
					diff = 6.f;
				}else if (evt.key.code == sf::Keyboard::Key::Num3 || evt.key.code == sf::Keyboard::Key::Numpad3) {
					diff = 4.f;
				}else if (evt.key.code == sf::Keyboard::Key::Num2 || evt.key.code == sf::Keyboard::Key::Numpad2){
					diff = 2.f;
				}else if (evt.key.code == sf::Keyboard::Key::Num1 || evt.key.code == sf::Keyboard::Key::Numpad1) {
					diff = 1.f;
				}else if (evt.key.code == sf::Keyboard::Key::S ) {
					diff = 1.f;
				}else if (evt.key.code == sf::Keyboard::Key::Add) {
					diff *= 2;
				}else if (evt.key.code == sf::Keyboard::Key::Subtract) {
					diff /= 2;
				}
			}

		}
		/*
		switch (speed) { 
		case Speed::speed_5:
		case Speed::FAST:
			diff = 8.f;
			break;
		case Speed::speed_4:
			diff = 6.f;
			break;
		case Speed::speed_3:
			diff = 4.f;
			break;
		case Speed::speed_2:
			diff = 2.f;
			break;
		case Speed::SLOW:
		case Speed::speed_1:
			diff = 1.f;
			break;
		}*/

		switch (direction) {
		case Direction::RIGHT_TO_LEFT:
			if (isTextEnable) {
				if (text.getPosition().x < -text_w.width) {
					text.setPosition(window_w, 0);
					isTextEnable = false;
				}
				if (text.getPosition().x < 0) {
					isText2Enable = true;
				}
				w.draw(text);
				text.move(-diff, 0);
			}
			if (isText2Enable) {
				if (text2.getPosition().x < -text_w.width) {
					text2.setPosition(window_w, 0);
					isText2Enable = false;
				}
				if (text2.getPosition().x < 0) {
					isTextEnable = true;
				}
				w.draw(text2);
				text2.move(-diff, 0);
			}
			break;
		case Direction::LEFT_TO_RIGHT:
			if (isTextEnable) {
				if (text.getPosition().x > window_w) {
					text.setPosition(-text_w.width, 0);
					isTextEnable = false;
				}
				if (text.getPosition().x > window_w - text_w.width) {
					isText2Enable = true;
				}
				w.draw(text);
				text.move(diff, 0);
			}
			if (isText2Enable) {
				if (text2.getPosition().x > window_w) {
					text2.setPosition(-text_w.width, 0);
					isText2Enable = false;
				}
				if (text2.getPosition().x > window_w - text_w.width) {
					isTextEnable = true;
				}
				w.draw(text2);
				text2.move(diff, 0);
			}
			break;
		default:
			return EXIT_FAILURE;
		}
		for (unsigned int i = 0; i < w.getSize().x; i += 4) {
			for (unsigned int j = 0; j < w.getSize().y; j += 4) {
				circle.setPosition(float(i), float(j));
				w.draw(circle);
			}
		}
		w.display();
		w.clear();
	}
	
	return 0;
}