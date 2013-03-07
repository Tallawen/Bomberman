#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../StdAfx.h"

#include "../../constants.h"

#include "../Entity.h"

class Player : public Entity {
public:
	enum class Bonus {
		raid,

	};

public:
	bool lockKey; /** Informuje nas ¿e klawisz ruchu jest wcisniety **/
	bool lockMovement; /** Iformuje nas czy klawisze akcji sa zablokowane **/

private:
	/** Do autometycznego poruszania siê **/
	std::queue<sf::Vector2f> distanceToGoQueue;
	bool isGoing;
	bool goingDone;
	float distanceToGo;

	int bombAmount;
	int maxBombAmount;

	int explosionLength;

	int healthAmount;
	int maxHealthAmount;

	int totalScores;

	bool immortal;
	float immortalTime;

	/** Do mrugania gracza po stracie ¿ycia **/
	float blinkingTime;
	float blinkingValue;
	float blinkingSign;

	sf::Vector2f hitboxOffset; /** Przesuniecie hitbox'a odnosnie ruchu w prawo **/

public:
	Player(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Player();

	EntityType getType() const { return EntityType::player; }

    void addScores(int scores) { totalScores += scores; }
    void setScores(int scores) { totalScores = scores; }
    int getScores() const { return totalScores; }

    void update(float dt);
	void draw(float dt);

	void putBomb();

	int getBombAmount() const { return bombAmount; }
	void setBombAmount(int targetValue);

	int getHealthAmount() const { return healthAmount; }
	void setHealthAmount(int targetValue);

	void looseLife();
    bool isImmortal() const { return immortal; }

    void goLeft()  { setXVelocity( -getDefaultXVelocity() ); state = EntityState::goLeft;  left->play(); hitboxOffset = sf::Vector2f(0, 0); }
   	void goRight() { setXVelocity(  getDefaultXVelocity() ); state = EntityState::goRight; right->play(); hitboxOffset = sf::Vector2f(8, 0); }
   	void goTop()   { setYVelocity( -getDefaultYVelocity() ); state = EntityState::goTop;   top->play();   hitboxOffset = sf::Vector2f(0, 0);}
   	void goDown()  { setYVelocity(  getDefaultYVelocity() ); state = EntityState::goDown;  down->play();  hitboxOffset = sf::Vector2f(0, 0);}

   	void stopLeft()  { setXVelocity(0); state = EntityState::stand; left->stop();  sprite = left->getSprite(); lockKey = false;}
   	void stopRight() { setXVelocity(0); state = EntityState::stand; right->stop(); sprite = right->getSprite(); lockKey = false; }
   	void stopTop()   { setYVelocity(0); state = EntityState::stand; top->stop();   sprite = top->getSprite(); lockKey = false;}
   	void stopDown()  { setYVelocity(0); state = EntityState::stand; down->stop();  sprite = down->getSprite(); lockKey = false;}

   	void stopMovement() { setVelocity(0, 0); state = EntityState::stand; left->stop(); right->stop(); top->stop(); down->stop(); }

   	void going(float dt);
   	void goingToCenter();

   	int getExplosionLength() const { return explosionLength; }
   	void setExplosionLength(int targetValue);

   	Hitbox getHitbox() const {
   		return Hitbox(
   				sf::Vector2f(position.x, position.y) + hitboxOffset,
   				sf::Vector2f(position.x + sd.dimensions.x, position.y - sd.dimensions.y / 2) + hitboxOffset);
   	}

	Hitbox getNextHitbox(float dt) const {
		return Hitbox(
				sf::Vector2f(getNextXPosition(dt), getNextYPosition(dt)) + hitboxOffset,
				sf::Vector2f(getNextXPosition(dt) + sd.dimensions.x, getNextYPosition(dt) - sd.dimensions.y / 2) + hitboxOffset);
	}

   	Hitbox getNextHorizontalHitbox(float dt) const {
   		return Hitbox(
   				sf::Vector2f(getNextXPosition(dt), position.y) + hitboxOffset,
   				sf::Vector2f(getNextXPosition(dt) + sd.dimensions.x, position.y - sd.dimensions.y / 2) + hitboxOffset);
	}

	Hitbox getNextVerticalHitbox(float dt) const {
		return Hitbox(
				sf::Vector2f(position.x, getNextYPosition(dt)) + hitboxOffset,
				sf::Vector2f(position.x, getNextYPosition(dt) - sd.dimensions.y / 2) + hitboxOffset);
	}
};

#endif /*__PLAYER_H__*/
