#ifndef __UIC_H__
#define __UIC_H__

#include "StdAfx.h"

#include "Renderer/SpriteManager.h"

class UIc {
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
	UIc(bool secondPlayer = false);
	~UIc() { };

	void drawHealthBar(int _health);
	void drawBombBar(int _health);
	void drawFPS(float dt);
	void drawBoard();
	void drawScores(int scores);

private:

};


#endif /*__UI_H__*/
