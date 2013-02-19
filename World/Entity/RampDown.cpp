#include "RampDown.h"

RampDown::RampDown(int _id, sf::Vector2f _position) {
	info.id = _id;
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
