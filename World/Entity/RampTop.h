#ifndef __RAMPTOP_H__
#define __RAMPTOP_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class RampTop : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampTop(int _id, sf::Vector2f _position);
	~RampTop() { }

	void draw(float dt);

	Hitbox getHitbox() const;

private:

};

#endif /*__RAMPTOP_H__*/
