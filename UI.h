#ifndef __UI_H__
#define __UI_H__

#include "StdAfx.h"

#include "Renderer/SpriteManager.h"

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
	sf::String *scoresPtr;

	sf::Shape board;

	int health;
	int newLenght;

public:
	UI(bool secondPlayer = false);
	~UI() { };

	void drawHealthBar(int _health);
	void drawBombBar(int _health);
	void drawFPS(float dt);
	void drawBoard();
	void drawScores(int scores);

private:

};


#endif /*__UI_H__*/
