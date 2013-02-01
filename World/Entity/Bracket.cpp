#include "Bracket.h"

Bracket::Bracket(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("Bracket");
	sp = Sprite::instance()->getSpriteData("Bracket");
	sprite.SetPosition(info.position);
}

void Bracket::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	//Window::instance()->drawAabb(Aabb(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y)), sf::Color::Green);
}
