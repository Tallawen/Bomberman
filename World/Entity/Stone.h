#ifndef __STONE_H__
#define __STONE_H__

#include "../../StdAfx.h"

#include "../Entity.h"
#include "../../Renderer/Sprite.h"
#include "../../Renderer/Animation.h"
#include "../../Renderer/Window.h"

class Stone : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	Stone(int _fieldId, int _priority, sf::Vector2f _position);
	~Stone() { }

	void draw(float dt);

private:

};

#endif /*__STONE_H__*/
