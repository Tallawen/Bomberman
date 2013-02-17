#ifndef __RAMPLEFT_H__
#define __RAMPLEFT_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class RampLeft : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampLeft(int _fieldId, int _priority, sf::Vector2f _position);
	~RampLeft() { }

	void draw(float dt);

	Hitbox getHitbox() const;

private:

};

#endif /*__RAMPLEFT_H__*/
