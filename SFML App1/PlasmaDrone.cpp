#include "PlasmaDrone.h"

void PlasmaDrone::levelUp(int round) {
	setHealth(getHealth() + (float)round * 0.1f * getHealth() / 5.f);
	strength += round * 0.1f * strength;
}
void PlasmaDrone::draw(sf::RenderTarget& target, sf::RenderStates state) {
	target.draw(sprite);
}
void PlasmaDrone::reset() {
	/*
		Do zaimplementowania gdyby dron musial zmienic parametry na domyslne
	*/
}

PlasmaDrone::PlasmaDrone(std::vector<std::unique_ptr<PlasmaBullet>>& bullets, std::vector<sf::Texture>& textures) : bullets(bullets), texture(textures) {
	try {
		state = static_cast<utils::PlasmaDroneState>(1);
		changeDirectionX = false;
		changeDirectionY = false;
		velocity.y = 4.0;
		sprite.setSize(sf::Vector2f(91, 92));
		sprite.setPosition(sf::Vector2f(-100 + utils::randomFloat(-20,0), -5));
		sf::IntRect rect(0, 0, 91, 92);
		sprite.setTextureRect(rect);
		animation.setRect(rect);
		sprite.setTexture(&texture[2]);
		sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
		setHealth(1000);
		strength = 1;
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
}

void PlasmaDrone::prepareToFly() {
	state = utils::PlasmaDroneState::fly;
	sprite.setTexture(&texture[2]);
	sprite.setSize(sf::Vector2f(91, 92));
	sf::IntRect rect(0, 0, 91, 92);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}

void PlasmaDrone::prepareToExplode() {
	state = utils::PlasmaDroneState::explode;
	sprite.setSize(sf::Vector2f(192, 204));
	sprite.setTexture(&texture[0]);
	sf::IntRect rect(0, 0, 192, 204);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}

void PlasmaDrone::prepareToFire() {
	state = utils::PlasmaDroneState::fire;
	sprite.setTexture(&texture[1]);
	sprite.setSize(sf::Vector2f(128, 128));
	sf::IntRect rect(0, 0, 128, 128);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}

bool PlasmaDrone::refresh(Player& player, bool wall) {
	bool alive = true;

	if (getHealth() > 0) {
		/* Sekcja odpowiedzialna za poruszanie sie po planszy*/
		if (sprite.getSize().x != 92)  // IDLE
			prepareToFly();
		if (!changeDirectionY)
			velocity.y = getSpeed();
		else velocity.y = -getSpeed();

		if (changeDirectionX) { //&& sprite.getPosition().x <= 1264) { // w prawo
			animation.rotateSprite(sprite, 'l');
			velocity.x = getSpeed();
		}
		else {
			animation.rotateSprite(sprite, 'r');
			velocity.x = -getSpeed();
		}

		if (sprite.getPosition().x <= 16) changeDirectionX = true;
		else if (sprite.getPosition().x >= 1264) changeDirectionX = false;

		if (sprite.getPosition().y >= 1080 || wall) changeDirectionY = true;
		else if (sprite.getPosition().y <= 16) changeDirectionY = false;

		setSpeed(3.f);
		animation.setAnimTime(sf::seconds(0.125));

		/* Sekcja odpowiedzialna za strzelanie drona */
		if ((abs(player.getPosition().x - getPosition().x)) <= 520) {
			if (sprite.getSize().x != 128) // FIREs
				prepareToFire();
			animation.changeMove(128, 0, 128 * 20, 0, sprite);
			for (auto& bullet : bullets) {
				if (bullet->getCooldown().elapsed()) {
					bullet->countDirection(this, &player);
					bullet->restart(getPosition());
				}
			}
		}
		else if (sprite.getSize().x != 91) { // IDLE
			prepareToFly();
		}

		if (sprite.getSize().x == 91)
			animation.changeMove(91, 0, 24 * 91, 0, sprite);
		sprite.move(velocity.x, velocity.y);
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		return 1;
	}
	else {
		/* Sekcja odpowiedzialna za wybuch drona */
		if (sprite.getSize().x != 192) // EXPLODE
			prepareToExplode();
		velocity.x *= 0.57f;
		velocity.y += 0.9810f * 2.5f;
		sprite.move(velocity.x, velocity.y);
		if (velocity.y > 17.0f) {
			velocity.y = 9.81f * 1.6f;
		}
		alive = (getHealth() > 0) || animation.death(192, 0, 6 * 192, 0, sprite, velocity);
		if (!alive) sprite.setPosition(2000, 2000);
		return alive;
	}
}