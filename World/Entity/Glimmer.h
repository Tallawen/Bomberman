#ifndef __GLIMMER_H__
#define __GLIMMER_H__

#include "../../StdAfx.h"

#include "../World.h"

#include "../Entity.h"

class Glimmer : public Entity {
public:

	/** kolejnosc musi byc taka sama jak w kontenerze sprite **/
	enum class Direction {
		down,
		top,
		right,
		left
	};

	World *ptr;

	/// if true, currently moving in certain direction
	bool goDown, goUp, goLeft, goRight;

private:
	/**
	 * 0 - sprite go down
	 * 1 - sprite go top
	 * 2 - sprite go right
	 * 3 - sprite go left
	 **/
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

	sf::Color hitboxColor;

public:
	Glimmer(World  *_ptr, int _id, sf::Vector2f _position);
	~Glimmer();

	void update(float dt);
	void draw(float dt);

	Hitbox getHitbox() const;

	void setVelocity(float x, float y) { velocity = sf::Vector2f(x, y); }
	void setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

	void movement(Direction direction);
	void route(bool current);

	sf::Vector2f* getPosition() { return &position; }

	void detectTileCollisions();
private:

	//used in detectTileCollisions
	void collideWithTile(World *ptr, int id);

};

#endif /*__PLAYER_H__*/
