#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../StdAfx.h"

#include "../Renderer/SpriteManager.h"
#include "../Renderer/Animation.h"
#include "../Renderer/Window.h"

#include "Hitbox.h"

class World;

class Entity {
public:

	enum class EntityType {
		none,
		stone,
		player,
		box,
		enemy,
		door_open,
		door_colse,
		bomb,
		explosion,
		collectible
	};

	enum class EntityState {
		stand,
		goLeft,
		goRight,
		goDown,
		goTop
	};

	enum class EntityLayer {
		layer_background1 = 0,
		layer_background2,
		layer_background3,
		layer_background4,
		layer_background5,
		layer_background6
	};

protected:
	std::queue<Entity*> *entitiesToCreate;

	EntityLayer layer;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f defaultVelocity;
	//sf::Vector2f acceleration;

	bool isDead;

	EntityState state;
	EntityType type;

	sf::Sprite sprite;
	SpriteData sd;

	Animation *left;
	Animation *right;
	Animation *top;
	Animation *down;
	Animation *stop;

	bool canGoLeft;
	bool canGoRight;
	bool canGoTop;
	bool canGoDown;

public:
	explicit Entity(float x, float y, float defVelocityX, float defVelocityY, std::queue<Entity*> *_entitiesToCreate);

	virtual ~Entity() { }

	virtual EntityType getType() const = 0;
	virtual EntityState getState() const { return state; }
	virtual int getScoresWhenKilled() const { return 0; }

	EntityLayer getLayer() const { return layer; }

	virtual void update(float dt);
	virtual void draw(float dt);

    bool isAlive() const { return !isDead; }
    void dead() { isDead = true; }

    float getX() const { return position.x; }
    float getY() const { return position.y; }
    sf::Vector2f getPosition() const { return position; }

    virtual float getNextXPosition(float dt) const { return position.x + velocity.x * dt; }
    virtual float getNextYPosition(float dt) const { return position.y + velocity.y * dt; }
    virtual sf::Vector2f getNextPosition(float dt) const { return position + velocity * dt; }

    void setX(float x) { position.x = x; }
    void setY(float y) { position.y = y; }
    void setPosition(float x, float y) { position = sf::Vector2f(x, y); }
    void setPosition(sf::Vector2f newPosition) { position = newPosition; }

    float getXVelocity() const { return velocity.x; }
    float getYVelocity() const { return velocity.y; }
    sf::Vector2f getVelocity() const { return velocity; }

    float getDefaultXVelocity() const { return defaultVelocity.x; }
    float getDefaultYVelocity() const { return defaultVelocity.y; }
    sf::Vector2f getDefaultVelocity() const { return defaultVelocity; }

    void setXVelocity(float velocityX) { velocity.x = velocityX; }
    void setYVelocity(float velocityY) { velocity.y = velocityY; }
    void setVelocity(float velocityX, float velocityY) { velocity = sf::Vector2f(velocityX, velocityY); }
    void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }

    void negateXVelocity() { velocity.x = -velocity.x; }
    void negateYVelocity() { velocity.y = -velocity.y; }
    void negateVelocity()  { negateXVelocity(); negateYVelocity(); }

    virtual void goLeft()  { setXVelocity( -getDefaultXVelocity() ); state = EntityState::goLeft; }
    virtual void goRight() { setXVelocity(  getDefaultXVelocity() ); state = EntityState::goRight; }
    virtual void goTop()   { setYVelocity( -getDefaultYVelocity() ); state = EntityState::goTop; }
    virtual void goDown()  { setYVelocity(  getDefaultYVelocity() ); state = EntityState::goDown; }

    virtual void stopLeft()  { setXVelocity(0); state = EntityState::stand; }
    virtual void stopRight() { setXVelocity(0); state = EntityState::stand; }
    virtual void stopTop()   { setYVelocity(0); state = EntityState::stand; }
    virtual void stopDown()  { setYVelocity(0); state = EntityState::stand; }

    virtual void stopMovement() { setVelocity(0, 0); state = EntityState::stand; }

    virtual void changeMovement() {
    	switch(sf::Randomizer::Random(0, 3)) {
    	    case 0:
    	    	goLeft();
    	      break;

    	    case 1:
    	    	goRight();
    	      break;

    	    case 2:
    	    	goTop();
    	      break;

    	    case 3:
    	    	goDown();
    	      break;
    	}
    }

    SpriteData getSpriteDate() const { return sd; }

    void ForbidGoingLeft()  { canGoLeft  = false; }
    void ForbidGoingRight() { canGoRight = false; }
    void ForbidGoingTop()   { canGoTop   = false; }
    void ForbidGoingDown()  { canGoDown  = false; }

    virtual void remove() {
    	isDead = true;

    	if(left != nullptr)
    		delete left;

    	if(right != nullptr)
    		delete right;

    	if(top != nullptr)
    		delete top;

    	if(down != nullptr)
    		delete down;

    	if(stop != nullptr)
    		delete stop;

    	left = nullptr;
    	right = nullptr;
    	top = nullptr;
    	down = nullptr;
    	stop = nullptr;
    }

    virtual void setDefaultMovement()  { canGoLeft = canGoRight = canGoTop = canGoDown = true; }

    virtual Hitbox getHitbox() const {
    	return Hitbox( sf::Vector2f(
    			           position.x, position.y),
    			           sf::Vector2f(position.x + sd.dimensions.x, position.y - sd.dimensions.y)
    	               );
    }

    virtual Hitbox getNextHitbox(float dt) const {
        	return Hitbox(
        		      sf::Vector2f(getNextXPosition(dt), getNextYPosition(dt)),
        		      sf::Vector2f(getNextXPosition(dt) + sd.dimensions.x, getNextYPosition(dt) - sd.dimensions.y)
        	       );
    }

    virtual Hitbox getNextHorizontalHitbox(float dt) const {
        	return Hitbox(
        		      sf::Vector2f(getNextXPosition(dt), position.y - sd.dimensions.y / 2 + 4),
        		      sf::Vector2f(getNextXPosition(dt) + sd.dimensions.x, position.y - sd.dimensions.y / 2 - 4)
        	       );
    }

    virtual Hitbox getNextVerticalHitbox(float dt) const {
    	    return Hitbox(
    	    	      sf::Vector2f(position.x + sd.dimensions.x / 2 - 4, getNextYPosition(dt)),
           		      sf::Vector2f(position.x + sd.dimensions.x / 2 + 4, getNextYPosition(dt) - sd.dimensions.y)
           	       );
     }

    bool IsAnyFieldBelowMe(double dt, World *world) const;
    bool IsAnyFieldAboveMe(double dt, World *world) const;
    bool IsAnyFieldOnLeft(double dt, World *world) const;
    bool IsAnyFieldOnRight(double dt, World *world) const;
    bool DoFieldsEndOnLeft(double dt, World *world) const;
    bool DoFieldsEndOnRight(double dt, World *world) const;

    /*void GetCurrentTile(size_t *x, size_t *y) const {
        const size_t v_tiles_count = Engine::Get().Renderer()->GetVerticalTilesOnScreenCount();
        *y = v_tiles_count - (GetAabb().GetMinY() + GetAabb().GetMaxY()) / 2;
        *x = GetX() + GetBasicAabb().GetMaxX() / 2;
    }*/
};

#endif /*__ENTITY_H__*/

