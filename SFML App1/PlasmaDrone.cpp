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
	return 1;
}

void PlasmaDrone::createBullets()
{
	//Bullet* tmp = nullptr;
	for (int i = 0; i < 5; i++) {
		Bullet tmp (sf::Vector2f(2000, 2000));//, texture[0]);
	//	tmp->setIntRect(sf::IntRect(0, 0, 64, 64));
		//tmp->setSize(32);
		//bullets.push_back(tmp);
	}
}

void PlasmaDrone::levelUp(int round)
{
	setHealth(getHealth() +  (float)round * 0.1f * getHealth() / 5.f);
	strength += round * 0.1f * strength;
}
void PlasmaDrone::draw(sf::RenderTarget& target, sf::RenderStates state){
	target.draw(sprite);
	/*for (auto &elem : bullets) {
		if (!elem->getCooldown().elapsed())
			target.draw(*elem);
	}*/
}
void PlasmaDrone::reset() {
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
PlasmaDrone::PlasmaDrone(std::vector<std::unique_ptr<PlasmaBullet>>& bullets) : bullets(bullets)
{
	try {
		std::vector<std::string> fileNames = { "images/PlasmaDrone/explode_sheet.png","images/PlasmaDrone/fire_sheet.png","images/PlasmaDrone/idle_sheet.png" };
		loadTextures(fileNames);
		state = static_cast<utils::PlasmaDroneState>(1);
		changeDirectionX = false;
		changeDirectionY = false;
		//createBullets();
		velocity.y = 4.0;
		sprite.setSize(sf::Vector2f(91, 92));
		sprite.setPosition(sf::Vector2f(100, 100));
		sf::IntRect rect(0, 0, 91, 92);
		sprite.setTextureRect(rect);
		animation.setRect(rect);
		sprite.setTexture(&texture[2]);
		sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
		setHealth(1000);

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

bool PlasmaDrone::refresh(Player* player, bool wall) {

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

		if (sprite.getPosition().x <= 16 ) changeDirectionX = true;
		else if (sprite.getPosition().x >= 1264) changeDirectionX = false;

		if (sprite.getPosition().y >= 1080 || wall) changeDirectionY = true;
		else if (sprite.getPosition().y <= 16) changeDirectionY = false;

		
		setSpeed(3.f);
		animation.setAnimTime(sf::seconds(0.125));
		
		/* Sekcja odpowiedzialna za strzelanie drona */
		if ((abs(player->getPosition().x - getPosition().x)) <= 520) {
			if (sprite.getSize().x != 128) // FIREs
				prepareToFire();
			animation.changeMove(128, 0, 128 * 20, 0, sprite);
			for(auto &bullet : bullets){
				if (bullet->getCooldown().elapsed()) {
					bullet->countDirection(this, player);
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