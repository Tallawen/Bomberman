#include "RampLeft.h"

RampLeft::RampLeft(int _id, sf::Vector2f _position) {
	info.id = _id;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("RampLeft");
	sprite.SetPosition(info.position);
}

void RampLeft::draw(float dt) {
	sf::Sprite shadow = Sprite::instance()->getSprite("Shadow");
	shadow.SetPosition(info.position.x+sprite.GetSize().x, info.position.y-1);

	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->getRW()->Draw(shadow);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Blue);
}

Hitbox RampLeft::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
