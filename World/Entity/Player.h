#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../World.h"

#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

#include "Bomb.h"

class Player : public Entity {
public:

	bool goDown, goTop, goLeft, goRight;
		bool lockChangeDirection;

private:
	/* 0 - sprite go down
	 * 1 - sprite go top
	 * 2 - sprite go right
	 * 3 - sprite go left
	 */
	std::vector<sf::Sprite> sprite;
	std::vector<SpriteData> spriteData;

	Animation *animation;

	sf::Vector2f velocity;
	sf::Vector2f position;

	//bool goDown, goTop, goLeft, goRight;
	//bool lockChangeDirection;

	float distanceToMove;

public:
	Player(int _fieldId, int _priority, sf::Vector2f _position);

	void update(float dt);
	void draw(float dt);

	bool isLock() const { return lockChangeDirection; }
	void setVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
	void setDistance(float newDis) { distanceToMove = newDis; }

	void down() { goDown = lockChangeDirection = true;  animation->setSprite(&sprite.at(0), spriteData.at(0)); animation->setPos(position);}
	void top() { goTop = lockChangeDirection = true; animation->setSprite(&sprite.at(1), spriteData.at(1)); animation->setPos(position); }
	void right() { goRight = lockChangeDirection = true; animation->setSprite(&sprite.at(2), spriteData.at(2)); animation->setPos(position);}
	void left() { goLeft = lockChangeDirection = true; animation->setSprite(&sprite.at(3), spriteData.at(3)); animation->setPos(position);}

	sf::Vector2f* getPosition() { return &position; }

	void checkCollisionsWorld(World *ptr);

	void setBomb(World *ptr);

private:
	bool isAnyFieldBelowMe(World *ptr, sf::Vector2i pos);
	bool isAnyFieldAboveMe(World *ptr, sf::Vector2i pos);
	bool isAnyFieldOnRight(World *ptr, sf::Vector2i pos);
	bool isAnyFieldOnLeft(World *ptr, sf::Vector2i pos);

};


#endif /*__PLAYER_H__*/
