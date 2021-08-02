#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <httplib.h>

int main() {
	httplib::SSLClient client("api.covid19api.com");

	const std::string data = client.Get("/world/total")->body;

	nlohmann::json j = nlohmann::json::parse(data);

	int confirmed = j["TotalConfirmed"];
	int death = j["TotalDeaths"];
	int recovered = j["TotalRecovered"];
	
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::String confirmedString(std::to_string(confirmed));
	sf::Text confirmedText(confirmedString, font);
	confirmedText.setPosition(200, 20);

	sf::String deathString(std::to_string(death));
	sf::Text deathText(deathString, font);
	deathText.setPosition(200, 80);

	sf::String recoveredString(std::to_string(recovered));
	sf::Text recoveredText(recoveredString, font);
	recoveredText.setPosition(200, 140);

	sf::Texture confirmedTexture;
	if (!confirmedTexture.loadFromFile("confirmed.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite confirmedSprite(confirmedTexture);
	confirmedSprite.setPosition(15, 20);

	sf::Texture deathTexture;
	if (!deathTexture.loadFromFile("death.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite deathSprite(deathTexture);
	deathSprite.setPosition(15, 80);

	sf::Texture recoveredTexture;
	if (!recoveredTexture.loadFromFile("recovered.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite recoveredSprite(recoveredTexture);
	recoveredSprite.setPosition(15, 140);

	sf::RenderWindow w(sf::VideoMode(400, 200), L"COVID-19");
	w.setFramerateLimit(30);
	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}
		w.clear();
		w.draw(confirmedSprite);
		w.draw(deathSprite);
		w.draw(recoveredSprite);
		w.draw(confirmedText);
		w.draw(deathText);
		w.draw(recoveredText);
		w.display();
	}
	return EXIT_SUCCESS;
}