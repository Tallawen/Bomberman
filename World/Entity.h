#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Hitbox.h"

#include "../StdAfx.h"
#include "../Renderer/Sprite.h"

struct EntityData {
	sf::Vector2f position;

	int fieldId;
	int priority;
};

class World;

class Entity {
public:
	Entity() { remove = false; }
	virtual ~Entity() { }

	EntityData info;
	SpriteData sp;

	/// Czy entity ma zostac usuniete
	bool remove;

	virtual void update(float dt) { }
	virtual void draw(float dt) { }

	virtual Hitbox getHitbox() const {
		// no collide: hitbox will ignore any collisions
		// See Hitbox.h
		return Hitbox(sf::Vector2f(0,0),sf::Vector2f(0,0));
	}
	//virtual void checkCollisions(float dt) const = 0;

private:

public:

private:

};

#endif /*__ENTITY_H__*/
