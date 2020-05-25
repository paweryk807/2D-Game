#include "TileMap.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(vertices, states);
}

bool TileMap::load(const std::string& tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width, unsigned int height) {
	if (!tileset.loadFromFile(tileSet)) {
		throw std::exception("TileSet file error");
		return false;
	}

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize((int)(width * height * 4));

	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++) {
			unsigned int tileNumber = tiles[i + j * width];
			unsigned int tu = tileNumber % (tileset.getSize().x / tileSize.x);
			unsigned int tv = tileNumber / (tileset.getSize().x / tileSize.x);

			sf::Vertex* quad = &vertices[(int)(((i + j * width) * 4))];

			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}