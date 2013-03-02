#include "Avatar.h"

Avatar::Avatar(sf::Vector2f _position) {
	sprite = SpriteManager::instance()->getSprite("ui.white_avatar");
	sd = SpriteManager::instance()->getSpriteData("ui.white_avatar");

	position = _position;

	sprite.SetCenter(0, 0);

	sprite.SetPosition(position);
}

void Avatar::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
}
