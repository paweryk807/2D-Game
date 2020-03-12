#include "Menu.h"

Menu::Menu() {
	try {
		current = 0;
		loadFont(FONT_PATH);
		std::string firstOptions[NUMBER_OF_ITEMS] = { "Start", "Options", "Scoreboard", "Quit" };
		for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
			text[i].setFont(font);
			text[i].setString(firstOptions[i]);
			text[i].setPosition(sf::Vector2f(WIDTH/2, ((HEIGHT/2)/(NUMBER_OF_ITEMS + 1) * (i + 1))));
			text[i].setFillColor(sf::Color::White);
		}
		text[current].setFillColor(sf::Color::Magenta);
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

bool Menu::loadFont(const std::string& fontPath) {
	if (!font.loadFromFile(fontPath)) {
		throw std::exception("Font not found");
		return 0;
	}
	return 1;
}

void Menu::draw(sf::RenderWindow*window) {
	for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
		window->draw(text[i]);
	}
}

bool Menu::moveUp() {
	if (current > 0) {
		text[current].setFillColor(sf::Color::White);
		current--;
		text[current].setFillColor(sf::Color::Magenta);
		return true;
	}
	return false;
	
}

bool Menu::moveDown() {
	if (current < NUMBER_OF_ITEMS) {
		text[current].setFillColor(sf::Color::White);
		current++;
		text[current].setFillColor(sf::Color::Magenta);
		return true;
	}
	return false;

}

bool Menu::handle(sf::RenderWindow* window) {
	bool esc = false;
	while (!esc && window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::S:
					moveDown();
					break;
				case sf::Keyboard::W:
					moveUp();
					break;
				case sf::Keyboard::Escape:
					esc = true;
					break;
				case sf::Keyboard::Enter:
					/// if(!instruction(current)){ return 0; }
					break;
				}
				break;
			case sf::Event::Closed:
				window->close();
				break;
			}
		}
		window->clear();
		draw(window);
		window->display();
	}
	return 1;
}