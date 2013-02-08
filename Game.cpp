#include "Game.h"

/***********************************************************************************
 Game :: methods
 *********************/
Game::Game() : input(Window::instance()->getRW()->GetInput()) {
	world = new World;
}

void Game::startGame(int id) {
	world->loadWorld(id);
	Window::instance()->showAabb = false;

	bool gameStart = true;
	sf::Clock clock;
	sf::Event event;

	while(gameStart) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
				gameStart = false;
				Window::instance()->process(event);
			}

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Z)
				Window::instance()->showAabb = !Window::instance()->showAabb;

		}

		Window::instance()->getRW()->Clear();

		float dt = clock.GetElapsedTime();
		clock.Reset();

		world->draw(dt);

		playerControl();

		for(unsigned int i=0; i<world->player.size(); ++i)
			world->player.at(i)->checkCollisionsWorld(world);

		changePlayerField();

		Window::instance()->getRW()->Display();
	}
}

void Game::playerControl() {
	if(input.IsKeyDown(sf::Key::Down)) {
		if(!world->player.at(0)->isLock()) {
			world->player.at(0)->down();

			world->player.at(0)->setVelocity(0, 100);
		}
	} else {
		if(world->player.at(0)->goDown)
			world->player.at(0)->goDown = world->player.at(0)->lockChangeDirection = false;
	}

	if(input.IsKeyDown(sf::Key::Up)) {
		if(!world->player.at(0)->isLock()) {
			world->player.at(0)->top();

			world->player.at(0)->setVelocity(0, -100);
		}
	} else {
		if(world->player.at(0)->goTop)
			world->player.at(0)->goTop = world->player.at(0)->lockChangeDirection = false;
	}

	if(input.IsKeyDown(sf::Key::Right)) {
		if(!world->player.at(0)->isLock()) {
			world->player.at(0)->right();

			world->player.at(0)->setVelocity(100, 0);
		}
	} else {
		if(world->player.at(0)->goRight)
			world->player.at(0)->goRight = world->player.at(0)->lockChangeDirection = false;
	}

	if(input.IsKeyDown(sf::Key::Left)) {
		if(!world->player.at(0)->isLock()) {
			world->player.at(0)->left();

			world->player.at(0)->setVelocity(-100, 0);
		}
	} else {
		if(world->player.at(0)->goLeft)
			world->player.at(0)->goLeft = world->player.at(0)->lockChangeDirection = false;
	}

	if(input.IsKeyDown(sf::Key::Space)) {
		world->player.at(0)->setBomb(world);
	}

 //TODO:
	if(world->player.size() > 1) {

	if(input.IsKeyDown(sf::Key::S)) {
			if(!world->player.at(1)->isLock()) {
				world->player.at(1)->down();

				world->player.at(1)->setVelocity(0, 100);
			}
		} else {
			if(world->player.at(1)->goDown)
				world->player.at(1)->goDown = world->player.at(1)->lockChangeDirection = false;
		}

		if(input.IsKeyDown(sf::Key::W)) {
			if(!world->player.at(1)->isLock()) {
				world->player.at(1)->top();

				world->player.at(1)->setVelocity(0, -100);
			}
		} else {
			if(world->player.at(1)->goTop)
				world->player.at(1)->goTop = world->player.at(1)->lockChangeDirection = false;
		}

		if(input.IsKeyDown(sf::Key::D)) {
			if(!world->player.at(1)->isLock()) {
				world->player.at(1)->right();

				world->player.at(1)->setVelocity(100, 0);
			}
		} else {
			if(world->player.at(1)->goRight)
				world->player.at(1)->goRight = world->player.at(1)->lockChangeDirection = false;
		}

		if(input.IsKeyDown(sf::Key::A)) {
			if(!world->player.at(1)->isLock()) {
				world->player.at(1)->left();

				world->player.at(1)->setVelocity(-100, 0);
			}
		} else {
			if(world->player.at(1)->goLeft)
				world->player.at(1)->goLeft = world->player.at(1)->lockChangeDirection = false;
		}

		if(input.IsKeyDown(sf::Key::Space)) {
			world->player.at(1)->setBomb(world);
		}
	}
}

void Game::changePlayerField() {
	for(unsigned int i=0; i<world->player.size(); ++i) {
		sf::Vector2i playerPosition = world->getNField(*world->player.at(i)->getPosition());

		if(playerPosition != world->getPlayerPos(i)) {
			world->world[playerPosition.y * world->mapDimensions.x + playerPosition.x][World::DisplayOrder::player] = world->world[world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x][World::DisplayOrder::player];

			if(world->world.size() == 1)
				world->world.erase(world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x);
			else
				world->world.at(world->getPlayerPos(i).y * world->mapDimensions.x + world->getPlayerPos(i).x).erase(World::DisplayOrder::player);

			world->setPlayerPos(i, sf::Vector2i(playerPosition.x, playerPosition.y));
		}
	}
}
