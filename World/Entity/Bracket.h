#ifndef __BRACKET_H__
#define __BRACKET_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Bracket : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	Bracket(int _fieldId, int _priority, sf::Vector2f _position);
	~Bracket() { }

	void draw(float dt);
	Hitbox getHitbox() const;

private:

};

#endif /*__BRACKET_H__*/
