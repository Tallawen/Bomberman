#ifndef __BOMB_H__
#define __BOMB_H__

#include "../../StdAfx.h"

#include "../World.h"

#include "../Entity.h"

class Bomb : public Entity {
public:
	bool live;

private:
	World *ptr;

	sf::Sprite sprite;

	int &bombNum;
	int explosionLength;

	float lifeTime;

public:
	Bomb(World *_ptr, int &_bombNum, int _explosionLength, int _fieldId, int _priority, sf::Vector2f _position);
	~Bomb();

	void draw(float dt);
	void update(float dt);

	Hitbox getHitbox() const;

	bool isLive() const { return live; }

private:
	void explosion();

};

#endif /*__BRACKET_H__*/
