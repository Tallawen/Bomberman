#include "Game.h"

#include "Constants.h"
#include "UI.h"

#include "Renderer/Window.h"
#include "Renderer/SubWindow.h"
#include "Renderer/SoundManager.h"

#include "World/Entity/Explosion.h"

/***********************************************************************************
 Game :: methods
 *********************/
Game::Game() : input(Window::instance()->getRW()->GetInput()) {
	world = nullptr;

	players.clear();

	play = true;
	end = false;

	level = 0;
}

Game::~Game() {
	if(world != nullptr) {
		delete world;

		world = nullptr;
	}
}

void Game::init(int id) {
	if(world == nullptr)
		world = new World;

	Window::instance()->showHitbox = false;

	if(id == 1) {
		players.push_back( new Player(sf::Vector2f(0, 0), &world->entitiesToCreate));// 1 vs kom
	}

	if(id > 1) {
		players.push_back( new Player(sf::Vector2f(0, 0), &world->entitiesToCreate));
		players.push_back( new Player(sf::Vector2f(1, 1), &world->entitiesToCreate));
	}

	musics[0] = SoundManager::instance().getMusic("game.ff");
	musics[0]->Stop();
	musics[0]->SetLoop(false);
	musics[0]->SetVolume(20.0f);
	musics[1] = SoundManager::instance().getMusic("game.ffs");
	musics[1]->Stop();
	musics[1]->SetLoop(false);
	musics[1]->SetVolume(30.0f);
	musics[2] = SoundManager::instance().getMusic("game.ffd");
//	musics[2]->Stop();
//	musics[2]->SetLoop(false);
//	musics[2]->SetVolume(30.0f);

	musicId = sf::Randomizer::Random(0, 1);
	musics[musicId]->Play();

	game(id);

	musics[musicId]->Stop();
}

void Game::game(int id) {
	end = false;

	while(!end) {
		++level;

		play = true;

		sf::Clock clock;
		sf::Event event;

		UI *uiFirstPlayer = new UI;
		UI *uiFirstSecond = new UI(true);

		world->loadWorld(this, id);

		while(play) {
			if(musics[musicId]->GetStatus() == sf::Music::Status::Stopped) {
				int mTmp = musicId;

				while(mTmp == musicId)
					musicId = sf::Randomizer::Random(0, 1);

				musics[musicId]->Play();
			}

			while(Window::instance()->getRW()->GetEvent(event)) {
				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
					switch(pauseMenu()) {
					    case sf::Key::Q:
					       	end = !(play = false);
					      break;

					    case sf::Key::R:
					    	play = false;
					      break;

					    default:
					      break;
					}

					clock.Reset();
				}

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Z)
					Window::instance()->showHitbox = !Window::instance()->showHitbox;

				playerControl(event);

				Window::instance()->process(event);
			}

			Window::instance()->getRW()->Clear();

			float dt = clock.GetElapsedTime();
			clock.Reset();

			world->draw(dt);

			uiFirstSecond->drawHealthBar(players.at(1)->getHealthAmount());
			uiFirstSecond->drawBombBar(players.at(1)->getBombAmount());
			uiFirstSecond->drawFPS(dt);
			uiFirstSecond->drawBoard();

			uiFirstPlayer->drawHealthBar(players.at(0)->getHealthAmount());
			uiFirstPlayer->drawBombBar(players.at(0)->getBombAmount());
			uiFirstPlayer->drawScores(players.at(0)->getScores());
			//uiFirstPlayer->drawFPS(dt);
			uiFirstPlayer->drawBoard();

			playerControlRealtime();

			checkEntityEntityCollisions(dt);
			//checkPlayerEntitiesCollisions(0, dt);

			Window::instance()->getRW()->Display();

			world->removeAndAddEntities();

			if(!players.at(0)->isAlive() || !players.at(1)->isAlive()) end = !(play = false);
		}
	}
}

sf::Key::Code Game::pauseMenu() {
	SubWindow sW;

	sW.init(300, 300, (Window::instance()->getWidth() - 300) / 2, (Window::instance()->getHeight() - 300) / 2);

	sW.setAplha(255);

	sW.add(SpriteManager::instance()->getSprite("button.esc"), sf::Vector2i(45,  71));
	sW.add(SpriteManager::instance()->getSprite("button.r"),   sf::Vector2i(45, 133));
	sW.add(SpriteManager::instance()->getSprite("button.h"),   sf::Vector2i(45, 195));
	sW.add(SpriteManager::instance()->getSprite("button.q"),   sf::Vector2i(45, 257));

	sW.add(SpriteManager::instance()->getSprite("text.resume"),            sf::Vector2i(120,  64));
	sW.add(SpriteManager::instance()->getSprite("text.restart"),           sf::Vector2i(120, 121));
	sW.add(SpriteManager::instance()->getSprite("text.help"),              sf::Vector2i(120, 186));
	sW.add(SpriteManager::instance()->getSprite("text.exit_to_main_menu"), sf::Vector2i(120, 245));

	sW.setTransitionEffect(1);

	sf::Key::Code result = sW.show([](sf::Event &event, sf::Key::Code &result, bool &done)->void {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
			result = sf::Key::Escape;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::R) {
			result = sf::Key::R;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::H) {
			result = sf::Key::H;
			LOG("HELP!!!!..");
			done = false;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) {
			result = sf::Key::Q;
			done = true;
		}
	});

  return result;
}

