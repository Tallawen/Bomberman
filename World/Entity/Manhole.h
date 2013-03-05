#ifndef __MANHOLE_H__
#define __MANHOLE_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Manhole : public Entity {
private:
	EntityType type;

public:
	Manhole(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Manhole() { }

	EntityType getType() const { return type; }

	void draw(float dt);

	void open();
	void close();
};

#endif /*__MANHOLE_H__*/
