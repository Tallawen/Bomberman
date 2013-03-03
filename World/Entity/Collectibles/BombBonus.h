#ifndef __BOMBBONUS_H__
#define __BOMBBONUS_H__

#include "../Collectible.h"
#include "../../../constants.h"

class BombBonus : public Collectible {
public:
	enum class Amount {
		minusone = -1,
		one = 1,
		many = 3,
		max = 5 //Constants::Bomb::MAX_AMOUNT
	};

private:
	Amount amount; // amount of health to give player. can be negative;

public:
	BombBonus(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate, Amount bombs);
	~BombBonus() { }

	void collect(Player* player);

};

#endif /*__BOMBBONUS_H__*/
