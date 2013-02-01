#ifndef __RAMPLEFT_H__
#define __RAMPLEFT_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class RampLeft : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampLeft(int _fieldId, int _priority, sf::Vector2f _position);
	~RampLeft() { }

	void draw(float dt);

private:

};

#endif /*__RAMPLEFT_H__*/
