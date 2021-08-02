#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::Font font;
	if (font.loadFromFile("arial.ttf") == false) {
		return EXIT_FAILURE;
	}
	sf::Text text("Hello", font);

	sf::RenderWindow w(sf::VideoMode(400,200),"Hi");
	text.setPosition(-70, 0);

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}
		if (text.getPosition().x > 400) {
			text.setPosition(-70,0);
		}
		w.draw(text);
		w.display();
		text.move(0.01,0);
		w.clear();
	}

	return 0;
}