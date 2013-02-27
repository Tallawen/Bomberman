#ifndef __STONE_H__
#define __STONE_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Stone : public Entity {
public:
	Stone(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);

	~Stone() { }

	EntityType getType() const { return EntityType::stone; }

	int getScoresWhenKilled() const { return 10; }

	void draw(float dt);

	Hitbox getHitbox() const {
		      return Hitbox(
		    		    sf::Vector2f(position.x, position.y),
		    		    sf::Vector2f(position.x + 50, position.y - 50));
	}

	Hitbox getNextHitbox(float dt) const {
		      return Hitbox(
		    		    sf::Vector2f(getNextXPosition(dt), getNextYPosition(dt)),
		    		    sf::Vector2f(getNextXPosition(dt) + 50, getNextYPosition(dt) - 50));
	}

	Hitbox getNextHorizontalHitbox(float dt) const {
		      return Hitbox(
		    		    sf::Vector2f(getNextXPosition(dt), position.y),
		    		    sf::Vector2f(getNextXPosition(dt) + 50, position.y - 50));
	}

	Hitbox getNextVerticalHitbox(float dt) const {
		      return Hitbox(
		    		    sf::Vector2f(position.x, getNextXPosition(dt)),
		    		    sf::Vector2f(position.x + 50, getNextYPosition(dt) - 50));
	}

};

#endif /*__STONE_H__*/
