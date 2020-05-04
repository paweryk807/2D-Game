#include "PlasmaDrone.h"


bool PlasmaDrone::loadTextures(std::vector<std::string>& textures)
{
	for (auto elem : textures) {
		sf::Texture tmp;
		if (!tmp.loadFromFile(elem)) {
			throw std::exception("PlasmaDrone Texture error!");
			break;
		}
		texture.push_back(sf::Texture(tmp));
	}
}

void PlasmaDrone::createBullets()
{
	for (int i = 0; i < 5; i++) {
		Bullet tmp(sf::Vector2f(2000, 2000), texture[0]);
		tmp.setIntRect(sf::IntRect(0, 0, 64, 64));
		tmp.setSize(32);
		
	}
}

void PlasmaDrone::levelUp(int round)
{
	setHealth(getHealth() + round * 0.1 * getHealth() / 5);
	strength += round * 0.1 * strength;
}
void PlasmaDrone::draw(sf::RenderTarget& target, sf::RenderStates state){
	target.draw(sprite);
	//for (auto elem : bullets) {
	//	if (!elem.getCooldown().elapsed())
	//		target.draw(elem);
	//}
}
/*
Collider PlasmaDrone::getCollider() {
	sf::Sprite tmp;
	switch (state) {
	case utils::PlasmaDroneState::fire:
		return sprite;
		break;
	case utils::PlasmaDroneState::fly:
		break;
	case utils::PlasmaDroneState::explode:
		break;

	}
}
*/
PlasmaDrone::PlasmaDrone()
{
	try {
		std::vector<std::string> fileNames = { "images/PlasmaDrone/ball_sheet.png", "images/PlasmaDrone/explode_sheet.png","images/PlasmaDrone/fire_sheet.png","images/PlasmaDrone/idle_sheet.png" };
		loadTextures(fileNames);
		state = static_cast<utils::PlasmaDroneState>(1);
		changeDirectionX = false;
		changeDirectionY = false;
		createBullets();
		velocity.y = 4.0;
		sprite.setSize(sf::Vector2f(92, 92));
		sprite.setPosition(sf::Vector2f(100, 100));
		sf::IntRect rect(0, 0, 92, 92);
		sprite.setTextureRect(rect);
		animation.setRect(rect);
		sprite.setTexture(&texture[3]);
		sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
		setHealth(1000);

	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
}

void PlasmaDrone::prepareToFly() {
	state = utils::PlasmaDroneState::fly;
	sprite.setTexture(&texture[3]);
	sprite.setSize(sf::Vector2f(92, 92));
	sf::IntRect rect(0, 0, 92, 92);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);

}

void PlasmaDrone::prepareToExplode() {
	state = utils::PlasmaDroneState::explode;
	sprite.setSize(sf::Vector2f(192, 204));
	sprite.setTexture(&texture[1]);
	sf::IntRect rect(0, 0, 192, 204);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);

}

void PlasmaDrone::prepareToFire() {
	state = utils::PlasmaDroneState::fire;
	sprite.setTexture(&texture[2]);
	sprite.setSize(sf::Vector2f(128, 128));
	sf::IntRect rect(0, 0, 128, 128);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);

}

bool PlasmaDrone::refresh(const Player& player, bool wall) {
	//sprite.setPosition(colid.getPosition());
	bool changed = false;
	for (auto& elem : bullets) {
		refresh(player, false);
	}
	if (getHealth() > 0) {
		// AI SECTION
		//velocity.x--;

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

		if (sprite.getPosition().x <= 16 ) changeDirectionX = true;
		else if (sprite.getPosition().x >= 1264) changeDirectionX = false;

		if (sprite.getPosition().y >= 1080 || wall) changeDirectionY = true;
		else if (sprite.getPosition().y <= 16) changeDirectionY = false;

		animation.changeMove(92, 0, 24 * 92, 0, sprite);

		/*
		if (player.getPosition().x - 1 >= getPosition().x) {

			velocity.x++;
			changed = true;
			animation.rotateSprite(sprite, 'l');
		//	moveRight();
		}
		else if ((player.getPosition().x + 1) < getPosition().x) {
			velocity.x--;
			sprite.setTexture(&texture[1]);
			changed = true;
			animation.rotateSprite(sprite, 'r');
		//	moveLeft();
		}
		else if (velocity.x == 0 && velocity.y == 0) {
			sprite.setTexture(&texture[0]);
			changed = true;

		}*/
		setSpeed(3.f);
		animation.setAnimTime(sf::seconds(0.125));
		sprite.move(velocity.x, velocity.y);
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		/*/*SEKCJA STRZELANIA
		if ((abs(player.getPosition().x) - abs(getPosition().x)) >= -520 && (abs(player.getPosition().x) - abs(getPosition().x)) <= 520) {
			if (sprite.getSize().x != 128) // FIRE
				prepareToFire();

			animation.changeMove(128, 0, 128 * 20, 0, sprite);
			for(auto &bullet : bullets)
				if (bullet.getCooldown().elapsed()) {
					bullet.restart(getPosition());
					bullet.setDirection(this);
				}
		}
		else if (sprite.getSize().x != 92) { // IDLE
				prepareToFly();
			animation.changeMove(92, 0, 24 * 92, 0, sprite);
		}
		//velocity.y += 0.9810f * 1.0f;
		sprite.move(velocity.x, velocity.y);
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		//velocity.y = 0.0f;
		//if (velocity.y > 17.0f) {
		//	velocity.y = 9.81 * 1.6f;
		//}*/
		return 1;
	}
	else {
		if (sprite.getSize().x != 192) // EXPLODE
			prepareToExplode();
		velocity.x *= 0.97;
		velocity.y += 0.9810f * 2.5f;
		sprite.move(velocity.x, velocity.y);
		if (velocity.y > 17.0f) {
			velocity.y = 9.81 * 1.6f;
		}
		return animation.death(192, 192, 6 * 192, 0, sprite, velocity);
	}

}