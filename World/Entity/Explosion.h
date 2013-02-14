#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../World.h"

#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class Explosion : public Entity {
public:

private:
	Animation animation;

	World *ptr;

public:
	Explosion(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position);
	~Explosion();

	void draw(float dt);

private:

};

#endif /*__EXPLOSION_H__*/
