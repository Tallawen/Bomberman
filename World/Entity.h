#ifndef __ENTITY_H__
#define __ENTITY_H__

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
	Entity() { }
	virtual ~Entity() { }

	EntityData info;
	SpriteData sp;

	virtual void update(float dt) { }
	virtual void draw(float dt) { }
	//virtual void checkCollisions(float dt) const = 0;

private:

public:

private:

};

#endif /*__ENTITY_H__*/
