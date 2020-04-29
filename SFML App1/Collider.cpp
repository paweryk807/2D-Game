#include "Collider.h" 

    Collider::Collider(sf::RectangleShape& body) : body(body) {}

	Collider::~Collider() {	

	}

	bool Collider::checkCollision(Collider other, sf::Vector2f& direction, float push) {
        sf::Vector2f otherPos = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPos = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x); // +12.5f;  // +12.5 aby zniwelowac wolne miejsce w teksturach :slight_smile: 
        float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y); // +0.99;

        if (intersectionX < 0.0f && intersectionY < 0.0f) {
            push = std::min(std::max(push, 0.0f), 1.0f);

            if (intersectionX > intersectionY) {
                if (deltaX > 0.0f) {
                    move(intersectionX * (1.0f - push), 0.0f);
                    other.move(-intersectionX * push, 0.0f);

                    direction.x = 1.0f;
                    direction.y = 0.0f;
                }
                else {
                    move(-intersectionX * (1.0f - push), 0.0f);
                    other.move(intersectionX * push, 0.0f);

                    direction.x = -1.0f;
                    direction.y = 0.0f;
                }
            }
            else {
                if (deltaY > 0.0f) {
                    move(0.0f, intersectionY * (1.0f - push));
                    other.move(0.0f, -intersectionY * push);

                    direction.x = 0.0f;
                    direction.y = 1.0f;
                }
                else {
                    move(0.0f, -intersectionY * (1.0f - push));
                    other.move(0.0f, intersectionY * push);

                    direction.x = 0.0f;
                    direction.y = -1.0f;

                }
            }

            return true;
        }

        return false;
    }

    bool Collider::onCollision(Collider other) {
        sf::Vector2f otherPos = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPos = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        return (intersectionX < 0.0f && intersectionY < 0.0f);
    }

	sf::Vector2f Collider::getPosition() {
		return body.getPosition();
	}

	sf::Vector2f Collider::getHalfSize() {
		return (body.getSize() / 2.0f);
	}

	void Collider::move(float dx, float dy) {
		body.move(dx, dy);
	}

    void Collider::setBody(sf::RectangleShape sh) {
        body = sh;
    }

    sf::RectangleShape Collider::getBody() {
        return body;
    }

	void Collider::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
	}

    // MAP COLLIDER 

    MapCollider::MapCollider(sf::RectangleShape& body): Collider(body){ };


    bool MapCollider::checkCollision(Collider other, sf::Vector2f& direction, float push) {
        sf::Vector2f otherPos = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPos = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);// -8.f;  // +12.5 aby zniwelowac wolne miejsce w teksturach :slight_smile: 
            float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);// +4.f; // +0.99;

        if (intersectionX < 0.0f && intersectionY < 0.0f) {
            push = std::min(std::max(push, 0.0f), 1.0f);

            if (intersectionX > intersectionY) {
                if (deltaX > 0.0f) {
                    other.move(-intersectionX * push, 0.0f);

                    direction.x = 1.0f;
                    direction.y = 0.0f;
                }
                else {
                    other.move(intersectionX * push, 0.0f);

                    direction.x = -1.0f;
                    direction.y = 0.0f;
                }
            }
            else {
                if (deltaY > 0.0f) {
                    other.move(0.0f, -intersectionY * push);

                    direction.x = 0.0f;
                    direction.y = 1.0f;
                }
                else {
                    other.move(0.0f, intersectionY * push);

                    direction.x = 0.0f;
                    direction.y = -1.0f;

                }
            }

            return true;
        }

        return false;
    }

    bool MapCollider::wallCollision(Collider other) {
        float deltaX = other.getPosition().x - getPosition().x;
        float deltaY = other.getPosition().y - getPosition().y;

        float intersectionX = abs(deltaX) - (other.getHalfSize().x + getHalfSize().x);
        float intersectionY = abs(deltaY) - (other.getHalfSize().y + getHalfSize().y);

        return (intersectionX < 0.0f && intersectionY < 0.0f);
    }