#include "Bat.h"

Bat::Bat(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 50, 50, _entitiesToCreate) {
	layer = EntityLayer::layer_background4;

	sd = SpriteManager::instance()->getSpriteData("enemy.bat_down");

	left = new Animation(
			SpriteManager::instance()->getSprite("enemy.bat_left"),
			SpriteManager::instance()->getSpriteData("enemy.bat_left"));

	right = new Animation(
			SpriteManager::instance()->getSprite("enemy.bat_right"),
			SpriteManager::instance()->getSpriteData("enemy.bat_right"));

	top = new Animation(
			SpriteManager::instance()->getSprite("enemy.bat_top"),
			SpriteManager::instance()->getSpriteData("enemy.bat_top"));

	down = new Animation(
			SpriteManager::instance()->getSprite("enemy.bat_down"),
			SpriteManager::instance()->getSpriteData("enemy.bat_down"));

	changeMovement();
}

void Bat::draw(float dt) {
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

void Bat::update(float dt) {
	if(getNextPosition(dt).x < 2 || getNextPosition(dt).x > Window::instance()->getWidth() - sd.dimensions.x - 2 ||
	   getNextPosition(dt).y < 152 || getNextPosition(dt).y > Window::instance()->getHeight() - 2) {

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
