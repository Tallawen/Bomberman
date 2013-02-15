#include "Bomb.h"

Bomb::Bomb(World *_ptr, int &_bombNum, int _explosionLength, int _fieldId, int _priority, sf::Vector2f _position) : bombNum(_bombNum) {
	ptr = _ptr;

	info.fieldId  = _fieldId;
	info.priority = _priority;
	info.position = _position;

	lifeTime = 3;
	live = true;

	explosionLength = _explosionLength;

	sprite = Sprite::instance()->getSprite("Bomb");
	sp     = Sprite::instance()->getSpriteData("Bomb");

	sprite.SetPosition(info.position);

	LOG("Create bomb");
}

Bomb::~Bomb() {
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
		if(!remove)
			explosion();

		remove = true;
	  return;
	}

	lifeTime -= dt;
}

Hitbox Bomb::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y));
}

void Bomb::explosion() {
	/* right, left, top, bottom */
	int id[] = {0, 0, 0, 0};
	sf::Vector2f position[] = {info.position, info.position, info.position, info.position};

	// Eksplozja w miejscu bomby
//	Explosion *newExplosion = new Explosion(ptr, info.fieldId, 0.1f, 0, info.position, 1, Explosion::Directions::allSite);
//	ptr->world[info.fieldId].insert( std::make_pair(World::DisplayOrder::explosion, newExplosion) );

	/*
	id[0] = info.fieldId + 1;
	id[1] = info.fieldId - 1;
	id[2] = info.fieldId + ptr->mapDimensions.x;
	id[3] = info.fieldId - ptr->mapDimensions.x;

	position[0].x += ptr->floorData.dimensions.x;
	position[1].x -= ptr->floorData.dimensions.x;
	position[2].y += ptr->floorData.dimensions.y;
	position[3].y -= ptr->floorData.dimensions.y;

	for(int i = 0; i < 4; ++i) {
		if(ptr->world[ id[i] ].find(World::DisplayOrder::explosion) == ptr->world[ id[i] ].end()) {
			newExplosion = new Explosion(ptr, id[i], 0.2f, 0, position[i], explosionLength - 1, i);
			ptr->world[ id[i] ].insert( std::make_pair(World::DisplayOrder::explosion, newExplosion) );
		}
	}*/
}
