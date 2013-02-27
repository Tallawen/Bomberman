#include "Entity.h"
Entity::Entity(float x, float y, float defVelocityX, float defVelocityY, std::queue<Entity*> *_entitiesToCreate) {
	entitiesToCreate = _entitiesToCreate;

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
	setDefaultMovement();
	//CheckCollisionsWithLevel(dt, level);

	sf::Vector2f nextPosition = getNextPosition(dt);

	if(nextPosition.x < position.x && canGoLeft)
		position.x = nextPosition.x;

	else if(nextPosition.x > position.x && canGoRight)
		position.x = nextPosition.x;

	if(position.x < 1)
		position.x = 1;

	// ustal stan ruchu gracza na podstawie prędkości
	if(fabsf(velocity.x) < 0.001) {
		state = EntityState::stand;
		velocity.x = 0;

	} else if (velocity.x > 0.0)
		state = EntityState::goRight;

	else
		state = EntityState::goLeft;

	// uaktualnij animację
	switch (state) {
	    case EntityState::stand:

	        break;

	    case EntityState::goLeft:
	    	left->process(dt);
	      break;

	    case EntityState::goRight:
	        right->process(dt);
	      break;

	    default:

	      break;
	}
}

void Entity::draw(float dt) { }
