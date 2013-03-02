#ifndef COLLECTIBLE_H_
#define COLLECTIBLE_H_

#include "../Entity.h"
#include "Player.h"

class Collectible : public Entity {
public:
	Collectible(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	virtual ~Collectible() {}

	EntityType getType() const { return EntityType::collectible; }

	int getScoresWhenKilled() const { return 0; }

//	void draw(float dt);
//	void update(float dt);

    virtual void collect(Player* player);

};


#endif /* COLLECTIBLE_H_ */
