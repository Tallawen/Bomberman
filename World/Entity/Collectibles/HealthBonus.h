#ifndef __HPBONUS_H__
#define __HPBONUS_H__

#include "../Collectible.h"
#include "../../../constants.h"

class HealthBonus : public Collectible {
public:
	enum class Amount {
		minusone = -1,
		one = 1,
		many = 3,
		max = 5 //Constants::Player::MAX_HEALTH
	};

private:
	Amount amount; // amount of health to give player. can be negative;

public:
	HealthBonus(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate, Amount health);
	~HealthBonus() { }

	void collect(Player* player);

};

#endif /*__HPBONUS_H__*/