#include "RampTop.h"

RampTop::RampTop(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("RampTop");
	sp = Sprite::instance()->getSpriteData("RampTop");
	sprite.SetPosition(info.position);
}

void RampTop::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Blue);
}

Hitbox RampTop::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
