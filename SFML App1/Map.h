#pragma once
#include <fstream>
#include <string>
#include "TileMap.h"
#include "Platform.h"
#include "Character.h"
#include "Bullet.h"
class Map : public sf::Drawable {
	/* Klasa utrzymujaca 
	wyswietlane na ekranie elementy oraz 
	obiekty odpowiedzialne za kolizje obiektow z mapa (platformy).*/
	unsigned int* tab;
	TileMap tiles;
	std::vector<std::unique_ptr<Platform>> platforms;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	/* Metoda odpowiedzialna za ustawienie kolizji planszy, wykonywany jest w niej algorytm optymalizacyjny scalajacy bloki */
	void setPlatforms(const unsigned int sizeTab);
	/* Podczas ladowania poziomu z pliku liczy jednostki wymagajace zaimplementowania kolizjii i dodaje je do ColliderTab */
	bool loadLevelToTab(const std::string& directory, unsigned int tabSize);
	/* Wczytywanie obrazku odpowiedzialnego za tlo planszy*/
	bool loadBackground(const std::string& texture);

public:
	Map(unsigned int sizeParam, const std::string& lvlDirectory);
	
	sf::Vector2f getSize() const;
	/* metoda zwracajaca informacje czy postac ma kolizje z ktora z platform */
	bool wall(Character* character) const;
	/* sprawdzanie kolizji miedzy postaciami w grze a mapa */
	bool checkCollision(sf::Vector2f direction, Character* character) const;
	/* Sprawdzanie kolizji pociskow z elementami otoczenia */
	bool checkBulletCollision(sf::Vector2f direction, Bullet* bullet) const;
	/* Sprawdzanie czy postac znajduje sie w obszarze planszy */
	bool checkPosition(Character* character);
	
	/* Metody jeszcze nie zaimplementowane */
	//bool openBox(Character* player);
	//bool thereIsALadder(Character* player);
	
	void draw(sf::RenderTarget& target, sf::RenderStates) const;

	~Map();
};
