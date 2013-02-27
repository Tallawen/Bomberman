#include "Stone.h"

Stone::Stone(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	sprite = SpriteManager::instance()->getSprite("game.stone");
	sd = SpriteManager::instance()->getSpriteData("game.stone");

	sprite.SetPosition(position);
}

void Stone::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Cyan);
}
