#include "Box.h"

Box::Box(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	sprite = SpriteManager::instance()->getSprite("game.box");
	sd = SpriteManager::instance()->getSpriteData("game.box");

	sprite.SetPosition(position);
}

void Box::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getNextHorizontalHitbox(dt), sf::Color::Blue);
}

