#ifndef __BRACKET_H__
#define __BRACKET_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Bracket : public Entity {
public:
	sf::Sprite sprite;

public:
	Bracket(int _id, sf::Vector2f _position);
	~Bracket() { }

	void draw(float dt);
	Hitbox getHitbox() const;

};

#endif /*__BRACKET_H__*/
