#include "Entity.h"
Entity::Entity(float x, float y, float defVelocityX, float defVelocityY, std::queue<Entity*> *_entitiesToCreate) {
	entitiesToCreate = _entitiesToCreate;

	layer = EntityLayer::layer_background6;

	setPosition(x, y);
	setVelocity(0, 0);

	defaultVelocity = sf::Vector2f(defVelocityX, defVelocityY);

	isDead = false;

	left  = nullptr;
	right = nullptr;
	top   = nullptr;
	down  = nullptr;
	stop  = nullptr;

	state = EntityState::stand;

	setDefaultMovement();
}

void Entity::update(float dt) {


}

void Entity::draw(float dt) {


}
