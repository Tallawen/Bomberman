#ifndef __BOMBBAR_H__
#define __BOMBBAR_H__

#include "../StdAfx.h"

#include "../Renderer/SpriteManager.h"

#include "../World/Entity/Player.h"

#include "UIElement.h"

class BombBar : public UIElement {
private:
	sf::Sprite sprite;
	SpriteData sd;

	sf::Vector2f position;

	int amount;

	Player *playerPtr;

public:
	BombBar(Player *_playerPtr, sf::Vector2f _position);
	~BombBar() { }

	void update(float dt);
	void draw(float dt);

private:
	void create();

};

#endif /*__BOMBBAR_H__*/
