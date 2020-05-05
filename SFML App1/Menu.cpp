#include "Menu.h"

Menu::Menu() {
	try {
		restart = false;
		game = false;
		exit = false;
		current = 0;
		loadFont(FONT_PATH);
		std::string firstOptions[5] = { "Resume", "Start", "Options", "Scoreboard", "Quit" };
		for (int i = 0; i < 5; i++) {
			sf::Text object;
			object.setFont(font);
			object.setString(firstOptions[i]);
			object.setPosition(sf::Vector2f(WIDTH * 0.5f - firstOptions[i].length()*10.f, (((HEIGHT   * 0.5f)/6.f) * (float)(i + 1)))); // /6 dla symetrii
			object.setFillColor(sf::Color::White);
			menu.push_back(object);

		}
		current = 1;
		menu[current].setFillColor(sf::Color::Magenta);
		loadScoreboard();
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
void Menu::drawMenu(sf::RenderWindow& window) {
	for (int i = 1; i < menu.size(); i++) {
		window.draw(menu[i]);
	}
}

void Menu::drawInGameMenu(sf::RenderWindow& window) {
	for(auto elem : menu){
		window.draw(elem);
	}

}

void Menu::gameStarted() {
	if (!restart) {
		
	}
}

void Menu::gameRunning() {
}

void Menu::drawOptions(sf::RenderWindow& window) {
	std::string optionsMenu = { };


}

bool Menu::loadScoreboard() {
	std::ifstream plik;
	plik.open(SCOREBOARD_PATH);
	if (!plik.good() || !plik.is_open()) {
		throw std::exception("Scoreboard load exception");
		plik.close();
		return false;
	}
	else {
		std::string line = "file_line_handler";
		unsigned int i = 10;
		sf::Text tmp = menu[0];
		while (!plik.eof() && line != "" && i > 0) {
			std::getline(plik, line);
			unsigned int pos = line.find(';');
			std::string name = line.substr(0, pos);
			std::string score = line.substr(pos + 1, (line.length()-1));
  			tmp.setString(name + ' ');
			scores.push_back(std::make_tuple(tmp, stoi(score)));
			i--;
		}
		plik.close();
		return true;

	}
}

bool Menu::saveScoreboard() {
	std::ofstream plik;
	plik.open(SCOREBOARD_PATH);
	if (!plik.good() || !plik.is_open()) {
		throw std::exception("Scoreboard load exception");
		plik.close();
		return false;
	}
	else {
		std::string tmp;
		for (auto& elem : scores) {
			tmp = std::get<0>(elem).getString();
			tmp.erase(tmp.length() - 1);
			tmp+=";" + std::to_string(std::get<1>(elem));
			plik << tmp;
			if(!(std::get<0>(elem).getString() == std::get<0>(scores[scores.size() -1]).getString() && std::get<1>(elem) == std::get<1>(scores[scores.size() - 1])))
				plik << std::endl;
		}
		plik.close();
		return true;
	}
}

bool Menu::sortScores() {
	if (scores.size()  > 0) {
		std::tuple<sf::Text, int> tmp;
		sf::Vector2f pos;
		for (int i = 0; i < scores.size(); i++)
			for (int j = 0; j < scores.size() - 1; j++) 
				if (std::get<1>(scores[j]) < std::get<1>(scores[j + 1]))
					std::swap(scores[j], scores[j + 1]);
		return 1;
	}
	return 0;
}


void Menu::drawScoreboard(sf::RenderWindow& window) {
	sf::Text tmp;
	sortScores();
	unsigned int position = 1;
	for (auto &elem : scores) {
		tmp = std::get<0>(elem);
		tmp.setString(std::to_string(position) + ". " + tmp.getString() + std::to_string(std::get<1>(elem)));
		tmp.setPosition(WIDTH * 0.5f - tmp.getString().getSize() * 10.f, 100.f + (float)position * 40.f);
		position++;
		window.draw(tmp);
	}
}

bool Menu::addToScores(sf::RenderWindow& window,unsigned int score) {
	bool dataSet = false;
	sf::String input;
	sf::Text userName;
	/* MALE GUI */

	sf::String textField("Zakwalifikowales sie do rankingu,\n prosze wpisz tu pseudonim: ");
	sf::Text fieldToPrint;
	fieldToPrint.setString(textField);
	fieldToPrint.setFont(font);
	fieldToPrint.setPosition(110, 400);

	userName.setFont(font);
	userName.setPosition(150 + textField.getSize() * 12.5f, 400);
	userName.setFillColor(sf::Color::Blue);
	userName.setOutlineColor(sf::Color::Cyan);

	/*----------*/
	if (scores.size() < 10) {
		while (window.isOpen() && !dataSet)
		{
			sf::Event event;
			while (window.pollEvent(event) && !dataSet)
			{ 
				if (event.key.code == sf::Keyboard::Escape) {
					return false;
				}
				if (event.key.code == sf::Keyboard::BackSpace && input.getSize() > 0)
					input.erase(input.getSize() - 1);
				else if (event.key.code == sf::Keyboard::Enter) {
					userName.setString(input + ' ');
					dataSet = true;
				}
				else if (event.type == sf::Event::TextEntered) {
						input += event.text.unicode;
						userName.setString(input);
				}

			}
			window.clear();
			window.draw(fieldToPrint);
			window.draw(userName);
			window.display();
		}
		scores.push_back(std::make_tuple(userName, score));
		return 1;
	}
	else {
		sortScores(); // zeby byly posortowane; 
		int pos = 0;
		for (auto& elem : scores) {
			if (std::get<1>(elem) < score) {
				while (window.isOpen() && !dataSet) {
					sf::Event event;
				while (window.pollEvent(event) && !dataSet)
				{
					if (event.key.code == sf::Keyboard::Escape) {
						return false;
					}
					if (event.key.code == sf::Keyboard::BackSpace && input.getSize() > 0)
						input.erase(input.getSize() - 1);
					else if (event.key.code == sf::Keyboard::Enter) {
						userName.setString(input + ' ');
						dataSet = true;
						scores.erase(scores.end() - 1);
						scores.push_back(std::make_tuple(userName, score));
					}
					else if (event.type == sf::Event::TextEntered) {
						input += event.text.unicode;
						userName.setString(input);
					}
				}
				window.clear();
				window.draw(fieldToPrint);
				window.draw(userName);
				window.display();
				}

				return 1;
			}
			pos++;
		}
	}
	return 0;
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

bool Menu::handle(sf::RenderWindow& window, bool started) {
	if (!started && current < 1) moveDown();
	while (!exit && window.isOpen())
	{
		game = false;
		sf::Event event;
		while (window.pollEvent(event))
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
						window.close();
					}
					break;
				case sf::Keyboard::Enter:
					exit = instruction(window);
					if (game) return false;
					if (exit) window.close();
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
            break;
			}
		}
		window.clear();
		if (!started) {
			drawMenu(window);
		}
		else {
			drawInGameMenu(window);
		}
		window.display();
	}
	return true;
}

bool Menu::instruction(sf::RenderWindow& window) {
	bool esc = false;
	switch (current) {
	case 0:
		game = true;
		break;
	case 1:
		game = true;
		restart = true;
		break;
	case 2:
		while (!esc && window.isOpen()) {
			sf::Event event;
			while(window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				if(event.key.code == sf::Keyboard::Escape)
					esc = true;
				break;
			case sf::Event::Closed:
				window.close();
				break;

			}
			window.clear();
			drawOptions(window);	
			window.display();
		}			
		return false;
		break;
	case 3:
		while (!esc && window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event))
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Escape)
						esc = true;
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			window.clear();
			drawScoreboard(window);
			window.display();
		}	
		return false;
		break;
	case 4:
		return true;
		break;
	}
	return false;
}