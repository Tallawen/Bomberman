#include "RampRight.h"

RampRight::RampRight(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("RampRight");
	sprite.SetPosition(info.position);
}

void RampRight::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
}
