#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../StdAfx.h"

#include "../Renderer/Sprite.h"
#include "../Renderer/Animation.h"
#include "../Renderer/Window.h"

#include "Entity.h"

class Player : public Entity {
public:
	sf::Vector2f speed;

	bool goDown;
	bool goTop;
	bool goLeft;
	bool goRight;

	bool lock;

	float dis;
	float disChange;
	sf::Sprite sprite;
	Animation *down;

private:
	SpriteData spriteData;

public:
	Player(int _fieldId, int _priority, sf::Vector2f _position) {
		info.fieldId = _fieldId;
		info.priority = _priority;
		info.position = _position;

		goDown = goTop = goLeft = goRight = false;

		dis = 51;
		speed = sf::Vector2f(0, 0);

		lock = false;
		sprite = Sprite::instance()->getSprite("Player");
		spriteData = Sprite::instance()->getSpriteData("Player");
		sprite.SetPosition(_position);
		sprite.Move(12, -10);

		down = new Animation(&sprite, spriteData, true);
		std::cout << "HELLO" << std::endl;
	}

	void update(float dt) {
		if(!goDown)
			down->stop();


		if(goDown) {
			down->play();

			dis -= speed.y * dt;
			if(dis > 0) {
				sf::Vector2f newPos = down->getPos();
				newPos += speed * dt;

				down->setPos(newPos);

			} else {
				lock = false;
				goDown = false;
			}
		}

		if(goTop) {
			dis += speed.y * dt;
			if(dis > 0) {

				std::cout << dis << std::endl;

				sf::Vector2f newPos = down->getPos();
				newPos += speed * dt;

				down->setPos(newPos);

			} else {
				lock = false;
				goTop = false;
			}
		}

		if(goLeft) {
			dis += speed.x * dt;
			if(dis > 0) {

				sf::Vector2f newPos = down->getPos();
				newPos += speed * dt;

				down->setPos(newPos);
			} else {
				lock = false;
				goLeft = false;

			}
		}

		if(goRight) {
			dis -= speed.x * dt;
			if(dis > 0) {

				sf::Vector2f newPos = down->getPos();
				newPos += speed * dt;

				down->setPos(newPos);
			} else {
				lock = false;
				goRight = false;
			}
		}
	}

	void draw(float dt) {
		Window::instance()->getRW()->Draw(sprite);

		down->process(dt);
		down->draw();
	}

private:

};

#endif /*__PLAYER_H__*/
