#include "World.h"

#include "../Renderer/Window.h"
#include "../Renderer/Sprite.h"

#include "Entity/RampDown.h"
#include "Entity/RampLeft.h"
#include "Entity/RampRight.h"
#include "Entity/RampTop.h"
#include "Entity/Stone.h"
#include "Entity/Bracket.h"
#include "Entity/Glimmer.h"

/***********************************************************************************
 World :: methods
 *********************/
World::World() {
	setWindowDimensions();

	floorData = Sprite::instance()->getSpriteData("FloorDark");
	floorSprite = nullptr;

	mapDimensions = sf::Vector2i(windowDimensions.x / floorData.dimensions.x,
			                     windowDimensions.y / floorData.dimensions.y - 2);

	std::cerr << "X: " << mapDimensions.x << " Y: "<< mapDimensions.y << std::endl;
	map.setSize(mapDimensions.x, mapDimensions.y);
}

void World::drawFloor() {
	if(floorSprite == nullptr) {
		sf::Sprite darkTile   = Sprite::instance()->getSprite("FloorDark");
		sf::Sprite brightTile = Sprite::instance()->getSprite("FloorBright");

		uint wNum = mapDimensions.x;
		uint hNum = mapDimensions.y + 2;

		sf::Vector2f offset(floorData.dimensions.x, floorData.dimensions.y);

		sf::Vector2f darkTilePosition   = sf::Vector2f(0, -offset.y);
		sf::Vector2f brightTilePosition = sf::Vector2f(0, -offset.y);

		for(int i = 0; i < hNum + 1; ++i) {
			darkTilePosition.x  = -3 * offset.x;
			darkTilePosition.y += offset.y;

			brightTilePosition.x  = -2 * offset.x;
			brightTilePosition.y += offset.y;

			if(i % 2) {
				darkTilePosition.x   += offset.x;
				brightTilePosition.x += offset.x;
			}

			for(int j = 0; j < wNum / 2 + 2; ++j) {
				darkTilePosition.x += 2 * offset.x;
				brightTilePosition.x += 2 * offset.x;

				darkTile.SetPosition(darkTilePosition);
				brightTile.SetPosition(brightTilePosition);

				Window::instance()->getRW()->Draw(darkTile);
				Window::instance()->getRW()->Draw(brightTile);
			}
		}

		sf::Sprite spots = Sprite::instance()->getSprite("FloorStop");
		int x = sf::Randomizer::Random(0, Sprite::instance()->getSpriteData("FloorStop").dimensions.x - Window::instance()->getWidth());
		int y = sf::Randomizer::Random(0, Sprite::instance()->getSpriteData("FloorStop").dimensions.y - Window::instance()->getHeight());

		spots.SetPosition(-x, y + Window::instance()->getHeight());
		Window::instance()->getRW()->Draw(spots);

		uint n = sf::Randomizer::Random(0, wNum);

		sf::Sprite shadow = Sprite::instance()->getSprite("FloorShadow");

		for(uint i = 0, x, y; i < n; ++i) {
			x = sf::Randomizer::Random(0, wNum);
			y = sf::Randomizer::Random(0, hNum);

			shadow.SetPosition(offset.x * x, offset.y * y);
			Window::instance()->getRW()->Draw(shadow);
		}

		newSpriteImg = Window::instance()->getRW()->Capture();
		newSpriteImg.SetSmooth(false);

		floorSprite = new sf::Sprite(newSpriteImg);
	} else
		Window::instance()->getRW()->Draw(*floorSprite);
}

