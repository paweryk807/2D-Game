#include "Soldier.h" 

Soldier::Soldier(std::vector<std::string>& textures)
{
	try {
		loadTextures(textures);
		bullet = nullptr;
		sf::IntRect r(48, 0, 48, 48);
		animation.setRect(r);
		animation.setAnimTime(sf::seconds(0.075));

		sprite.setSize(sf::Vector2f(48.0f, 48.0f));
		sprite.setOrigin(32.0f / 2.0f, 30.0f / 2.0f);  // Aby nie bylo odstepow od podloza
		sprite.setTexture(&texture[0]);
		sprite.setTextureRect(animation.getRect());
		sprite.setPosition(800, 350);

		velocity = sf::Vector2f(0.0f, 0.0f);

		strength = 20.0f;
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


void Soldier::setStrength(float str) {
	if (str > 0) {
		strength = str;
	}
	else {
		strength = 0;
	}
}

float Soldier::getStrength() {
	return strength;
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
		animation.changeMove(48, 0, 6 * 48, 0, sprite);
	}
}

void Soldier::moveLeft() {
	velocity.x = -getSpeed();
	if (!getOnAir()) {
		animation.changeMove(48, 0, 6 * 48, 0, sprite);
	}
}

void Soldier::idle() {
	if (!getOnAir()) {
		animation.changeMove(48, 0, 5 * 48, 0, sprite);
	}
}

void Soldier::jump() {
	if (getCanJump()) {
		velocity.y = -sqrtf(2.0f * 9.81f * getJumpHeight());
		animation.jump(48, 0, 48, 0, sprite, velocity);
	}
}

void Soldier::setSpeed(float temp, sf::Time tempAnim) //Sprint Speed
{
	Character::setSpeed(temp);
	animation.setAnimTime(tempAnim);
}

void Soldier::setAnimation(CharacterAnimation& a) {
	animation = a;
}

void Soldier::levelUp(int round)
{
	setHealth(getHealth() + round * 0.15 * getHealth() / 5);
	strength += round * 0.15 * strength / 8;
}

bool Soldier::refresh(const Player& player, bool wall) {
	//sprite.setPosition(colid.getPosition());
	bool changed = false;
	if (getHealth() > 0) {
		// AI SECTION
		if (getPosition().x < 0)
			correctPosition(sf::Vector2f(5.1f, sprite.getPosition().y));
		else if (getPosition().x > 1280) 
			correctPosition(sf::Vector2f(1274.1f, sprite.getPosition().y));
		if (getPosition().y > 1070)
				correctPosition(sf::Vector2f(getPosition().x, player.getPosition().y));
		else if (getPosition().y < 0)
				correctPosition(sf::Vector2f(getPosition().x, 5.f));

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

		if (player.getPosition().x - 1 >= getPosition().x) {
			velocity.x++;
			sprite.setTexture(&texture[1]);
			changed = true;
			animation.rotateSprite(sprite, 'r');
			moveRight();
		}
		else if ((player.getPosition().x + 1) < getPosition().x) {
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
		setSpeed(2.f, sf::seconds(2.2 * 0.125));


		/*SEKCJA STRZELANIA*/
		if ((abs(player.getPosition().x) - abs(getPosition().x)) >= -400 && (abs(player.getPosition().x) - abs(getPosition().x)) <= 400) {
			if (bullet->getCooldown().elapsed()) {
				bullet->restart(getPosition());
				bullet->setDirection(this);
			}
		}

		velocity.y += 0.9810f * 1.0f;	
		sprite.move(velocity.x, velocity.y);
		velocity.x = 0.0f;
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
		return 	animation.death(48, 0, 8 * 48, 0, sprite, velocity);

	}

}

Soldier::~Soldier() {
	bullet = nullptr;
}																	 