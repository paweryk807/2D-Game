#include "Collider.h" 

Collider::Collider(sf::RectangleShape& body) : body(body) {
   // this->body.setOrigin(body.getOrigin().x, body.getOrigin().y - 3);
}

	Collider::~Collider() {	

	}

		bool Collider::checkCollisionY(Collider other) {
		sf::Vector2f otherPos = other.getPosition();
		sf::Vector2f otherHalfSize = other.getHalfSize();
		sf::Vector2f thisPos = getPosition();
		sf::Vector2f thisHalfSize = getHalfSize();

		float deltaY = otherPos.y - thisPos.y;
		
		float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);// -0.5f;

		if (intersectionY < 0.0)
			return true;
		else return false;
	}

	bool Collider::checkCollisionX(Collider other) {
        sf::Vector2f otherPos = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPos = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x); //+12.5f;  // +12.5 aby zniwelowac wolne miejsce w teksturach :slight_smile: 
        float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);// +0.5f;

        if (intersectionX < 0.0f && intersectionY < 0.0f) {
            return true;
        }
        else return false;
	}
   
	bool Collider::checkCollision(Collider other, sf::Vector2f& direction, float push) {
        sf::Vector2f otherPos = other.getPosition();
        sf::Vector2f otherHalfSize = other.getHalfSize();
        sf::Vector2f thisPos = getPosition();
        sf::Vector2f thisHalfSize = getHalfSize();

        float deltaX = otherPos.x - thisPos.x;
        float deltaY = otherPos.y - thisPos.y;

        float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x) + 12.5f;  // +12.5 aby zniwelowac wolne miejsce w teksturach :slight_smile: 
        float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);// -0.5f;

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
