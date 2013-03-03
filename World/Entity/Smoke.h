#ifndef __SMOKE_H__
#define __SMOKE_H__

#include "../../StdAfx.h"

#include "../World.h"

#include "../Entity.h"

class Smoke : public Entity {
public:
	Smoke(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Smoke();

	EntityType getType() const { return EntityType::none; }

	void draw(float dt);
	void update(float dt);
};
#endif /*__SMOKE_H__*/
