#include "Soldier.h" 

Soldier::Soldier(std::vector<std::string>& textures) : Enemy(2.5f, 4.5f)
{
	//for (auto elem : textures) {
	//	texture.push_back(elem);
	//}	

	loadTextures(textures);

	sf::IntRect r(48, 0, 48, 48);
	animation.setRect(r);
	animation.setAnimTime(sf::seconds(0.075));

	sprite.setSize(sf::Vector2f(48.0f, 48.0f));
	sprite.setOrigin((sprite.getSize().x - 16) / 2.0f, (sprite.getSize().y - 16.0f) / 2.0f);
	sprite.setTexture(&texture[0]);
	sprite.setTextureRect(animation.getRect());
	sprite.setPosition(800, 350);

	velocity = sf::Vector2f(0.0f, 0.0f);


	setHealth(100.0);
	setSpeed(2.f, sf::seconds(2.2 * 0.125));
	setJumpHeight(10.20);
	setCanJump(true);
	setOnAir(false);
	setCanClimb(false);


	/*try {
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}*/
}

bool Soldier::loadTextures(std::vector<std::string>& text) {
	for (auto elem : text) {
		sf::Texture tmp; 
		if (!tmp.loadFromFile(elem)) {
			throw std::exception("Soldier Texture error!");
			break;
		}
		texture.push_back(sf::Texture(tmp));
	}
}


void Soldier::moveRight() {
	velocity.x = getSpeed();
	if (!getOnAir()) {
		animation.oX(sprite);
	}
}

void Soldier::moveLeft() {
	velocity.x = -getSpeed();
	if (!getOnAir()) {
		animation.oX(sprite);
	}
}

void Soldier::idle() {
	if (!getOnAir()) {
		animation.idle(sprite);
	}
}

void Soldier::jump() {
	if (getCanJump()) {
		velocity.y = -sqrtf(2.0f * 9.81f * getJumpHeight());
		animation.jump(sprite, velocity);
	}
}

void Soldier::setSpeed(float temp, sf::Time tempAnim) //Sprint Speed
{
	Character::setSpeed(temp);
	animation.setAnimTime(tempAnim);
}

void Soldier::setAnimation(SoldierAnimation& a) {
	animation = a;
}

void Soldier::refresh(const Player& player, bool wall) {
	if (getHealth() > 0) {
		if (player.getPosition().x >= getPosition().x) {
			velocity.x++;
			sprite.setTexture(&texture[1]);
			animation.rotateSprite(sprite, 'r');
			moveRight();
		}
		else if (player.getPosition().x < getPosition().x) {
			velocity.x--;
			sprite.setTexture(&texture[1]);
			animation.rotateSprite(sprite, 'l');
			moveLeft();
		}
		else if (velocity.x == 0 && velocity.y == 0) {
			sprite.setTexture(&texture[0]);

		}
		Character::refresh();
		// AI SECTION
		if (wall) {
			sprite.setTexture(&texture[2]);
			jump();
		}
		else if ((abs(player.getPosition().x - getPosition().x) < 30 && (player.getPosition().y < getPosition().y))) {
			sprite.setTexture(&texture[2]);
			jump();
		}
	}
	else {
		sprite.setTexture(&texture[3]);
	}
}