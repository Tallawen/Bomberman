#include "World.h"

/***********************************************************************************
 World :: methods
 *********************/
World::World() {
	/* Load Texture */
	Sprite::instance()->insertTexture("Data/Block.png");
	Sprite::instance()->insertTexture("Data/Player_White.png", true);
	Sprite::instance()->insertTexture("Data/PlayerGoRight2.png", true);
	Sprite::instance()->insertTexture("Data/PlayerGoLeft.png", true);
	Sprite::instance()->insertTexture("Data/PlayerGoTop.png", true);
	Sprite::instance()->insertTexture("Data/Bomb.png", true);

	/* Load Sprite */
	Sprite::instance()->insertSprite("Background", "Block", 51, 40, 0, 21);
	Sprite::instance()->insertSprite("Floor", "Block", 51, 40, 51, 21);
	Sprite::instance()->insertSprite("Stone", "Block", 51, 60, 102, 1);
	Sprite::instance()->insertSprite("Bracket", "Block", 51, 60, 153, 1);
	Sprite::instance()->insertSprite("RampTop", "Block", 51, 41, 204, 20);
	Sprite::instance()->insertSprite("RampDown", "Block", 51, 61, 255, 0);
	Sprite::instance()->insertSprite("RampLeft", "Block", 51, 59, 306, 2);
	Sprite::instance()->insertSprite("RampRight", "Block", 51, 59, 357, 2);
	Sprite::instance()->insertSprite("DoorClose", "Block", 51, 60, 408, 1);
	Sprite::instance()->insertSprite("DoorOpen", "Block", 51, 34, 459, 27);

	Sprite::instance()->insertSprite("Bomb", "Bomb", 23, 25, 0, 0);

	Sprite::instance()->insertSprite("Player_White_Down", "Player_White", 27, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Right", "PlayerGoRight2", 33, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Left", "PlayerGoLeft", 32, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Top", "PlayerGoTop", 27, 41, 0, 0, true, 15);

	/* Insert Map */
	map.insertMap("Test", "test.map");

	/* Set Data */
	windowDimensions.x = Window::instance()->getWidth();
	windowDimensions.y = Window::instance()->getHeight();

	backgroundData = Sprite::instance()->getSpriteData("Background");
	floorData = Sprite::instance()->getSpriteData("Floor");

	backgroundStartPos = sf::Vector2i(0, 0);

	backgroundSprite = floorSprite = NULL;
}

void World::drawBackground() {
	if(backgroundSprite == NULL) {
		sf::Sprite sprite = Sprite::instance()->getSprite("Background");

		Window::instance()->getRW()->Clear();

		int h = backgroundStartPos.y;
		int w = backgroundStartPos.x;

		while(h < windowDimensions.y + backgroundData.dimensions.y) {
			 w = backgroundStartPos.x;
			 --h;
			while(w < windowDimensions.x) {
				--w;
				sprite.SetPosition(w, h);
				Window::instance()->getRW()->Draw(sprite);
				w += backgroundData.dimensions.x;
			}
			h += backgroundData.dimensions.y;
		}

		newBackgroundImg = Window::instance()->getRW()->Capture();
		newBackgroundImg.SetSmooth(false);

		backgroundSprite = new sf::Sprite(newBackgroundImg);
	} else
		Window::instance()->getRW()->Draw(*backgroundSprite);
}

void World::drawFloor() {
	if(floorSprite == NULL) {
		sf::Sprite sprite = Sprite::instance()->getSprite("Floor");

		Window::instance()->getRW()->Clear();

		int w = floorStartPos.x + floorData.dimensions.x;
		int h = floorStartPos.y;

		int x = mapDimensions.x - 2;
		int y = mapDimensions.y - 2;

		for(int i=0; i < y; ++i) {
			 w = floorStartPos.x + floorData.dimensions.x;
			 --h;
			for(int j=0; j < x; ++j) {
				--w;
				sprite.SetPosition(w, h);
				Window::instance()->getRW()->Draw(sprite);
				w += floorData.dimensions.x;
			}
			h += floorData.dimensions.y;
		}

		newSpriteImg = Window::instance()->getRW()->Capture();
		newSpriteImg.SetSmooth(false);

		floorSprite = new sf::Sprite(newSpriteImg);
		floorSprite->SetSubRect(sf::IntRect(floorStartPos.x + floorData.dimensions.x,  floorStartPos.y - floorData.dimensions.y, w, h-floorData.dimensions.y));
		floorSprite->SetPosition(floorStartPos.x + floorData.dimensions.x, floorStartPos.y);
	} else
		Window::instance()->getRW()->Draw(*floorSprite);
}

void World::loadWorld(unsigned int id) {
	map.loadMap(id);

	mapDimensions = sf::Vector2i(map.getWidth(), map.getHeight());

	floorStartPos.x = windowDimensions.x;
	floorStartPos.x /= floorData.dimensions.x;
	floorStartPos.x = ceil(floorStartPos.x);
	floorStartPos.x = (floorStartPos.x - mapDimensions.x) / 2 * floorData.dimensions.x + backgroundStartPos.x - (floorStartPos.x - mapDimensions.x) / 2 - 1;

	floorStartPos.y = windowDimensions.y;
	floorStartPos.y /= floorData.dimensions.y;
	floorStartPos.y = ceil(floorStartPos.y);
	floorStartPos.y = (floorStartPos.y - mapDimensions.y) / 2 * floorData.dimensions.y + backgroundStartPos.y + floorData.dimensions.y - (floorStartPos.y - mapDimensions.y) / 2 - 2;

	unsigned int *board = map.getMap();

	for(int i=0; i < mapDimensions.y; ++i) {
		for(int j=0; j < mapDimensions.x; ++j) {
			if(board[i*mapDimensions.x+j] == 1) /* TODO: Zmienic porównywanie na bardziej dynamiczne */ // RampTop
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampTop(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			if(board[i*mapDimensions.x+j] == 2) // RampBottom
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampDown(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			if(board[i*mapDimensions.x+j] == 3) // RampLeft
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampLeft(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			if(board[i*mapDimensions.x+j] == 4) // RampRight
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampRight(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			//if(board[i*mapDimensions.x+j] == 5) ;// DoorClose
				//world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampLeft(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x, i*floorData.dimensions.y + floorStartPos.y))));

			//if(board[i*mapDimensions.x+j] == 6) ;// DoorOpen
				//world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new RampRight(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x, i*floorData.dimensions.y + floorStartPos.y))));

			if(board[i*mapDimensions.x+j] == 7) // Stone
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new Stone(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			if(board[i*mapDimensions.x+j] == 8) // Bracket
				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::block, new Bracket(i*mapDimensions.y, 0, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - j, i*floorData.dimensions.y + floorStartPos.y - i))));

			if(board[i*mapDimensions.x+j] == 9) { // Player
				player.push_back(new Player(i*mapDimensions.y, 4, sf::Vector2f(j*floorData.dimensions.x + floorStartPos.x - (floorData.dimensions.x - Sprite::instance()->getSpriteData("Player_White_Down").dimensions.x) / 2, i*floorData.dimensions.y + floorStartPos.y)));
				playerPos.push_back(sf::Vector2i(j, i));

				world[i*mapDimensions.x+j].insert(std::make_pair(DisplayOrder::player, player.back()));
			}
		}
	}
}

void World::loadWorld(std::string title) {
	loadWorld(map.getId(title));
}

void World::draw(float dt) {
	drawBackground();
	drawFloor();

	worldIterator wI = world.begin();
	entityIterator eI;

	while(wI != world.end()) {
		eI = wI->second.begin();

		while(eI != wI->second.end()) {
			if(eI->second != NULL) {
				eI->second->draw(dt);
				eI->second->update(dt);
			}
			++eI;
		}
		++wI;
	}

	bomb();
}

void World::bomb() {
	if(!bombs.empty()) {
		if(!bombs.front()->isLive()) {
			delete bombs.front();
			bombs.erase(bombs.begin());
		}
	}
}

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
