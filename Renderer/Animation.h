#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Sprite.h"
#include "Window.h"
#include "../StdAfx.h"

class Animation {
public:
	enum class RotationDirection {
		left,
		right,
		none
	};

	/* TODO: Wymyslic lepsze nazwy (wyszystkiego) */
	enum class MoveType {
		left,
		right,
		top,
		down,
		topAndDown,
		leftAndRight,
		none
	};

private:
	sf::Sprite sprite;
	SpriteData info;

	bool playAnimation;
	bool autoDraw;
	bool autoStop;

	float timePerFrame;
	float timeAccumulation;

	float delayPerFrame;
	float delayAccumulation;

	float rotationSpeed;
	float rotationTimeAccumulation;
	float rotationAngle;
	RotationDirection rotationDirection;

public:
	Animation() { }
	Animation(sf::Sprite _sprite, const SpriteData &_info, bool _autoDraw = true, bool _autoStop = false);

	void play();
	void stop();
	void pause();

	void setAutoStop(bool _autoStop = true);
	void setAutoDraw(bool _autoDraw = true);
	void setDelay(float delay = 0.f);

	sf::Sprite* getSprite();
	void setSprite(sf::Sprite _sprite, const SpriteData &_info);

	void draw();

	void process(float dt);

	void setPos(sf::Vector2f newPos);

	sf::Vector2f getPos();
	SpriteData getSpriteInfo();

	bool isPlay() { return playAnimation; }
	bool isDelay();

	/**
	 * Wlacza obracanie obiektu wzglêdem jego srodka.
	 *
	 * @param rd kierunek obracania [none - wylacza obracanie]
	 * @param speed prêtkosc obracania
	 *
	 */
	void rotate(RotationDirection rd, float speed = 1.f);

	/**
	 * Obraca obiekt
	 *
	 */
	void rotate(float dt);

	/**
	 * Poruszanie obiektem od jego srodka do danego wychylenia i spowrotem.
	 *
	 * @param md typ wychylenia [none - wylacza obracanie]
	 * @param distance amplituda wychylenia
	 * @param speed prêtkosc obracania
	 *
	 */
	void move(MoveType md, float distance, float speed = 1) = delete;

private:

};

#endif /*__ANIMATION_H__*/
