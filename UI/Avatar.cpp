#include "Avatar.h"

Avatar::Avatar(sf::Vector2f _position, bool black) {
	 std::string filename = "ui.white_avatar";
	if(black) filename = "ui.black_avatar";

	sprite = SpriteManager::instance()->getSprite(filename);
	sd = SpriteManager::instance()->getSpriteData(filename);

	position = _position;

	sprite.SetCenter(0, 0);

	sprite.SetPosition(position);
}

void Avatar::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
}
