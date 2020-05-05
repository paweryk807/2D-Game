#include "PlasmaBullet.h"

PlasmaBullet::PlasmaBullet(sf::Vector2f pos)
{
	texture.loadFromFile("images/PlasmaDrone/ball_sheet.png");
	sprite.setTexture(&texture); 
	sf::IntRect rect(0, 0, 64, 64);

	sprite.setTextureRect(rect);
	sprite.setRadius(24);
	cooldown.setCooldown(sf::seconds(2.0));
	animation.setAnimTime(sf::seconds(0.24));
	animation.setRect(rect);
	sprite.setPosition(pos.x, pos.y);	
	sf::Vector2f cSize(sprite.getRadius(), sprite.getRadius());

	colid.setSize(cSize);
	colid.setPosition(pos.x, pos.y);
	colid.setOrigin(cSize / 2.0f);
}

void PlasmaBullet::countDirection(Character* shooter, Character* target)
{
	sf::Vector2f shooterPosition = shooter->getPosition();
	sf::Vector2f targetPosition = target->getPosition();

	velocity.x = (targetPosition.x - shooterPosition.x) / 65;
	velocity.y = (targetPosition.y - shooterPosition.y) / 65;

	if (abs(velocity.x) < 10) velocity.x * 3;
	if (abs(velocity.x) < 10) velocity.x * 3;
	if (abs(velocity.y) < 10) velocity.y * 3;
	if (abs(velocity.y) < 10) velocity.y * 3;
	
}

void PlasmaBullet::restart(sf::Vector2f pos) {
	animation.restartCooldown();
	Bullet::restart(pos);
}

void PlasmaBullet::refresh() {
	animation.changeMove(64, 0, 8 * 64, 0, sprite);
	Bullet::refresh();
}