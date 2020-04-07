#include "Soldier.h" 

Soldier::Soldier(std::vector<std::string>& textures) : Enemy(2.5f, 4.5f)
{
	try {
		loadTextures(textures);
		bullet = nullptr;
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
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

void Soldier::addAmmunition(Bullet& bullet) {
	this->bullet = &bullet;
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

bool Soldier::refresh(const Player& player, bool wall) {
	bool changed = false;	
	if (getHealth() > 0) {
		// AI SECTION
		if (velocity.y != 0.0f) {
			setOnAir(true);
			setCanJump(false);
			sprite.setTexture(&texture[2]);
			jump();
			changed = true;
		}
		else if (getCanJump()) {
			if (getCanJump()) {
				if (wall) {
					if (!changed) {
						sprite.setTexture(&texture[2]);
						changed = true;
					}
					jump();
				}
				else if ((abs(player.getPosition().x - getPosition().x) < 30 && (player.getPosition().y < getPosition().y))) {
					if (!changed) {
						sprite.setTexture(&texture[2]);
						changed = true;
					}
					jump();
				}
			}

		}

		if (player.getPosition().x >= getPosition().x) {
			velocity.x++;
			sprite.setTexture(&texture[1]);
			changed = true;
			animation.rotateSprite(sprite, 'r');
			moveRight();
		}
		else if (player.getPosition().x < getPosition().x) {
			velocity.x--;
			sprite.setTexture(&texture[1]);
			changed = true;
			animation.rotateSprite(sprite, 'l');
			moveLeft();
		}
		else if (velocity.x == 0 && velocity.y == 0) {
			sprite.setTexture(&texture[0]);
			changed = true;

		}	


		/*SEKCJA STRZELANIA*/
		if ((abs(player.getPosition().x) - abs(getPosition().x)) >= -400 && (abs(player.getPosition().x) - abs(getPosition().x)) <= 400) {
			if (bullet->getCooldown().elapsed()) {
				bullet->restart(getPosition());
				bullet->setDirection(this);
			}
		}
		//else bullet->refresh();



		//velocity.x = 0.0f;
		velocity.y += 0.9810f * 1.0f;	
		sprite.move(velocity.x, velocity.y);

		if (velocity.y > 17.0f) {
			velocity.y = 9.81 * 1.6f;
		}
		return 1;
	}
	else {
		sprite.setTexture(&texture[3]);
		velocity.x *= 0.97;
		velocity.y += 0.9810f * 2.5f;
		sprite.move(velocity.x, velocity.y);
		if (velocity.y > 17.0f) {
			velocity.y = 9.81 * 1.6f;
		}
		return animation.death(sprite, velocity);

	}

}

Soldier::~Soldier() {
	bullet = nullptr;
}																	 