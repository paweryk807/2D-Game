#include "Menu.h"

Menu::Menu() {
	try {
		restart = false;
		current = 0;
		loadFont(FONT_PATH);
		std::string firstOptions[5] = { "Resume", "Start", "Options", "Scoreboard", "Quit" };
		for (int i = 0; i < 5; i++) {
			sf::Text object;
			object.setFont(font);
			object.setString(firstOptions[i]);
			object.setPosition(sf::Vector2f(WIDTH/2 - firstOptions[i].length()*10, ((HEIGHT/2)/6 * (i + 1)))); // /6 dla symetrii
			object.setFillColor(sf::Color::White);
			menu.push_back(object);

		}
		current = 1;
		menu[current].setFillColor(sf::Color::Magenta);
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

bool Menu::restarted() {
	if (restart) {
		restart = false;
		return true;
	}
	return restart;
}
void Menu::drawMenu(sf::RenderWindow* window) {
	for (int i = 1; i < menu.size(); i++) {
		window->draw(menu[i]);
	}
}

void Menu::drawInGameMenu(sf::RenderWindow* window) {
	for(auto elem : menu){
		window->draw(elem);
	}
}

void Menu::gameStarted() {
	if (!restart) {
		
	}
}

void Menu::gameRunning() {
}

void Menu::drawOptions(sf::RenderWindow* window) {
	std::string optionsMenu = { };


}

void Menu::drawScoreboard(sf::RenderWindow* window) {

}

bool Menu::moveUp(bool started) {
	if (!started) {
		if (current > 1) {
			menu[current].setFillColor(sf::Color::White);
			current--;
			menu[current].setFillColor(sf::Color::Magenta);
			return true;
		}
	}
	else if (current > 0) {
		menu[current].setFillColor(sf::Color::White);
		current--;
		menu[current].setFillColor(sf::Color::Magenta);
		return true;
	}
	return false;
	
}

bool Menu::moveDown() {
	if (current < menu.size() - 1) {
		menu[current].setFillColor(sf::Color::White);
		current++;
		menu[current].setFillColor(sf::Color::Magenta);
		return true;
	}
	return false;

}

sf::Font Menu::getFont() {
	return font;
}

bool Menu::handle(sf::RenderWindow* window, sf::View view, bool started) {
	bool esc = false;
	restart = esc;
	if (!started && current < 1) moveDown();
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
					moveUp(started);
					break;
				case sf::Keyboard::Escape:
					if (started) {
						return false;
					}
					else {
						window->close();
					}
					break;
				case sf::Keyboard::Enter:
					if(instruction(window)) {
						esc = true;	
						window->close();	


					}
					else {
						return false;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::Resized:
				ResizeView(*window, view);
            break;
			}
		}
		window->clear();
		if (!started) {
			drawMenu(window);
		}
		else {
			drawInGameMenu(window);
		}

		window->display();
	}
	return 1;
}

bool Menu::instruction(sf::RenderWindow* window) {
	switch (current) {
	case 0:
		break;
	case 1:
		restart = true;
		break;
	case 2:
		while (window->isOpen()) {
			drawOptions(window);

		}
		break;
	case 3:
		while (window->isOpen()) {
			drawScoreboard(window);
		}
		break;
	case 4:
		return true;
		break;

	}
	return false;
}