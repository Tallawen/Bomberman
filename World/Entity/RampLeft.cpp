#include "RampLeft.h"

RampLeft::RampLeft(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("RampLeft");
	sprite.SetPosition(info.position);
}

void RampLeft::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
}
