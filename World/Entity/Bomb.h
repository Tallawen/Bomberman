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
	Animation *animation;

	bool live;
	World *ptr;

public:
	Bomb(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position);
	~Bomb();

	void draw(float dt);
	//void draw(float dt);

	bool isLive() const { return live; }
	void destroyStone(World *ptr, sf::Vector2f position, int dis);

private:

};

#endif /*__BRACKET_H__*/
