#include "Smoke.h"

#include "../../constants.h"

#include "Bomb.h"

Smoke::Smoke(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	sd = SpriteManager::instance()->getSpriteData("game.smoke");
	stop = new Animation(SpriteManager::instance()->getSprite("game.smoke"), sd);

	stop->setAutoStop(true);
	stop->setAutoDraw(true);
	stop->setPosition(position);
	stop->play();
}

Smoke::~Smoke() {
	//LOG("Delete explosion");
}

void Smoke::draw(float dt) {
	if(stop != nullptr && isAlive())
		stop->process(dt);

	Window::instance()->drawHitbox(getHitbox(), sf::Color::Black);
}

void Smoke::update(float dt) {
	if(stop == nullptr || !isAlive())
		return;

	if(!stop->isPlay() && isAlive()) {
		dead();
		remove();
	}
}
