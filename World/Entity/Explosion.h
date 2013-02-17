#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "../../StdAfx.h"

#include "../World.h"

#include "../Entity.h"

class Explosion : public Entity {
public:
	/** Przy zmianie enuma nalezy wprowadzic zmiany w dlaszej czesci klasy **/
	enum class Directions {
		none = -2, /// wybuch w miejscu
		allSite,   /// wybuch w wszystkie strony (4)
		right,
		left,
		top,
		down,
	};

private:
	World *ptr;
	Animation *animation;

	/** Indeksy odpowiadaj¹ wartoscia enuma Directions (od zera) **/
	int id[4];
	sf::Vector2f position[4];

	int explosionLength;

	/** Kierunek w ktorym idze wybuch **/
	Directions directions;

	/** Opuznienie zalaczenia animacji **/
	float delay;

	/** Flaga gwarantujaca wykonanie danego bloku kodu w sekji update 1 raz **/
	bool first;

public:
	Explosion(World *_ptr, int _fieldId, float delay, int _priority, sf::Vector2f _position, int _explosionLength, Directions _directions);
	~Explosion();

	void draw(float dt);
	void update(float dt);

	/** Tworzy eksplozje na polu o danym id **/
	inline void create(int _id);

	/**
	 * Sprawdza czy na danym kaflu istnieje dana warstwa.
	 * Jesli tak to to wywoluje funkcje ktora jest przekazana jako wskaznik
	 * (szablon dla funkcji)
	 *
	 * @param ptr wskaznik na klase World
	 * @param id id pola
	 * @param layer warstwa dosprawdzenia
	 * @param ptrFun wskaznik na funkcje ktora ma sie wykonac
	 *
	 * @retval true jesli na danym kaflu istnieje dana warstwa
	 * @retval false jesli warstwa nie istnieje
	 *
	 **/
	bool checkTile(World *ptr, int id, LayerType layer, bool(Explosion::*ptrFun)(World*, int));

	/** Metody przekazywana do checkTitle **
	 ** @see checkTile                    **/
	bool stone(World *ptr, int id);
	bool block(World *ptr, int id);
	bool explosion(World *ptr, int id);
	bool bomb(World *ptr, int id);
	/** Koniec **/

	Hitbox getHitbox() const;

	void setDelay(float delay);
	void setRemove();

private:

};

#endif /*__EXPLOSION_H__*/