void inline Game::playerControl(sf::Key::Code keyCode, Player* player, Entity::EntityState state) {
	if(!player->lockMovement) {
		void (Player::*ptrFun)() = nullptr;
		void (Player::*ptrNegFun)() = nullptr;

		switch(state) {
		    case Entity::EntityState::goRight:
		    	ptrFun = &Player::goRight;
		    	ptrNegFun = &Player::stopRight;
		      break;

		    case Entity::EntityState::goLeft:
		    	ptrFun = &Player::goLeft;
		    	ptrNegFun = &Player::stopLeft;
		      break;

		    case Entity::EntityState::goTop:
		    	ptrFun = &Player::goTop;
		    	ptrNegFun = &Player::stopTop;
		      break;

		    case Entity::EntityState::goDown:
		    	ptrFun = &Player::goDown;
		    	ptrNegFun = &Player::stopDown;
		      break;

		    default:

		      break;
		}

		if(input.IsKeyDown(keyCode)) {
			if(!player->lockKey) {
				(player->*ptrFun)();
				player->lockKey = true;
			}
		} else if(player->getState() == state && player->lockKey) {
			(player->*ptrNegFun)();
			player->lockKey = false;
			LOG("a");
		}
	}
}

void Game::playerControl(sf::Event &event) {
	if(players.size() > 0) {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space) {
			if(!players.at(0)->lockMovement)
				players.at(0)->goingToCenter();
		}
	}

	if(players.size() > 1) {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::LShift) {
			if(!players.at(1)->lockMovement)
				players.at(1)->goingToCenter();
		}
	}
}

void Game::playerControlRealtime() {
	if(players.size() > 0) {
		playerControl(sf::Key::Down,  players.at(0), Entity::EntityState::goDown);
		playerControl(sf::Key::Up,    players.at(0), Entity::EntityState::goTop);
		playerControl(sf::Key::Right, players.at(0), Entity::EntityState::goRight);
		playerControl(sf::Key::Left,  players.at(0), Entity::EntityState::goLeft);

	}
	if(players.size() > 1) {
		playerControl(sf::Key::S, players.at(1), Entity::EntityState::goDown);
		playerControl(sf::Key::W, players.at(1), Entity::EntityState::goTop);
		playerControl(sf::Key::D, players.at(1), Entity::EntityState::goRight);
		playerControl(sf::Key::A, players.at(1), Entity::EntityState::goLeft);
	}
}

