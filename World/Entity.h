#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../StdAfx.h"

#include "../Renderer/Sprite.h"
#include "../Renderer/Animation.h"
#include "../Renderer/Window.h"

#include "Hitbox.h"

struct EntityData {

	/** Pozycja na ekranie **/
	sf::Vector2f position;

	/** Id kafla **/
	int id;
};

class World;

class Entity {
public:
	EntityData info;
	SpriteData sd;

	/// Czy entity ma zostac usuniete
	bool remove;

public:
	Entity() { remove = false; }
	virtual ~Entity() { }

	virtual void update(float dt) { }
	virtual void draw(float dt) { }

	virtual Hitbox getHitbox() const {
		// no collide: hitbox will ignore any collisions
		// See Hitbox.h
		return Hitbox(sf::Vector2f(0,0),sf::Vector2f(0,0));
	}
	//virtual void checkCollisions(float dt) const = 0;
};

#endif /*__ENTITY_H__*/
