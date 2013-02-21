#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../StdAfx.h"

#include "../World.h"

#include "../Entity.h"

class Player : public Entity {
public:
	enum class Dire {
		none,
		down,
		top,
		left,
		right
	};
	/// if true, currently moving in certain direction
	bool goDown, goUp, goLeft, goRight;

	/// if true, the player is moving
	bool lockChangeDirection;

	Dire lastMove;

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

	/// przesuniecie hitboxa dla ruchu w prawo
	// TODO: Sprawdzic czy blad przesuniecia nie wynika z zle podpietej tekstury
	sf::Vector2f hitboxOffset;

	/// Liczba bomb ktore posiada aktualne gracz
	int bombAmount;

	int maxBombAmount;
	int explosionLength;

	uint healthAmount;
	uint maxHealthAmount;

	sf::Color hitboxColor;

public:
	Player(int _id, sf::Vector2f _position);

	void update(float dt);
	void draw(float dt);

	Hitbox getHitbox() const;

	void setVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
	void setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

	/// Initialize movement in a direction
	void down() {
		goDown = lockChangeDirection = true;
		animation->setSprite(sprite.at(0), spriteData.at(0));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);
		lastMove = Dire::down;
	}
	void top() {
		goUp = lockChangeDirection = true;
		animation->setSprite(sprite.at(1), spriteData.at(1));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);

		lastMove = Dire::top;
	}
	void right() {
		goRight = lockChangeDirection = true;
		animation->setSprite(sprite.at(2), spriteData.at(2));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(10, 0);

		lastMove = Dire::right;
	}
	void left() {
		goLeft = lockChangeDirection = true;
		animation->setSprite(sprite.at(3), spriteData.at(3));
		animation->setPos(position + animation_offset);

		hitboxOffset = sf::Vector2f(0, 0);
		lastMove = Dire::left;
	}

	sf::Vector2f* getPosition() { return &position; }

	void detectTileCollisions(World *ptr);

	void setBomb(World *ptr);

	bool isLock() const { return lockChangeDirection; }

	int getBombAmount() const { return bombAmount; }
	int getHealthAmount() const { return healthAmount; }

private:
	//used in detectTileCollisions
	void collideWithTile(World *ptr, int id);

};

#endif /*__PLAYER_H__*/
