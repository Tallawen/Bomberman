#ifndef __BOMB_H__
#define __BOMB_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../World.h"

#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class Bomb : public Entity {
public:
	sf::Sprite sprite;
	float lifeTime;

private:
	std::vector<Animation> animationArray;

	bool live;
	bool detonated;
	World *ptr;

public:
	Bomb(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position);
	~Bomb();

	void draw(float dt);
	Hitbox getHitbox() const;

	bool isLive() const { return live; }
	void destroyStone(World *ptr, sf::Vector2f position, int dis);

private:

};

#endif /*__BRACKET_H__*/
