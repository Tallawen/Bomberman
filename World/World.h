#ifndef __WORLD_H__
#define __WORLD_H__

#include "../StdAfx.h"

#include "../Renderer/SpriteManager.h"

#include "../Game.h"

#include "MapGen.h"

#include "Entity.h"
#include "Entity/Player.h"
#include "Entity/Manhole.h"

class Player;
class Game;
class Bomb;

class World {
public:
	enum class Direction {
		right,
		left,
		top,
		bottom
	};

public:
	std::vector<Entity*> entities;
	std::queue<Entity*> entitiesToCreate;

	sf::Vector2i mapDimensions;

	SpriteData floorData;
	Manhole *manhole;

	std::vector<int> emptyField;

private:
    MapGen map;

    sf::Vector2f windowDimensions;
	sf::Vector2i backgroundStartPos;

	/// corresponds to bottom-left corner of tile(0,0) of the map
	sf::Vector2i floorStartPos;

	sf::Image newSpriteImg;
	sf::Sprite *floorSprite;

public:
    World();

    void loadWorld(std::string title);
    void loadWorld(Game *gamePtr, unsigned int id, int level);

    void removeAndAddEntities();

    void setWindowDimensions();

    Player* getPlayer(unsigned int id);

    void draw(float dt);

public:
    void drawFloor();
    void drawWall();

};

#endif /*__WORLD_H__*/
