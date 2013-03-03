#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "../Entity.h"
#include "Player.h"

class Collectible : public Entity {
public:
	Collectible(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Collectible() { }

	EntityType getType() const { return EntityType::collectible; }

	int getScoresWhenKilled() const { return 0; }

	void draw(float dt);
//	void update(float dt);

    virtual void collect(Player* player) = 0;

};


#endif /*__COLLECTIBLE_H__*/
