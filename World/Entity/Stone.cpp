#include "Stone.h"

Stone::Stone(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("Stone");
	sp = Sprite::instance()->getSpriteData("Stone");
	sprite.SetPosition(info.position);
}

void Stone::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Cyan);
//	Window::instance()->drawHitbox(Hitbox(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y)), sf::Color::Green);
}

Hitbox Stone::getHitbox() const {
	return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
