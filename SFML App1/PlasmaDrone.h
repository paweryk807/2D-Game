#pragma once
#include "Player.h"
#include "PlasmaBullet.h"

class PlasmaDrone : public Character {
	std::vector <std::unique_ptr<PlasmaBullet>>& bullets;
	std::vector<sf::Texture> texture;
	utils::PlasmaDroneState state;
	float strength;
	bool changeDirectionX;
	bool changeDirectionY;

	/* Metody odpowiedzialne za przestawienie parametrow postaci aby moc animowac (zmiana rozmiaru, textury) */
	void prepareToFly();
	void prepareToExplode();
	void prepareToFire();
	/* Wczytanie textur drona z plikow */
	bool loadTextures(std::vector<std::string>& textures);

public:
	PlasmaDrone(std::vector<std::unique_ptr<PlasmaBullet>>& bullets);
	/* Aktualizowanie postaci drona i jego AI */
	bool refresh(Player* player, bool wall);
	/* Inkrementowanie parametrow punktow zycia i sily postaci w zaleznosci od rundy gry przekazanej jako parametr */
	void levelUp(int round);

	void draw(sf::RenderTarget& target, sf::RenderStates state);
	/* Metoda ktora nie jest w tym momencie potrzebna do poprawnego dzialania drona 
	w momencie, gdyby powrot statystyk default'owych drona byl potrzebny nalezy zmodyfikowac jej cialo */
	void reset();
};