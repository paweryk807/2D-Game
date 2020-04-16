#include "Map.h"

// Przemyslec p-try c-ora
Map::Map(unsigned int sizeParam, const std::string& lvlDirectory) {
	try {

		background.setSize(sf::Vector2f(1280, 720));
		loadBackground("images/bg.jpg");
		background.setTexture(&(this->backgroundTexture));

		tab = new unsigned int[sizeParam];
		loadLevelToTab(lvlDirectory, sizeParam);
		tiles.load("images/sheet.png", sf::Vector2u(16, 16), tab, 80, 45);
		setCollider(sizeParam);
		

	}
	catch(std::exception ){
		
	}
}

bool Map::loadLevelToTab(const std::string& directory, unsigned int tabSize) {
	std::fstream plik;
	plik.open(directory);
	if (!plik.good() || !plik.is_open()) {
		throw std::exception("Level load exception");
		plik.close();
		return false;
	}
	else {
		std::string line = "file_line_handler";
		unsigned int i = 0;
		while (!plik.eof() && line != "" && i < tabSize) {
			std::getline(plik, line, ' ');
			tab[i] = stoi(line);
			i++;
		}
	}
	plik.close();
	return true;
}

void Map::setCollider(const unsigned int sizeTab)
{	
	float width = 0, height = 0;
	int w_param = 0;
	int h_param = 0;
	bool add;
	for (int i = 0; i < sizeTab; i++) {		
		if (w_param == 80) {
			w_param = 0;
			h_param++;
		}
		add = false;
		if (tab[i] >= 7 && tab[i] <= 14) {
			add = true;
		}
		//else if (tab[i] >= 24 && tab[i] <= 30) {
		//        	add = true;
		//}
		//else if (tab[i] >= 41 && tab[i] <= 47) {
		//	add = true;
		//}
	//	else if (tab[i] >= 58 && tab[i] <= 61) {
		//	add = true;
		//}
		//else if (tab[i] >= 63 && tab[i] <= 64) {
		//	add = true;
		//}
		if (add) {
			sf::RectangleShape tmp(sf::Vector2f(16, 16));
			tmp.setOrigin(8, 8);
			width = w_param * 16.f;// + 8.f;
			height = h_param * 16.f;/// /+ 8.f;
			tmp.setPosition(sf::Vector2f(width, height));
			platforms.push_back(new Collider(tmp));
		}
		w_param++;
	}
	// OGRANICZA SIE LICZBA BLOKOW ALE NIE KOLIDUJE POPRAWNIE
	
	for (int i = 0; i < platforms.size(); i++) {
		if (i > 0) {
			if ((platforms[i]->getPosition().x - platforms[i]->getPosition().x) <= 16.1)  // Kolejny blok z danych
			{
				sf::RectangleShape tmp = platforms[i-1]->getBody();
				sf::Vector2f newSize(platforms[i - 1]->getBody().getSize().x + platforms[i]->getBody().getSize().x, platforms[i - 1]->getBody().getSize().y);
				sf::Vector2f newPos(platforms[i - 1]->getBody().getPosition().x + (0.5)*(platforms[i - 1]->getBody().getPosition().x + platforms[i]->getBody().getPosition().x), platforms[i - 1]->getBody().getPosition().y);
				tmp.setSize(newSize);
				tmp.setOrigin(newSize.x/2, newSize.y/2);
				tmp.setPosition(newPos);
				platforms[i - 1]->setBody(tmp);
				platforms.erase(platforms.begin() + i);
				
			}
		}
	}
// KOLIDUJACE BLOKI :
// 7,8,9,10,11,12,14
// 24,25,26,27,28,29,30
// 41,42,43,44,45,46,47
// 58,59,60,61,63,64
 }

bool Map::checkCollision(sf::Vector2f direction, Character* character)
{
	bool collision = false;
	for (auto platform : platforms) {
		if (platform->checkCollision(character->getCollider(), direction, 2.0f)) {
			character->onCollision(direction);
			collision = true;
		}
		else collision = false;
	}
	return collision;
}

bool Map::checkBulletCollision(sf::Vector2f direction, Bullet bullet)
{
	for (auto platform : platforms) {
		if (platform->checkCollision(bullet.getCollider(), direction, 1.4f)) {
			return true;
		}
	}
	return false;
}

bool Map::checkPosition(Character* character)
{
	if (character->getPosition().x > 1280 || character->getPosition().x < 0) {
		return false;
	}
	else if (character->getPosition().y > 720 || character->getPosition().y < 0) {
		return false;
	}
	return true;
}

bool Map::loadBackground(const std::string& texture) {
	if (!backgroundTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
		return 0;
	}
	return 1;
}

bool Map::wall(Character* character) {
	for (auto platform : platforms) {
		if (platform->checkCollisionX(character->getCollider())) {
			return true;
		}
	}
	return false;
}

sf::Vector2f Map::getSize() const
{
	return sf::Vector2f(1280, 720);
}

void Map::draw(sf::RenderWindow& window) const {
	window.draw(background);
	window.draw(tiles);
}