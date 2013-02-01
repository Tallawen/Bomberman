#ifndef __RAMPTOP_H__
#define __RAMPTOP_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class RampTop : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	RampTop(int _fieldId, int _priority, sf::Vector2f _position);
	~RampTop() { }

	void draw(float dt);

private:

};

#endif /*__RAMPTOP_H__*/
