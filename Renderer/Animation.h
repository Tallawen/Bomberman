#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../StdAfx.h"

#include "SpriteManager.h"

class Animation {
private:
	sf::Sprite sprite;
	SpriteData info;

	bool playAnimation;
	bool autoDraw;
	bool autoStop;

	float timePerFrame;
	float timeAccumulation;

	float delayTime;
	float delayAccumulation;

public:
	Animation() = delete;
	Animation(sf::Sprite _sprite, SpriteData _info, bool _autoDraw = true, bool _autoStop = false);

	void play();
	void stop();
	void pause();

	void setAutoStop(bool _autoStop = true) { autoStop = _autoStop; }
	void setAutoDraw(bool _autoDraw = true) { autoDraw = _autoDraw; }
	void setDelay(float delay = 0.0f);

	void setSprite(sf::Sprite _sprite, const SpriteData &_info);

	sf::Sprite* getSpritePtr() { return &sprite; }
	sf::Sprite getSprite() { return sprite; }

	void draw();

	void process(float dt);

	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition() const { return sprite.GetPosition(); }

	SpriteData getSpriteInfo() const { return info; }

	bool isPlay() const { return playAnimation; }
	bool isDelay() const { return !(delayAccumulation >= delayTime); };
};

#endif /*__ANIMATION_H__*/
