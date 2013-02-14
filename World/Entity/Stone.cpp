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
	sf::Sprite shadow = Sprite::instance()->getSprite("Shadow");
	shadow.SetPosition(info.position.x + sp.dimensions.x, info.position.y-1);

	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->getRW()->Draw(shadow);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Cyan);
}

Hitbox Stone::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
