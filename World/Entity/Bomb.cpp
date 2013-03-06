#include "Bomb.h"

#include "../../constants.h"

#include "../../Renderer/SoundManager.h"

#include "Explosion.h"

Bomb::Bomb(sf::Vector2f _position, Player* _playerPtr, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {
	layer = EntityLayer::layer_background5;

	playerPtr = _playerPtr;

	LOG(playerPtr);

	playerPtr->setBombAmount( playerPtr->getBombAmount() - 1 );

	lifeTime = Constants::Bomb::LIFE_TIME;
	blinkingTime = lifeTime / 5;

	filename = "game.bomb_black";

	sprite = SpriteManager::instance()->getSprite(filename);
	sd     = SpriteManager::instance()->getSpriteData(filename);

	sprite.SetPosition(position);

	//LOG("Create bomb");
}

Bomb::~Bomb() {
	//playerPtr->setBombAmount( playerPtr->getBombAmount() + 1 );
}

void Bomb::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->drawHitbox(getHitbox(), sf::Color::Yellow);
}

void Bomb::update(float dt) {
	move(dt);

	blinking(dt);

	if(lifeTime < 0 && isAlive()) {
		explosion();
		dead();

	  return;
	}

	lifeTime -= dt;
}
/*Hitbox Bomb::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y));
}*/


void Bomb::move(float dt) {
	if(offsetTime > 0.0f) {
		position.y += offsetDistance / offsetTime * dt;

		sprite.SetPosition(position);

		if(oTTmp < 0)
			offsetTime = 0.0f;

		oTTmp -= dt;
	}
}

void Bomb::move(float _time, float _distance) {
	oTTmp = offsetTime = _time;
	offsetDistance = 10 + position.y;

	position.y = -10;

	lifeTime = _time + 0.5f;
}

void Bomb::blinking(float dt) {
	if(blinkingTime < 0) {
		blinkingTime = lifeTime / 5;

		filename = (filename == "game.bomb_black") ? "game.bomb_red" : "game.bomb_black";

		sprite = SpriteManager::instance()->getSprite(filename);
		sprite.SetPosition(position);
	}

	blinkingTime -= dt;
}

void Bomb::explosion() {
	// Play sound
	SoundManager::getQueue().push(sf::Sound());
	SoundManager::getQueue().back().SetBuffer( SoundManager::instance().getSoundBuffer("bomb.explode"));
	SoundManager::getQueue().back().SetVolume(30.0f);
	SoundManager::getQueue().back().Play();

	/// Eksplozja w miejscu bomby
	Explosion *newExplosion      = new Explosion(position + sf::Vector2f( -5,  10), playerPtr, entitiesToCreate, Explosion::Directions::none,  1 * Constants::Explosion::DELAY, 3);
	Explosion *newExplosionLeft  = new Explosion(position + sf::Vector2f(-55,  10), playerPtr, entitiesToCreate, Explosion::Directions::left,  2 * Constants::Explosion::DELAY, 2);
	Explosion *newExplosionRight = new Explosion(position + sf::Vector2f( 45,  10), playerPtr, entitiesToCreate, Explosion::Directions::right, 2 * Constants::Explosion::DELAY, 2);
	Explosion *newExplosionTop   = new Explosion(position + sf::Vector2f( -5, -40), playerPtr, entitiesToCreate, Explosion::Directions::top,   2 * Constants::Explosion::DELAY, 2);
	Explosion *newExplosionDown  = new Explosion(position + sf::Vector2f( -5,  60), playerPtr, entitiesToCreate, Explosion::Directions::down,  2 * Constants::Explosion::DELAY, 2);

	entitiesToCreate->push(newExplosion);
	entitiesToCreate->push(newExplosionLeft);
	entitiesToCreate->push(newExplosionRight);
	entitiesToCreate->push(newExplosionTop);
	entitiesToCreate->push(newExplosionDown);
}
