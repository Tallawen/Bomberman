#ifndef __RAMPRIGHT_H__
#define __RAMPRIGHT_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class RampRight : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampRight(int _fieldId, int _priority, sf::Vector2f _position);
	~RampRight() { }

	void draw(float dt);

	Hitbox getHitbox() const;

private:

};

#endif /*__RAMPRIGHT_H__*/
