#ifndef __BOX_H__
#define __BOX_H__

#include "../../StdAfx.h"

#include "../Entity.h"

class Box : public Entity {
public:
	Box(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Box() { }

	EntityType getType() const { return EntityType::box; }

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

#endif /*__BRACKET_H__*/
