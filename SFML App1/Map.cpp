#include "Map.h"

Map::Map(unsigned int sizeParam, const std::string& lvlDirectory) {
	try {

		background.setSize(sf::Vector2f(1280, 720));
		loadBackground("images/bg.jpg");
		background.setTexture(&(this->backgroundTexture));

		tab = new unsigned int[sizeParam];
		loadLevelToTab(lvlDirectory, sizeParam);
		tiles.load("images/sheet.png", sf::Vector2u(16, 16), tab, 80, 45);
		setPlatforms(sizeParam);
		

	}
	catch(std::exception e){
		std::cerr << e.what();
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

void Map::setPlatforms(const unsigned int sizeTab)
{
	float size_param = 16.f;
	float half_size = 8.f;
	float width = 0, height = 0;
	int w_param = 0;
	int h_param = 0;
	bool add;
	for (unsigned int i = 0; i < sizeTab; i++) {
		if (w_param == 80) {
			w_param = 0;
			h_param++;
		}
		add = false;
		if (tab[i] >= 7 && tab[i] <= 14) {
			add = true;
		}
		else if (tab[i] >= 24 && tab[i] <= 30) {
		        	add = true;
		}
		else if (tab[i] >= 41 && tab[i] <= 47) {
			add = true;
		}
		else if (tab[i] >= 58 && tab[i] <= 61) {
			add = true;
		}
		else if (tab[i] >= 63 && tab[i] <= 64) {
			add = true;
		}
		if (add) {
			sf::RectangleShape tmp(sf::Vector2f(size_param, size_param));
			width = w_param * size_param + half_size;// + 8.f;
			height = h_param * size_param + half_size;/// /+ 8.f;
			tmp.setPosition(sf::Vector2f(width, height));
			platforms.push_back(std::unique_ptr<Platform>(new Platform(tmp)));
		}
		w_param++;
	}
	// DODAWANIE PARAMI IDENTYCZNYCH BLOKOW W JEDNEJ PLASZCZYZNIE ___  NIE DZIALA IDEALNIE ALE REDUKUJE 1440 BLOKOW KOLIDERA DO 36 
	bool changed = false;
	while (!changed)
	{
		for (int i = 1; i < platforms.size(); i++) {
			sf::RectangleShape tmp = platforms[i - 1]->getBody();
			if (platforms[i]->getPosition().y == tmp.getPosition().y && platforms[i]->getBody().getSize() == tmp.getSize()) {
				float distance = platforms[i]->getCollider().getHalfSize().x + platforms[i - 1]->getCollider().getHalfSize().x;
				if (platforms[i]->getPosition().x - platforms[i - 1]->getPosition().x <= distance)  // Kolejny blok z danych
				{
					changed = true;
					sf::Vector2f newSize((tmp.getSize().x + platforms[i]->getBody().getSize().x) , tmp.getSize().y);
					sf::Vector2f newPos((tmp.getPosition().x + platforms[i]->getBody().getPosition().x)/2, tmp.getPosition().y);
					tmp.setSize(newSize);
					tmp.setOrigin(newSize.x / 2, newSize.y / 2);
					tmp.setPosition(newPos);
					platforms[i]->setBody(tmp);
					platforms.erase(platforms.begin() + i - 1);
				}
			}
		}
		if (!changed)
			break;
		changed = false;
	}


	while (!changed)
	{
		for (int i = 1; i < platforms.size(); i++) {
			sf::RectangleShape tmp = platforms[i - 1]->getBody();
			if (platforms[i]->getPosition().x == tmp.getPosition().x && platforms[i]->getBody().getSize() == tmp.getSize()) {
				float distance = platforms[i]->getCollider().getHalfSize().y + platforms[i - 1]->getCollider().getHalfSize().y;
				if (platforms[i]->getPosition().y - platforms[i - 1]->getPosition().y <= distance)  // Kolejny blok z danych
				{
					changed = true;
					sf::Vector2f newSize(tmp.getSize().x , (tmp.getSize().y + platforms[i]->getBody().getSize().y));
					sf::Vector2f newPos((tmp.getPosition().x + platforms[i]->getBody().getPosition().x) / 2, tmp.getPosition().y + 8);
					tmp.setSize(newSize);
					tmp.setOrigin(newSize.x / 2, newSize.y / 2);
					tmp.setPosition(newPos);
					platforms[i]->setBody(tmp);
					platforms.erase(platforms.begin() + i - 1);
				}
			}
		}
		if (!changed)
			break;
		changed = false;
	}
// KOLIDUJACE BLOKI :
// 7,8,9,10,11,12,14
// 24,25,26,27,28,29,30
// 41,42,43,44,45,46,47
// 58,59,60,61,63,64

}

bool Map::checkCollision(sf::Vector2f direction, Character* character) const {
	bool collision = false;
	sf::Vector2f characterPosition = character->getPosition();
	for(auto iterator = platforms.begin(); iterator!= platforms.end(); iterator++) { //for (platforms platform : &platforms)
		if(std::abs(characterPosition.x - iterator->get()->getPosition().x) < 700 && std::abs(characterPosition.y - iterator->get()->getPosition().y) < 100)
		if (iterator->get()->getCollider().checkCollision(character->getCollider(), direction, 1.2f)) {
			character->onCollision(direction);
			if (direction.x != 0) {
				character->setVelocity(sf::Vector2f(0, character->getVelocity().y));
			}
			if (direction.y != 0) {
				character->setVelocity(sf::Vector2f(character->getVelocity().x, 0));
			}

			collision = true;
		}
	}
	return collision;
}

bool Map::checkBulletCollision(sf::Vector2f direction, Bullet* bullet) const {
	for (auto iterator = platforms.begin(); iterator != platforms.end(); iterator++) {//for (auto platform : platforms) {
		if (iterator->get()->getCollider().checkCollision(bullet->getCollider(), direction, 1.f)) {
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
/*
bool Map::openBox(Character* player)
{
	if)
}
*/
bool Map::loadBackground(const std::string& texture) {
	if (!backgroundTexture.loadFromFile(texture)) {
		throw std::exception("unable to open texture file");
		return 0;
	}
	return 1;
}

bool Map::wall(Character* character) const {
	for (auto iterator = platforms.begin(); iterator != platforms.end(); iterator++) {//	for (auto platform : platforms) {
		if (iterator->get()->getCollider().wallCollision(character->getCollider())) {// , dir, 1.0)) {
			return true;
		}
	}
	return false;
}

sf::Vector2f Map::getSize() const {
	return sf::Vector2f(1279, 719);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(background);
	target.draw(tiles);
}

Map::~Map() {
	delete tab; 
	platforms.clear();
}
