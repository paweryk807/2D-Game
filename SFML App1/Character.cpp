#include "Character.h"

Character::Character() {
	try {
		sprite.setSize(sf::Vector2f(32.0f, 32.0f));
		sprite.setOrigin(sprite.getSize() / 2.0f);
		sprite.setPosition(600, 350);  
		velocity = sf::Vector2f(0.0f, 0.0f);
		//animation.setAnimTime(sf::seconds(0.125));  
		health = 100.0;
		speed = 2.20;
		jumpHeight = 10.20;
		canJump = true;
		onAir = false;
		canClimb = false;
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
}

Character::~Character() {}

//sf::IntRect Character::getIntRect() {
//	return animation.getRect();
//}

bool Character::getCanClimb() {
	return canClimb;
}

float Character::getHealth() {
	return health;
}

void Character::reset() {
	sprite.setPosition(600, 350);
	health = 100.0;
	//speed = 2.20;
	//jumpHeight = 10.20;
	canJump = true;
	onAir = false;
	canClimb = false;
}

bool Character::getCanJump() {
	return canJump;
}

bool Character::getOnAir() {
	return onAir;
}

float Character::getJumpHeight() {
	return jumpHeight;
}

sf::Vector2f Character::getVelocity() {
	return velocity;
}

void Character::setSprite(sf::RectangleShape& sprite) {
	this->sprite = sprite;
}

//CharacterAnimation Character::getAnimation() {
//	return animation;
//}

float Character::getSpeed() {
	return speed;
}

void Character::setJumpHeight(float height){
	if (height >= 0) {
		jumpHeight = height;
	}
	else {
		jumpHeight = 0.0;
	}
}

void Character::setCanClimb(bool climb) {
	canClimb = climb;
}

void Character::setHealth(float hp) {
	if (hp >= 0) {
		health = hp;
	}
	else {
		health = 0;
	}
}

void Character::setCanJump(bool jump) {
	canJump = jump;
}

void Character::setOnAir(bool air) {
	onAir = air;
}

sf::RectangleShape Character::getSprite() const {
	return sprite;
}

void Character::moveUp() {
	velocity.y = -speed;
}

void Character::jump() {
	if (canJump) {
		velocity.y = -sqrtf(2.0f * 9.81f * jumpHeight);
		canJump = false;
	}	
}

void Character::moveDown() {
	velocity.y = speed;
}

void Character::moveRight() {
	velocity.x = speed;
}

void Character::moveLeft() {
	velocity.x = -speed;
}

void Character::refresh() {
	
	sprite.move(velocity.x, velocity.y);

	if(velocity.y  != 0.0f ) {
		onAir = true;
		canJump = false;
	}

	velocity.x = 0.0f;
	velocity.y += 0.9810f * 1.0f;
	if (velocity.y > 17.0f) {
		velocity.y = 9.81f;
	}	
}

void Character::onCollision(sf::Vector2f direction) {
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;

	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		onAir = false;
		canJump = true;

	}
	else if (direction.y > 0.0f) {
		velocity.y = 0.0f;
	}
}
void Character::setSpeed(float temp) //Sprint Speed
{
	speed = temp;
   // animation.setAnimTime(tempAnim);
}

void Character::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

/*
void Character::setAnimation(CharacterAnimation& a) {
	animation = a;
}*/


void Character::correctPosition(sf::Vector2f size) {
	int x = getPosition().x;
	int y = getPosition().y;
	if (x < 0) {
		sprite.setPosition(0, y);
	}
	else if (x > size.x) {
		sprite.setPosition(size.x, y);
	}
	if(y < 0) {
		sprite.setPosition(sprite.getPosition().x, 0);
	}
	else if(y > size.y) {
		sprite.setPosition(sprite.getPosition().x, size.y);
	}
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite);
}

Collider Character::getCollider() {
	return Collider(sprite);
}

sf::Vector2f Character::getPosition() const {
	return sprite.getPosition();
}