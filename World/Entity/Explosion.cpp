#include "Explosion.h"

#include "../../constants.h"

#include "Bomb.h"

Explosion::Explosion(sf::Vector2f _position, Player *_playerPtr, std::queue<Entity*> *_entitiesToCreate, Directions _directions, float _delay, int _explosionLenght) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	playerPtr = _playerPtr;
	directions = _directions;

	delay = _delay;
	explosionLength = _explosionLenght;
	first = false;

	nextPosition[0] = position;  nextPosition[0].x += 50;
	nextPosition[1] = position;  nextPosition[1].x -= 50;
	nextPosition[2] = position;  nextPosition[2].y -= 50;
	nextPosition[3] = position;  nextPosition[3].y += 50;

	sd = SpriteManager::instance()->getSpriteData("game.explosion");
	stop = new Animation(SpriteManager::instance()->getSprite("game.explosion"), sd);

	stop->setDelay(delay);
	stop->setAutoStop(true);
	stop->setAutoDraw(true);
	stop->setPosition(position);
	stop->play();

    //std::cerr << "Create explosion: " << explosionLength << std::endl;
}

Explosion::~Explosion() {
	//LOG("Delete explosion");
}

void Explosion::draw(float dt) {
	if(stop != nullptr && isAlive())
		stop->process(dt);
	Window::instance()->drawHitbox(getHitbox(),sf::Color::Green);
}

void Explosion::update(float dt) {
	if(stop == nullptr || !isAlive())
		return;

	if(!first && !stop->isDelay()) {
		if(explosionLength > 0) {

			switch(directions) {
			    case Directions::none: // -2

			      break;

			    case Directions::allSite: // -1
			    	for(int i = 0; i < 4; ++i)
			    		create(i);

			      break;

			    case Directions::right: // 0
			    	create(0);
			      break;

			    case Directions::left: // 1
			    	create(1);
			      break;

			    case Directions::top: // 2
			    	create(2);
			      break;

			    case Directions::down: // 3
			    	create(3);
			      break;
			}

		}

		first = true;
	}

	if(!stop->isPlay() && isAlive()) {
		dead();
		remove();
	}
}

void Explosion::setDelay(float delay) {
	stop->setDelay(delay);
}

void Explosion::create(int _id) {
	Explosion *newExplosion = nullptr;

	newExplosion = new Explosion(nextPosition[_id], playerPtr, entitiesToCreate, Directions(_id), delay + Constants::Explosion::DELAY, explosionLength - 1);
	entitiesToCreate->push(newExplosion);
}
/*
Hitbox Explosion::getHitbox() const {
    return Hitbox( info.position + sf::Vector2f(10, -10), info.position + sf::Vector2f(sd.dimensions.x, -sd.dimensions.y) + sf::Vector2f(-10, 10));
}*/
