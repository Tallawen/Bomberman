#ifndef __WORLD_H__
#define __WORLD_H__

#include "../StdAfx.h"

#include "../Renderer/Sprite.h"
#include "../Renderer/Layers.h"

#include "MapGen.h"

#include "Entity.h"
#include "Entity/Player.h"

class Player;
//class Entity;

class World {
public:
	enum class Direction {
		right,
		left,
		top,
		bottom
	};

public:
	std::vector<Player*> player;
	typedef std::vector<Player*>::iterator playerIterator;

	/**
	 * std::map<int [a], std::map<int [b], Entity* [c]> >
	 * [a] - id tablicy dwuwymiarowej w konwencji y*width+x
	 * [b] - kolejnosc wyswietlania elementow znajdujacych sie na danym polu (stala)
	 *       (kazda kolejnosc moze miec przypisany tylko jeden element)
	 * [c] - wskaznik na element który znajduje siê na danym polu i na danej kolejnosci
	 *
	 */
	std::map<int, std::multimap<LayerType, Entity*> > world;

	sf::Vector2i mapDimensions;

	SpriteData floorData;

private:
    MapGen map;

    typedef std::map<int, std::map<LayerType, Entity*> >::iterator worldIterator;
    typedef std::map<LayerType, Entity*>::iterator entityIterator;

    std::vector<sf::Vector2i> playerPos;

    sf::Vector2f windowDimensions;
	sf::Vector2i backgroundStartPos;

	/// corresponds to bottom-left corner of tile(0,0) of the map
	sf::Vector2i floorStartPos;

    // Mala optymalizacja
	//SpriteData floorData;

	sf::Image newSpriteImg;

	sf::Sprite *floorSprite;

public:
    World();

    void loadWorld(std::string title);
    void loadWorld(unsigned int id);

    void setWindowDimensions();

    Player* getPlayer(unsigned int id);

    void draw(float dt);

    /**
     * Zwraca id bloku w tablicy [world] na podstawie wspolrzednych z planszy
     *
     */
    sf::Vector2i getNField(sf::Vector2f pos);
    sf::Vector2i getNField(float x, float y);

    /**
     * Zwraca wspolrzedne na planszy na podstawie x i y tablicy
     *
     */
    sf::Vector2f getPixelPosition(sf::Vector2f pos);
    sf::Vector2f getPixelPosition(float x, float y);

    /**
     * Zwraca wspolrzedne na planszy na podstawie id tablicy
     *
     */
    sf::Vector2f getPixelPosition(int id);

    sf::Vector2i getFloorStartPosition() { return floorStartPos; }
    sf::Vector2i getPlayerPos(int i) { return playerPos.at(i); }

    void setPlayerPos(int i, sf::Vector2i newPos) { playerPos.at(i) = newPos; }

    int ID(int x, int y) const { return y * mapDimensions.x + x; }

    uint xByID(uint id) const { return id % mapDimensions.x; }

    uint yByID(uint id) const { return id / mapDimensions.x; }

public:
    void drawFloor();
    void drawWall();

};

#endif /*__WORLD_H__*/
