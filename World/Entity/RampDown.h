#ifndef __RAMPDOWN_H__
#define __RAMPDOWN_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class RampDown : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampDown(int _id, sf::Vector2f _position);
	~RampDown() { }

	void draw(float dt);

	Hitbox getHitbox() const;

private:

};

#endif /*__RAMPDOWN_H__*/
