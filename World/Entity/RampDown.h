#ifndef __RAMPDOWN_H__
#define __RAMPDOWN_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class RampDown : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampDown(int _fieldId, int _priority, sf::Vector2f _position);
	~RampDown() { }


	void draw(float dt);

private:

};

#endif /*__RAMPDOWN_H__*/
