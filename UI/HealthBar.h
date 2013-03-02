#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__

#include "../StdAfx.h"

#include "UIElement.h"

#include "../World/Entity/Player.h"
#include "../Renderer/Text.h"

class HealthBar : public UIElement {
public:
	const int MAX_LENGHT;

private:
	sf::Sprite hpText;
	SpriteData hpSd;

	sf::Sprite sprite; /// pomocnicza

	sf::Sprite bar; /// grafika pokazuj¹ca aktualny stan ¿ycia
	sf::Sprite barAlpha; /// grafika pokazyj¹ca maksymalny stan ¿ycia

	Text amountText; /// tekst na srodku paska

	sf::Image img;

	SpriteData sd;
	sf::Vector2f position;
	sf::Vector2f barPosition;

	Player *playerPtr;

	int healthAmount;
	int lenght;

public:
	HealthBar(Player *_playerPtr);
	HealthBar(Player *_playerPtr, sf::Vector2f _position);

	~HealthBar() { }

	void update(float dt);
	void draw(float dt);

private:
	void create();
	std::string intToStr(int i);

};

#endif /*__HEALTHBAR_H__*/

