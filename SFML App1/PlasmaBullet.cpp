#include "PlasmaBullet.h"

PlasmaBullet::PlasmaBullet(sf::Vector2f pos, float seconds)
{
	texture.loadFromFile("images/PlasmaDrone/ball_sheet.png");
	sprite.setTexture(&texture);
	sf::IntRect rect(0, 0, 64, 64);

	sprite.setTextureRect(rect);
	sprite.setRadius(24);
	sf::Time  cooldownTime = sf::seconds(seconds);
	cooldown.setCooldown(cooldownTime);

	sf::Time perFrame = sf::seconds(seconds / 8);
	animation.setAnimTime(perFrame);

	animation.setRect(rect);
	sprite.setPosition(pos.x, pos.y);
	sf::Vector2f cSize(sprite.getRadius() / 2, sprite.getRadius() / 2);

	colid.setSize(cSize);
	colid.setPosition(pos.x, pos.y);
	colid.setOrigin(cSize / 2.0f);
}

void PlasmaBullet::countDirection(Character* shooter, Character* target)
{
	sf::Vector2f shooterPosition = shooter->getPosition();
	sf::Vector2f targetPosition = target->getPosition();
	
	float deltaX = abs(targetPosition.x - shooterPosition.x);
	float deltaY = abs(targetPosition.y - shooterPosition.y);
	if (deltaX > 100 && deltaY > 100) {
		velocity.x = (targetPosition.x - shooterPosition.x) * 0.0125;
		velocity.y = (targetPosition.y - shooterPosition.y) * 0.0125;
	}
	else {
		velocity.x = (targetPosition.x - shooterPosition.x) * 0.05;
		velocity.y = (targetPosition.y - shooterPosition.y) * 0.05;
	}
}

void PlasmaBullet::restart(sf::Vector2f pos) {
	sf::IntRect rect(0, 0, 64, 64);
	sprite.setTextureRect(rect);
	animation.setRect(rect);
	animation.restartCooldown();
	Bullet::restart(pos);
}

void PlasmaBullet::refresh() {
	sf::Time control = sf::seconds(0.5);
	if (cooldown.getTime() - cooldown.getClock().getElapsedTime() < control)
		animation.changeMove(64, 0, 4 * 64, 0, sprite);
	else if (animation.changeMove(4 * 64, 0, 8 * 64, 0, sprite))
		sprite.setPosition(2000, 2000);
	Bullet::refresh();
}

//Collider PlasmaBullets::getCollider() {
//	colid.setPosition(sprite.getPosition());
//	return Collider(colid);
//}