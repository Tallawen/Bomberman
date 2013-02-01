#ifndef __BAC_H__
#define __BAC_H__

#include "Entity.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Window.h"
#include "../StdAfx.h"

class Bac : public Entity {
public:
	sf::Sprite sprite;

private:

public:
	Bac(int _fieldId, int _priority, sf::Vector2f _position) {
		info.fieldId = _fieldId;
		info.priority = _priority;
		info.position = _position;

		sprite = Sprite::instance()->getSprite("Bracket");
		sprite.SetPosition(info.position);
	}
	~Bac() { }

	//void update(float )
	void draw() {
		Window::instance()->getRW()->Draw(sprite);
	}

};

#endif /*__STONE_H__*/
