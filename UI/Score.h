#ifndef __SCORES_H__
#define __SCORES_H__

#include "../StdAfx.h"

#include "UIElement.h"

#include "../Renderer/Text.h"
#include "../Renderer/SpriteManager.h"

#include "../World/Entity/Player.h"

class Scores : public UIElement {
private:
	sf::Sprite sprite;
	SpriteData sd;

	Text scores;

	sf::Vector2f position;

	Player *playerPtr;

public:
	Scores(Player *_playerPtr, sf::Vector2f _position);

	void update(float dt);
	void draw(float dt);

private:
	std::string intToStr(int i);

};


#endif /*__SCORES_H__*/
