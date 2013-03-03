#include "Death.h"

Death::Death(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 50, 50, _entitiesToCreate) {
	sd = SpriteManager::instance()->getSpriteData("enemy.death_down");

	left = new Animation(
			SpriteManager::instance()->getSprite("enemy.death_left"),
			SpriteManager::instance()->getSpriteData("enemy.death_left"));

	right = new Animation(
			SpriteManager::instance()->getSprite("enemy.death_right"),
			SpriteManager::instance()->getSpriteData("enemy.death_right"));

	top = new Animation(
			SpriteManager::instance()->getSprite("enemy.death_top"),
			SpriteManager::instance()->getSpriteData("enemy.death_top"));

	down = new Animation(
			SpriteManager::instance()->getSprite("enemy.zombie_down"),
			SpriteManager::instance()->getSpriteData("enemy.zombie_down"));

	changeMovement();
}

void Death::draw(float dt) {
	switch(state) {
	    case EntityState::stand:

	      break;

	    case EntityState::goLeft:
	    	left->draw();
	      break;

	    case EntityState::goRight:
	    	right->draw();
	      break;

	    case EntityState::goTop:
	    	top->draw();
	      break;

	    case EntityState::goDown:
	    	down->draw();
	      break;
	}

	Window::instance()->drawHitbox(getHitbox(), sf::Color::White);
}

void Death::update(float dt) {
	if(getNextPosition(dt).x < 0 || getNextPosition(dt).x > Window::instance()->getWidth() - sd.dimensions.x ||
	   getNextPosition(dt).y < 150 || getNextPosition(dt).y > Window::instance()->getHeight()) {

		stopMovement();
		changeMovement();
	}

	position = getNextPosition(dt);

	switch(state) {
        case EntityState::stand:

          break;

	    case EntityState::goLeft:

	        left->process(dt);
	      break;

	    case EntityState::goRight:

	    	right->process(dt);
	      break;

	    case EntityState::goTop:

	    	top->process(dt);
	      break;

	    case EntityState::goDown:

	    	down->process(dt);
	      break;
    }

	left->setPosition(position);
	right->setPosition(position);
	top->setPosition(position);
	down->setPosition(position);

	if(sf::Randomizer::Random(0, 10000) == 0) {
		stopMovement();
		changeMovement();
	}
}
