#ifndef __BAT_H__
#define __BAT_H__

#include "../Entity.h"

class Bat : public Entity {
public:
	Bat(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Bat() { }

	EntityType getType() const { return EntityType::enemy; }

	int getScoresWhenKilled() const { return 10; }

	void draw(float dt);
	void update(float dt);

	void goLeft()  { setXVelocity( -getDefaultXVelocity() ); state = EntityState::goLeft;  left->play();  }
	void goRight() { setXVelocity(  getDefaultXVelocity() ); state = EntityState::goRight; right->play(); }
	void goTop()   { setYVelocity( -getDefaultYVelocity() ); state = EntityState::goTop;   top->play();   }
	void goDown()  { setYVelocity(  getDefaultYVelocity() ); state = EntityState::goDown;  down->play();  }

	void stopLeft()  { setXVelocity(0); state = EntityState::stand; left->stop();  }
	void stopRight() { setXVelocity(0); state = EntityState::stand; right->stop(); }
	void stopTop()   { setYVelocity(0); state = EntityState::stand; top->stop();   }
	void stopDown()  { setYVelocity(0); state = EntityState::stand; down->stop();  }

	void stopMovement() { setVelocity(0, 0); state = EntityState::stand; left->stop(); right->stop(); top->stop(); down->stop(); }
};

#endif /*__BRACKET_H__*/