void Game::checkCollisionOfOnePair(
               Entity *entityFirst, Entity::EntityType firstType,
               Entity *entitySecond, Entity::EntityType secondType, float dt) {

		if(!entityFirst->getNextHitbox(dt).collidesWith(entitySecond->getNextHitbox(dt)))
			return;

	// makro SWAP_IF pozwala zamieniæ znaczenie argumentów fst_* z snd_*
    // w ten sposób, ¿e sprawdzaj¹c kolizjê otrzymujemy wska¿niki zawsze
    // w dobrej kolejnoœci, tzn. tak, aby ka¿d¹ parê obs³ugiwaæ jeden raz

	#define SWAP_IF(type_a, type_b)  \
	            if(firstType == type_a && secondType == type_b) {  \
    	            std::swap(entityFirst, entitySecond);   \
                    std::swap(firstType, secondType);   \
	            }

    SWAP_IF(Entity::EntityType::stone, Entity::EntityType::enemy);
    SWAP_IF(Entity::EntityType::box, Entity::EntityType::enemy);
    SWAP_IF(Entity::EntityType::stone, Entity::EntityType::player);
    SWAP_IF(Entity::EntityType::box, Entity::EntityType::player);
    SWAP_IF(Entity::EntityType::enemy, Entity::EntityType::player);
    SWAP_IF(Entity::EntityType::stone, Entity::EntityType::explosion);
    SWAP_IF(Entity::EntityType::box, Entity::EntityType::explosion);
    SWAP_IF(Entity::EntityType::explosion, Entity::EntityType::player);
    SWAP_IF(Entity::EntityType::explosion, Entity::EntityType::enemy);

    // w tym miejscu wiemy, ¿e je¿eli nast¹pi³a kolizja Mush z PlayerBullet,
    // to jednostka Mush bêdzie pod fst_entity a PlayerBullet pod snd_entity

    if(firstType == Entity::EntityType::enemy && (secondType == Entity::EntityType::stone || secondType == Entity::EntityType::box)) {
    	if(entityFirst->getState() == Entity::EntityState::goDown) {
    		float newY = entitySecond->getY() - 50.0f - 0.5f;

    		entityFirst->setPosition(entityFirst->getX(), newY);
    		entityFirst->stopDown();
    	} else if(entityFirst->getState() == Entity::EntityState::goTop) {
    		float newY = entitySecond->getY() + entityFirst->getSpriteDate().dimensions.y + 0.5f;

    		entityFirst->setPosition(entityFirst->getX(), newY);
    		entityFirst->stopTop();

    	} else if(entityFirst->getState() == Entity::EntityState::goLeft) {
    		float newX = entitySecond->getX() + 50 + 0.5f;

    		entityFirst->setPosition(newX, entityFirst->getY());
    		entityFirst->stopLeft();

    	} else if(entityFirst->getState() == Entity::EntityState::goRight) {
    		float newX = entitySecond->getX() - entityFirst->getSpriteDate().dimensions.x - 0.5f;

    		entityFirst->setPosition(newX, entityFirst->getY());
    		entityFirst->stopRight();
    	}

    	entityFirst->stopMovement();

    	switch(sf::Randomizer::Random(0, 3)) {
    	    case 0:
    	    	entityFirst->goLeft();
    	      break;

    	    case 1:
    	    	entityFirst->goRight();
    	      break;

    	    case 2:
    	    	entityFirst->goTop();
    	      break;

    	    case 3:
    	    	entityFirst->goDown();
    	      break;

    	    default:

    	      break;
    	}

    }

    if(firstType == Entity::EntityType::player && (secondType == Entity::EntityType::stone || secondType == Entity::EntityType::box)) {
    	if(entityFirst->getState() == Entity::EntityState::goDown) {
    		float newY = entitySecond->getY() - 50.0f - 0.5f;

    		entityFirst->setPosition(entityFirst->getX(), newY);
    		entityFirst->stopDown();

    	} else if(entityFirst->getState() == Entity::EntityState::goTop) {
    		float newY = entitySecond->getY() + entityFirst->getSpriteDate().dimensions.y + 0.5f;

    		entityFirst->setPosition(entityFirst->getX(), newY);

    		entityFirst->stopTop();

    	} else if(entityFirst->getState() == Entity::EntityState::goLeft) {
    		float newX = entitySecond->getX() + 50 + 0.5f;

    		entityFirst->setPosition(newX, entityFirst->getY());

    		entityFirst->stopLeft();

    	} else if(entityFirst->getState() == Entity::EntityState::goRight) {
    		float newX = entitySecond->getX() - entityFirst->getSpriteDate().dimensions.x - 0.5f;

    		entityFirst->setPosition(newX, entityFirst->getY());

    		entityFirst->stopRight();
    	}

    	static_cast<Player*>(entityFirst)->lockKey = false;
    }

    if(firstType == Entity::EntityType::player && secondType == Entity::EntityType::enemy) {
    	Player *player = static_cast<Player*> (entityFirst);

    	if(!player->isImmortal()) {
    		player->looseLife();
    		entitySecond->remove();
    	}
    }

    if(firstType == Entity::EntityType::player && secondType == Entity::EntityType::explosion) {
    	Player *player = static_cast<Player*> (entityFirst);

    	if(!player->isImmortal())
    		player->looseLife();
    }

    if(firstType == Entity::EntityType::enemy && secondType == Entity::EntityType::explosion) {
      	static_cast<Explosion*> (entitySecond)->getPlayerPtr()->addScores( entityFirst->getScoresWhenKilled() );

      	entityFirst->remove();
    }

    if(firstType == Entity::EntityType::explosion && secondType == Entity::EntityType::box) {
    	entityFirst->remove();
    }

    if(firstType == Entity::EntityType::explosion && secondType == Entity::EntityType::stone) {
    	Player *player = static_cast<Explosion*>(entityFirst)->getPlayerPtr();

    	player->addScores( entitySecond->getScoresWhenKilled() );
    	entitySecond->remove();
    	entityFirst->remove();
    }

    #undef SWAP_IF
}

void Game::checkEntityEntityCollisions(float dt) { // sprawdzenie ka¿dej pary (ka¿dej jednokrotnie) - O(n^2)
    std::vector<Entity*>::iterator itFirst, itSecond;
    Entity *entityFirst, *entitySecond;
    Entity::EntityType fistType, secondType;

    for(itFirst = world->entities.begin(); itFirst != world->entities.end(); ++itFirst) {
    	entityFirst = *itFirst;
    	fistType = entityFirst->getType();

    	//if(fistType != Entity::EntityType::stone) {
    		if(entityFirst->isAlive()) {
    			itSecond = itFirst;
    			++itSecond;

    			for ( ; itSecond != world->entities.end(); ++itSecond) {
    				entitySecond = *itSecond;
    				secondType = entitySecond->getType();

    				if(entitySecond->isAlive())
    					checkCollisionOfOnePair(entityFirst, fistType, entitySecond, secondType, dt);
    			}
        	//}
        }
    }
}
