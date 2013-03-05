#ifndef __AVATAR_H__
#define __AVATAR_H__

#include "../StdAfx.h"

#include "../Renderer/SpriteManager.h"
#include "../Renderer/Window.h"

#include "UIElement.h"

class Avatar : public UIElement {
private:
	sf::Sprite sprite;
	SpriteData sd;

	sf::Vector2f position;

public:
	Avatar(sf::Vector2f _position, bool black = false);
	~Avatar() { }

	void update(float dt) { }
	void draw(float dt);
};

#endif /*__AVATAR_H__*/
