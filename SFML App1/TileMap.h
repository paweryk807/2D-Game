#pragma once
#include<SFML/Graphics.hpp>
class TileMap : public sf::Drawable, public sf::Transformable {
	/* 
	Klasa bazowa mapy 
	przechowuje ona pojedyncze bloki 16x16, dzieki czemu mozna swobodnie wczytywac 
	tekstury z jednego pliku i dowolnie rozmieszczac je po ekranie 
	*/
	sf::Texture tileset;
	sf::VertexArray vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	bool load(const std::string& tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width, unsigned int height);
};
