#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Sprite.h"
#include "Window.h"
#include "../StdAfx.h"

class Animation {
public:

private:
	sf::Sprite *sprite;
	SpriteData info;

	bool playAnimation;
	bool autoDraw;

	float timePerFrame;
	float timeAccumulation;

public:
	Animation() { }
	Animation(sf::Sprite *_sprite, const SpriteData &_info, bool _autoDraw = true);

	void play();
	void stop();
	void pause();

	sf::Sprite* getSprite();
	void setSprite(sf::Sprite *_sprite, const SpriteData &_info);

	void draw();

	void process(float dt);

	void setPos(sf::Vector2f newPos);
	sf::Vector2f getPos();
	SpriteData getSpriteInfo();

private:

};

#endif /*__ANIMATION_H__*/

