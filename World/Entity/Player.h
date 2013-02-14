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

	/// if true, currently moving in certain direction
	bool goDown, goUp, goLeft, goRight;

	/// if true, the player is moving
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

	/// Sprite placement in relation to `position`
	sf::Vector2f animation_offset;

	sf::Vector2f velocity;
	sf::Vector2f position;

	//bool goDown, goTop, goLeft, goRight;
	//bool lockChangeDirection;

	float distanceToMove;

	/// przesuniecie hitboxa dla ruchu w prawo
	// TODO: Sprawdzic czy blad przesuniecia nie wynika z zle podpietej tekstury
	sf::Vector2f hitboxOffset;

public:
	Player(int _fieldId, int _priority, sf::Vector2f _position);

	void update(float dt);
	void draw(float dt);
	Hitbox getHitbox() const;

	bool isLock() const { return lockChangeDirection; }

	void setVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
	void setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

	void setDistance(float newDis) { distanceToMove = newDis; }

	/// Initialize movement in a direction
	void down() {
		goDown = lockChangeDirection = true;
		animation->setSprite(sprite.at(0), spriteData.at(0));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);
	}
	void top() {
		goUp = lockChangeDirection = true;
		animation->setSprite(sprite.at(1), spriteData.at(1));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);
	}
	void right() {
		goRight = lockChangeDirection = true;
		animation->setSprite(sprite.at(2), spriteData.at(2));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(10, 0);
	}
	void left() {
		goLeft = lockChangeDirection = true;
		animation->setSprite(sprite.at(3), spriteData.at(3));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);
	}

	sf::Vector2f* getPosition() { return &position; }

	void detectTileCollisions(World *ptr);

	void setBomb(World *ptr);

private:
	//used in detectTileCollisions
	void collideWithTile(World *ptr, int id);

};

#endif /*__PLAYER_H__*/
