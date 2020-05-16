#pragma once
#include <SFML\Graphics.hpp>
class Collider
{
	/*	
	Klasa odpowiedzialna za kolizje obiektow w grze
	*/
	sf::RectangleShape& body;
public:
	Collider() = default;

	Collider(sf::RectangleShape& body);

	~Collider();

	void move(float dx, float dy);

	void setBody(sf::RectangleShape sh);

	sf::RectangleShape getBody();

	void setPosition(sf::Vector2f pos);
	/* Metoda sprawdzajaca czy dwa obiekty ze soba nie koliduja, jesli tak to odpwiednio modeluje ich polozenie
	   Parametr push okresla sile z jaka obiekty maja na siebie oddzialywac */
	bool virtual checkCollision(Collider other, sf::Vector2f& direction, float push);
	/* Metoda informuje czy obiekty ze soba koliduja */
	bool onCollision(Collider other);

	sf::Vector2f getPosition();

	sf::Vector2f getHalfSize();
};

class MapCollider : public Collider {
	/*
	Klasa odpowiedzialna za kolizje z mapa w grze
	Nie oddzialuje ona na parametry takie jak polozenie fragmentow mapy
	*/	
public:

	MapCollider(sf::RectangleShape& body);
	/* Metoda sprawdza czy obiekt koliduje z mapa i odpowiednio modeluje jego polozenie */
	bool checkCollision(Collider other, sf::Vector2f& direction, float push) override;
	/* Metoda informuje czy obiekt koliduje z mapa */
	bool wallCollision(Collider other);
};