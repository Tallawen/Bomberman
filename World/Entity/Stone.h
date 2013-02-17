#ifndef __STONE_H__
#define __STONE_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Stone : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	Stone(int _fieldId, int _priority, sf::Vector2f _position);
	~Stone() { }

	void draw(float dt);
	Hitbox getHitbox() const;

private:

};

#endif /*__STONE_H__*/
