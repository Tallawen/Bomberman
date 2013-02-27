#ifndef __BOMB_H__
#define __BOMB_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "Player.h"

class Bomb : public Entity {
private:
	Player *playerPtr;

	float lifeTime;

public:
	Bomb(sf::Vector2f _position, Player* _playerPtr, std::queue<Entity*> *_entitiesToCreate);
	~Bomb();

	EntityType getType() const { return EntityType::bomb; }

	void draw(float dt);
	void update(float dt);

private:
	void explosion();

};

#endif /*__BRACKET_H__*/
