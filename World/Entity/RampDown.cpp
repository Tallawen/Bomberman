#include "RampDown.h"

RampDown::RampDown(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("RampDown");
	sprite.SetPosition(info.position);
}

void RampDown::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Blue);
}

Hitbox RampDown::getHitbox() const {
	return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
