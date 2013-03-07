#ifndef __BOMB_H__
#define __BOMB_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "Player.h"

class Bomb : public Entity {
private:
	Player *playerPtr;

	float lifeTime;
	int explosionLength;

	float oTTmp;
	float offsetTime;
	float offsetDistance;

	float blinkingTime;

	std::string filename;

public:
	Bomb(sf::Vector2f _position, Player* _playerPtr, std::queue<Entity*> *_entitiesToCreate);
	~Bomb();

	EntityType getType() const { return EntityType::bomb; }

	void draw(float dt);
	void update(float dt);

	Player* getPlayerPtr() { return playerPtr; }

	void move(float _time, float _distance);

	void setLifetime(float lf);

private:
	void move(float dt);
	void blinking(float dt);

	void explosion();
};

#endif /*__BRACKET_H__*/
