#include "Game.h"

#include "Constants.h"

#include "Renderer/Window.h"

/***********************************************************************************
 Game :: methods
 *********************/
Game::Game() : input(Window::instance()->getRW()->GetInput()) {
	world = new World;
}

void Game::startGame(int id) {
	world->setWindowDimensions();

	world->loadWorld(id);
	Window::instance()->showHitbox = false;

	bool gameStart = true;
	sf::Clock clock;
	sf::Event event;

	while(gameStart) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
				gameStart = false;

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Z)
				// Press Z while playing to toggle hitboxes
				Window::instance()->showHitbox = !Window::instance()->showHitbox;

			Window::instance()->process(event);
			playerControl(event);
		}

		Window::instance()->getRW()->Clear();

		float dt = clock.GetElapsedTime();
		clock.Reset();

		world->draw(dt);

		playerControlRealtime();

		for(unsigned int i=0; i<world->player.size(); ++i)
			world->player.at(i)->detectTileCollisions(world);

		changePlayerField();

		Window::instance()->getRW()->Display();
	}
}

void inline Game::playerControl(sf::Key::Code keyCode, sf::Vector2f velocity, Player* player, World::Direction direction) {
	void (Player::*ptrFun)() = nullptr;
	bool *move;

	switch(direction) {
	    case World::Direction::right:
	    	ptrFun = &Player::right;
	    	move = &player->goRight;
	      break;

	    case World::Direction::left:
	    	ptrFun = &Player::left;
	    	move = &player->goLeft;
	      break;

	    case World::Direction::top:
	    	ptrFun = &Player::top;
	    	move = &player->goUp;
	      break;

	    case World::Direction::bottom:
	    	ptrFun = &Player::down;
	    	move = &player->goDown;
	      break;
	}

	if(input.IsKeyDown(keyCode)) {
		if(!player->isLock()) {
			(player->*ptrFun)();
			player->setVelocity(velocity);
		}
	} else
		if(*move)
			*move = player->lockChangeDirection = false;
}

void Game::playerControl(sf::Event &event) {
	if(world->player.size() > 0) {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
			world->player.at(0)->setBomb(world);
	}

	if(world->player.size() > 1) {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
			world->player.at(1)->setBomb(world);
	}
}

void Game::playerControlRealtime() {
	if(world->player.size() > 0) {
		playerControl(sf::Key::Down,  sf::Vector2f(0, Constants::Player::SPEED),  world->player.at(0), World::Direction::bottom);
		playerControl(sf::Key::Up,    sf::Vector2f(0, -Constants::Player::SPEED), world->player.at(0), World::Direction::top);
		playerControl(sf::Key::Right, sf::Vector2f(Constants::Player::SPEED,  0),  world->player.at(0), World::Direction::right);
		playerControl(sf::Key::Left,  sf::Vector2f(-Constants::Player::SPEED, 0), world->player.at(0), World::Direction::left);
	}

	if(world->player.size() > 1) {
		playerControl(sf::Key::S, sf::Vector2f(0, Constants::Player::SPEED),  world->player.at(1), World::Direction::bottom);
		playerControl(sf::Key::W, sf::Vector2f(0, -Constants::Player::SPEED), world->player.at(1), World::Direction::top);
		playerControl(sf::Key::D, sf::Vector2f(Constants::Player::SPEED,  0),  world->player.at(1), World::Direction::right);
		playerControl(sf::Key::A, sf::Vector2f(-Constants::Player::SPEED, 0), world->player.at(1), World::Direction::left);
	}
}

void Game::changePlayerField() {
	for(unsigned int i=0; i<world->player.size(); ++i) {
		sf::Vector2i playerPosition = world->getNField(*world->player.at(i)->getPosition());

		if(playerPosition != world->getPlayerPos(i)) {
			world->world[playerPosition.y * world->mapDimensions.x + playerPosition.x][LayerType::LAYER_CHARACTERS] = world->world[world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x][LayerType::LAYER_CHARACTERS];

			if(world->world.size() == 1)
				world->world.erase(world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x);
			else
				world->world.at(world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x).erase(LayerType::LAYER_CHARACTERS);

			world->setPlayerPos(i, sf::Vector2i(playerPosition.x, playerPosition.y));
		}
	}
}
