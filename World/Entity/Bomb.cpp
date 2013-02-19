#include "Bomb.h"

#include "../../constants.h"

#include "../../Renderer/SoundManager.h"

#include "Explosion.h"

Bomb::Bomb(World *_ptr, int &_bombAmount, int _explosionLength, int _id, sf::Vector2f _position) : bombAmount(_bombAmount) {
	ptr = _ptr;

	info.id  = _id;
	info.position = _position;

	bombAmount -= 1;

	lifeTime = Constants::Bomb::LIFE_TIME;
	live = true;

	explosionLength = _explosionLength;

	sprite = Sprite::instance()->getSprite("Bomb");
	sd     = Sprite::instance()->getSpriteData("Bomb");

	sprite.SetPosition(info.position);

	LOG("Create bomb");
}

Bomb::~Bomb() {
	bombAmount += 1;

	LOG("Delete bomb");
}

void Bomb::draw(float dt) {
	if(lifeTime > 0) {
		Window::instance()->getRW()->Draw(sprite);
		Window::instance()->drawHitbox(getHitbox(), sf::Color::Yellow);
	}
}

void Bomb::update(float dt) {
	if(lifeTime < 0 || !live) {
		if(!remove) {
			explosion();

			SoundManager::getQueue().push(sf::Sound());
			SoundManager::getQueue().back().SetBuffer(SoundManager::instance().getSoundBuffer("bomb.explode"));
		 	SoundManager::getQueue().back().Play();
		}
		remove = true;
	  return;
	}

	lifeTime -= dt;
}

Hitbox Bomb::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y));
}

void Bomb::explosion() {
	if(ptr->world[info.id].find(LayerType::LAYER_EXPLOSIONS) != ptr->world[info.id].end()) {
		Entity* entity = ptr->world[info.id][LayerType::LAYER_EXPLOSIONS];

		ptr->world[info.id].erase(LayerType::LAYER_EXPLOSIONS);

		static_cast<Explosion*>(entity)->setRemove();
		delete entity;
	}


	/// Eksplozja w miejscu bomby
	Explosion *newExplosion = new Explosion(ptr, info.id, Constants::Explosion::DELAY, info.position, explosionLength, Explosion::Directions::allSite);
	ptr->world[info.id].insert(std::make_pair(LayerType::LAYER_EXPLOSIONS, newExplosion));
}