void World::loadWorld(unsigned int id) {
	map.generate();

	/* floorData.dimensions -- Vector2i(width,height) of one tile */

	floorStartPos.x = 0;
	floorStartPos.y = 150;

	LOG("map2");

	MapGen::ElementType *board = map.getMap();

	LOG("map1");

	for(int y = 0; y < mapDimensions.y; ++y) {
		for(int x = 0; x < mapDimensions.x; ++x) {
			if(board[ID(x, y)] == MapGen::ElementType::stone) {
				LOG("STONE");
				LOG(ID(x, y));
				world[ID(x, y)].insert(std::make_pair(LayerType::LAYER_STONES, new Stone(ID(x, y),
						sf::Vector2f(
								x * floorData.dimensions.x + floorStartPos.x,
								y * floorData.dimensions.y + floorStartPos.y
						)
			    )));
				LOG("STONE_END");
			}

			if(board[ID(x, y)] == MapGen::ElementType::box) {
				LOG("BOX");
				LOG(ID(x, y));
				world[ID(x, y)].insert(std::make_pair(LayerType::LAYER_BLOCKS, new Bracket(ID(x, y),
						sf::Vector2f(
								x * floorData.dimensions.x + floorStartPos.x,
								y * floorData.dimensions.y + floorStartPos.y
						)
			    )));
				LOG("BOX_END");
			}

			if(board[ID(x, y)] == MapGen::ElementType::characters) { // Player
				LOG("PLAYER_END");
				LOG(ID(x, y));
				// Player is placed in the middle of tile (j, i)
				player.push_back(new Player(ID(x, y),
					sf::Vector2f(
							x * floorData.dimensions.x + floorStartPos.x,
							y * floorData.dimensions.y + floorStartPos.y
							//floorStartPos.x	+ (x * floorData.dimensions.x - x) - floorData.dimensions.x / 2,
						//floorStartPos.y	+ (y * floorData.dimensions.y - y) - floorData.dimensions.y / 2
					)
				));
				/* floorStartPos -- bottom-left corner of Tile(0,0)
				 * floorData.dimensions -- width,height of one tile
				 * `- j` is used to counter one-pixel offset */
				LOG("PLAYER_END");

				playerPos.push_back(sf::Vector2i(x, y));

				world[ID(x, y)].insert(std::make_pair(LayerType::LAYER_CHARACTERS, player.back()));
			}

			if(board[ID(x, y)] == MapGen::ElementType::exit) { // Player
				world[ID(x, y)].insert(std::make_pair(LayerType::LAYER_CHARACTERS, new Glimmer(this, ID(x, y),
										sf::Vector2f(
												x * floorData.dimensions.x + floorStartPos.x,
												y * floorData.dimensions.y + floorStartPos.y
										)
							    )));
			}
		}
	}

	LOG("load");
}

void World::setWindowDimensions() {
	windowDimensions.x = Window::instance()->getWidth();
	windowDimensions.y = Window::instance()->getHeight();
}

void World::draw(float dt) {
	drawFloor();

	worldIterator worldIt = world.begin();
	entityIterator entityIt;

	while(worldIt != world.end()) {
		entityIt = worldIt->second.begin();

		while(entityIt != worldIt->second.end()) {
			if(entityIt->second->remove) {
				delete entityIt->second;
				entityIt->second = nullptr;
			}

			// Wywolanie metody wylaczone z if'a znajdujacego sie wyzej na wypadek gdyby entity zostal usuniety z listy gdzies indziej
			if(entityIt->second == nullptr)
				entityIt = worldIt->second.erase(entityIt);

			else {
				entityIt->second->draw(dt);
				entityIt->second->update(dt);

				++entityIt;
			}
		}
		++worldIt;
	}
}

/// Return field containing this vector
sf::Vector2i World::getNField(sf::Vector2f pos) {
	pos.x -= floorStartPos.x;
	pos.y -= floorStartPos.y;

	int x = pos.x / (floorData.dimensions.x - 1);
	int y = pos.y / (floorData.dimensions.y - 1);

  return sf::Vector2i(x, y+1);
}

sf::Vector2i World::getNField(float x, float y) {
  return getNField(sf::Vector2f(x, y));
}

sf::Vector2i World::getPixelPosition(sf::Vector2i pos) {
	pos.y *= (floorData.dimensions.y - 1);
	pos.x *= (floorData.dimensions.x - 1);

	pos.x += floorStartPos.x;
	pos.y += floorStartPos.y;
  return pos;
}

sf::Vector2i World::getPixelPosition(float x, float y) {
  return getPixelPosition(sf::Vector2i(x, y));
}

sf::Vector2i World::getPixelPosition(int id) {
	int y = floor(id / mapDimensions.x);
	int x = id - y * mapDimensions.x;

  return getPixelPosition(sf::Vector2i(x, y));
}
