#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main() {
	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}

	sf::Text text("Hello World!", font);
	sf::Text text2;
	text2 = text;
	sf::RenderWindow w(sf::VideoMode(1000, 500), "Hi");

	bool isTextEnable = true;
	bool isText2Enable = false;

	sf::Rect<float> text_w;
	text_w = text.getLocalBounds();

	text.setPosition(-text_w.width, 0);
	text2.setPosition(-text_w.width, 0);

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}
		if (isTextEnable) {
			if (text.getPosition().x > w.getSize().x) {
				text.setPosition(-text_w.width, 0);
				isTextEnable = false;
			}
			if (text.getPosition().x > w.getSize().x - text_w.width) {
				isText2Enable = true;
			}
			w.draw(text);
			text.move(0.01f, 0);
		}
		if (isText2Enable) {
			if (text2.getPosition().x > w.getSize().x) {
				text2.setPosition(-text_w.width, 0);
				isText2Enable = false;
			}
			if (text2.getPosition().x > w.getSize().x - text_w.width) {
				isTextEnable = true;
			}
			w.draw(text2);
			text2.move(0.01f, 0);

		}
		w.display();
		w.clear();
	}

	return 0;
}