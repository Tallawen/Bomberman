#ifndef __UI_H__
#define __UI_H__

#include "StdAfx.h"

#include "Renderer/Sprite.h"

class UI {
public:

private:
	sf::Sprite sprite;

	sf::Sprite *healthBar;
	sf::Sprite *healthBarAlpha;

	sf::Image newHealthBarImg;
	sf::Image newBombBarImg;

	sf::Vector2f healthBarPos;
	sf::Vector2f bombBarPos;

	sf::String *fps;

	sf::Shape board;

public:
	UI();
	~UI() { };

	void drawHealthBar(int _health);
	void drawBombBar(int _health);
	void drawFPS(float dt);
	void drawBoard();

private:

};


#endif /*__UI_H__*/
