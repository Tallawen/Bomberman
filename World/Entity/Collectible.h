#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "../Entity.h"
#include "Player.h"

class Collectible : public Entity {
private:
	float offsetSign;
	float offsetTime;

	bool blinking;
	float blinkingValue;

	sf::Vector2f firstPosition; // podstawowa pozycja (bez ruchu)

	EntityType type;

public:
	Collectible(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate);
	~Collectible() { }

	EntityType getType() const { return type; }

	int getScoresWhenKilled() const { return 0; }

	void draw(float dt);
	void update(float dt);

    virtual void collect(Player* player) = 0;

    void remove();

private:
    void move(float dt, float time, float distance);
    void blink(float dt);

};


#endif /*__COLLECTIBLE_H__*/
