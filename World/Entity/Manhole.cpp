#include "Manhole.h"

Manhole::Manhole(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	layer = EntityLayer::layer_background1;

	sprite = SpriteManager::instance()->getSprite("game.door_close");
	sd = SpriteManager::instance()->getSpriteData("game.door_close");

	sprite.SetPosition(position);

	type = EntityType::door_colse;
}

void Manhole::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Blue);
}

void Manhole::open() {
	type = EntityType::door_open;

	sprite = SpriteManager::instance()->getSprite("game.door_open");
	sd = SpriteManager::instance()->getSpriteData("game.door_open");

	sprite.SetPosition(position);
}


void Manhole::close() {
	type = EntityType::door_colse;

	sprite = SpriteManager::instance()->getSprite("game.door_close");
	sd = SpriteManager::instance()->getSpriteData("game.door_close");

	sprite.SetPosition(position);
}
