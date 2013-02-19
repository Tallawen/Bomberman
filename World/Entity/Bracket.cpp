#include "Bracket.h"

Bracket::Bracket(int _id, sf::Vector2f _position) {
	info.id = _id;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("newBracket");
	sd = Sprite::instance()->getSpriteData("newBracket");

	sprite.SetPosition(info.position);
}

void Bracket::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Blue);
}

Hitbox Bracket::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(51,-40));
}
