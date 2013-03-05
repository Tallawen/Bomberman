#include "Collectible.h"

Collectible::Collectible(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	layer = EntityLayer::layer_background3;

	firstPosition = _position;

	offsetTime = 0.0f;
	offsetSign = -1.0f;

	blinking = false;
	blinkingValue = 255.0f;

	type = EntityType::collectible;
}

void Collectible::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);

	Window::instance()->drawHitbox(getHitbox(), sf::Color::Magenta);
}

void Collectible::update(float dt) {
	if(!blinking)
		move(dt, Constants::Collectible::MOVE_TIME, Constants::Collectible::MOVE_DISTANCE);

	else {
		move(dt, Constants::Collectible::MOVE_TIME, 30);
		blink(dt);
	}

}

void Collectible::move(float dt, float time, float distance) {
	if(offsetTime > time && offsetSign == -1.0f)
		offsetSign = 1.0f;

	if(offsetTime > time * 2 && offsetSign == 1.0f) {
		offsetTime = 0.0f;
		offsetSign = -1.0f;

		sprite.SetPosition(firstPosition);
	}

	position.y += distance * offsetSign / time * dt;
	sprite.SetPosition(position);

	offsetTime += dt;
}

void Collectible::blink(float dt) {
	if(blinkingValue <= 0.0f) {
		isDead = true;
	  return;
	}

	blinkingValue += -1 * 255 / Constants::Collectible::BLINK_TIME * dt;

	sprite.SetColor(sf::Color(255, 255, 255, blinkingValue));
}

void Collectible::remove() {
	type = EntityType::none;

	blinking = true;

	offsetTime = 0.0f;
	offsetSign = -1.0f;
}
