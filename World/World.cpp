#include "World.h"

#include "../Renderer/Window.h"

#include "Entity/Stone.h"
#include "Entity/Box.h"
#include "Entity/Bat.h"
#include "Entity/Death.h"

#include "Entity/Collectibles/HealthBonus.h"
#include "Entity/Collectibles/BombBonus.h"

/***********************************************************************************
 World :: methods
 *********************/
World::World() {
	setWindowDimensions();

	floorData = SpriteManager::instance()->getSpriteData("game.floor_dark");
	floorSprite = nullptr;

	mapDimensions = sf::Vector2i(windowDimensions.x / floorData.dimensions.x,
			                     windowDimensions.y / floorData.dimensions.y - 2);

	std::cerr << "X: " << mapDimensions.x << " Y: "<< mapDimensions.y << std::endl;
	map.setSize(mapDimensions.x, mapDimensions.y);
}

void World::drawFloor() {
	if(floorSprite == nullptr) {
		sf::Sprite darkTile   = SpriteManager::instance()->getSprite("game.floor_dark");
		sf::Sprite brightTile = SpriteManager::instance()->getSprite("game.floor_bright");

		uint wNum = mapDimensions.x;
		uint hNum = mapDimensions.y + 2;

		sf::Vector2f offset(floorData.dimensions.x, floorData.dimensions.y);

		sf::Vector2f darkTilePosition   = sf::Vector2f(0, -offset.y);
		sf::Vector2f brightTilePosition = sf::Vector2f(0, -offset.y);

		for(uint i = 0; i < hNum + 1; ++i) {
			darkTilePosition.x  = -3 * offset.x;
			darkTilePosition.y += offset.y;

			brightTilePosition.x  = -2 * offset.x;
			brightTilePosition.y += offset.y;

			if(i % 2) {
				darkTilePosition.x   += offset.x;
				brightTilePosition.x += offset.x;
			}

			for(uint j = 0; j < wNum / 2 + 2; ++j) {
				darkTilePosition.x += 2 * offset.x;
				brightTilePosition.x += 2 * offset.x;

				darkTile.SetPosition(darkTilePosition);
				brightTile.SetPosition(brightTilePosition);

				Window::instance()->getRW()->Draw(darkTile);
				Window::instance()->getRW()->Draw(brightTile);
			}
		}

		sf::Sprite spots = SpriteManager::instance()->getSprite("game.floor_spots");
		int x = sf::Randomizer::Random(0, SpriteManager::instance()->getSpriteData("game.floor_spots").dimensions.x - Window::instance()->getWidth());
		int y = sf::Randomizer::Random(0, SpriteManager::instance()->getSpriteData("game.floor_spots").dimensions.y - Window::instance()->getHeight());

		spots.SetPosition(-x, y + Window::instance()->getHeight());
		Window::instance()->getRW()->Draw(spots);

		uint n = sf::Randomizer::Random(0, wNum);

		sf::Sprite shadow = SpriteManager::instance()->getSprite("game.floor_shadow");

		for(uint i = 0, x, y; i < n; ++i) {
			x = sf::Randomizer::Random(0, wNum);
			y = sf::Randomizer::Random(0, hNum);

			shadow.SetPosition(offset.x * x, offset.y * y);
			Window::instance()->getRW()->Draw(shadow);
		}

		drawWall();

		newSpriteImg = Window::instance()->getRW()->Capture();
		newSpriteImg.SetSmooth(false);

		floorSprite = new sf::Sprite(newSpriteImg);
	} else
		Window::instance()->getRW()->Draw(*floorSprite);
}

void World::drawWall() {
	sf::Sprite sprite = SpriteManager::instance()->getSprite("game.wall");
	sprite.SetCenter(0, 0);
	sprite.SetBlendMode(sf::Blend::Alpha);

	for(int i = 0; i < windowDimensions.x; ++i) {
		sprite.SetPosition(i, 0);

		Window::instance()->getRW()->Draw(sprite);
	}

	 sprite = SpriteManager::instance()->getSprite("game.ledder");
	 sprite.SetCenter(0, 0);
	 sprite.SetPosition(sf::Randomizer::Random(600.0f, windowDimensions.x - 100.0f), 0);

	 Window::instance()->getRW()->Draw(sprite);
}

void World::loadWorld(Game *gamePtr, unsigned int id) {
	static int playerId = 0;

	for(auto it = entities.begin(); it != entities.end(); ) {
		if((*it)->getType() != Entity::EntityType::player)
			delete *it;
		else it++;

		it = entities.erase(it);
	}

	if(id == 1) map.generate(1);
	else map.generate(2);

	floorStartPos.x = 0;
	floorStartPos.y = 150;

	MapGen::ElementType *board = map.getMap();

	for(int y = 0; y < mapDimensions.y; ++y) {
		for(int x = 0; x < mapDimensions.x; ++x) {

			switch(board[y * mapDimensions.x + x]) {
			   case MapGen::ElementType::stone:
				   //entities.push_back( new Stone(sf::Vector2f(x*50 + 0, y*50 + 150), &entitiesToCreate));
				 break;

			   case MapGen::ElementType::box:
				   //entities.push_back( new Box(sf::Vector2f(x*50 + 0, y*50 + 150), &entitiesToCreate));
				 break;

			   case MapGen::ElementType::characters:
				   {
					   gamePtr->players.at(playerId)->setPosition(x*50, y*50 + 150);
					   gamePtr->players.at(playerId)->setPosition(x*50, y*50 + 150);
					   entities.push_back(gamePtr->players.at(playerId++));
				   }
				 break;

			   case MapGen::ElementType::exit:
				   //entities.push_back( new Death(sf::Vector2f(x*50 + 1, y*50 + 150 - 1), &entitiesToCreate));
				 break;

			    default:

			      break;
			}

		}
	}

	entities.push_back( new BombBonus(sf::Vector2f(115, 200), &entitiesToCreate, BombBonus::Amount::minusone));
	entities.push_back( new BombBonus(sf::Vector2f(215, 200), &entitiesToCreate, BombBonus::Amount::one));
	entities.push_back( new BombBonus(sf::Vector2f(306, 200), &entitiesToCreate, BombBonus::Amount::many));
	entities.push_back( new BombBonus(sf::Vector2f(405, 200), &entitiesToCreate, BombBonus::Amount::max));

	playerId = 0;
	map.reset();
}

void World::removeAndAddEntities() {
	for(auto it = entities.begin(); it != entities.end(); ) {
		if( !(*it)->isAlive() && ((*it)->getType() != Entity::EntityType::player) ) {
			(*it)->remove();

			delete (*it);

			it = entities.erase(it);
		} else
			++it;
	}

	while(!entitiesToCreate.empty()) {
		entities.push_back(entitiesToCreate.front());

		entitiesToCreate.pop();
	}
}

void World::setWindowDimensions() {
	windowDimensions.x = Window::instance()->getWidth();
	windowDimensions.y = Window::instance()->getHeight();
}

void World::draw(float dt) {
	drawFloor();

	std::sort(entities.begin(), entities.end(),[](Entity* a, Entity* b)->bool { return a->getY() < b->getY(); });

	for(auto it = entities.begin(); it != entities.end(); ++it) {
		(*it)->update(dt);
		(*it)->draw(dt);
	}
}
