#ifndef __WORLD_H__
#define __WORLD_H__

#include "../StdAfx.h"

#include "../Renderer/Window.h"
#include "../Renderer/Sprite.h"

#include "Entity.h"
#include "Map.h"
#include "Aabb.h"

#include "Entity/Player.h"
#include "Entity/RampDown.h"
#include "Entity/RampLeft.h"
#include "Entity/RampRight.h"
#include "Entity/RampTop.h"
#include "Entity/Stone.h"
#include "Entity/Bracket.h"
#include "Entity/Bomb.h"
#include "Bac.h"

class Player;
class Entity;
class Bomb;

class World {
public:
	std::vector<Player*> player;
	typedef std::vector<Player*>::iterator playerIterator;

	std::vector<Bomb*> bomb;
	//typedef std::vector<Bomb*>::iterator bombIterator;

	std::map<int, std::map<int, Entity*> > world;

	sf::Vector2i mapDimensions;

	SpriteData floorData;

private:
    Map map;

    //std::map<int, std::map<int, Entity*> > world;
    typedef std::map<int, std::map<int, Entity*> >::iterator worldIterator;
    typedef std::map<int, Entity*>::iterator entityIterator;

    //std::vector<Player*> player;
//    typedef std::vector<Player*>::iterator playerIterator;

    std::vector<sf::Vector2i> playerPos;

    sf::Vector2f windowDimensions;
	//sf::Vector2i mapDimensions;

	sf::Vector2i backgroundStartPos;
	sf::Vector2i floorStartPos;

    // Mala optymalizacja
	SpriteData backgroundData;
	//SpriteData floorData;

	sf::Image newBackgroundImg;
	sf::Image newSpriteImg;
	sf::Sprite *backgroundSprite;
	sf::Sprite *floorSprite;

public:
    World();

    void loadWorld(std::string title);
    void loadWorld(unsigned int id);

    Player* getPlayer(unsigned int id);

    void draw(float dt);

    sf::Vector2i getNField(sf::Vector2f pos);
    sf::Vector2i getNField(float x, float y);

    sf::Vector2i getFloorStartPosition() { return floorStartPos; }
    sf::Vector2i getPlayerPos(int i) { return playerPos.at(i); }
    void setPlayerPos(int i, sf::Vector2i newPos) { playerPos.at(i) = newPos; }

    void deleteFirstBomb() { delete bomb.front(); }

public:
    void drawBackground();
	void drawFloor();

};

#endif /*__WORLD_H__*/
