#pragma once
#include<SFML/Graphics.hpp>
class TileMap : public sf::Drawable, public sf::Transformable {
	sf::Texture tileset;
	sf::VertexArray vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	bool load(const std::string& tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width, unsigned int height);
};
