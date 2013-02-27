#ifndef __GLIMMER_H__
#define __GLIMMER_H__

#include "../../StdAfx.h"

#include "../Entity.h"

#include "../World.h"

class Glimmer : public Entity {
public:
	World *ptr;

public:
	Glimmer(World *_ptr, sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Glimmer() { };

	EntityType getType() const { return EntityType::enemy; }

	void update(float dt);
	void draw(float dt);

};

#endif /*__GLIMMER_H__*/
