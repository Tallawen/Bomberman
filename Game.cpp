#include "Game.h"

#include "constants.h"
#include "UI/UI.h"

#include "Renderer/Window.h"
#include "Renderer/SubWindow.h"
#include "Renderer/SoundManager.h"

#include "World/Entity/Explosion.h"
#include "World/Entity/Smoke.h"
#include "World/Entity/Bomb.h"
#include "World/Entity/Collectible.h"
#include "World/Entity/Collectibles/BombBonus.h"
#include "World/Entity/Collectibles/HealthBonus.h"

#include "UI/HealthBar.h"
#include "UI/Avatar.h"
#include "UI/BombBar.h"
#include "UI/Score.h"

/***********************************************************************************
 Game :: methods
 *********************/
Game::Game() : input(Window::instance()->getRW()->GetInput()) {
	world = nullptr;
	players.clear();

	playingLevel = true;
	gameEnded = false;

	level = 0;

	movePtr[0] = &Entity::goLeft;
	movePtr[1] = &Entity::goRight;
	movePtr[2] = &Entity::goTop;
	movePtr[3] = &Entity::goDown;

	throwHp = false;

	// TODO: put it in a better place, preferably somewhere else entirely
	endWindow_KeyPress = // lambda
		[](sf::Event &event, sf::Key::Code &result, bool &done)->void {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::R) { // Restart
				result = sf::Key::R;
				done = true;
			} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) { // Quit
				result = sf::Key::Q;
				done = true;
			}
		};
}

Game::~Game() {
	if(world != nullptr) {
		delete world;

		world = nullptr;
	}
}

void Game::init(GameType _type) {
	type = _type;

	if(world == nullptr)
		world = new World;

	Window::instance()->showHitbox = false;

	if(type == GameType::oneVsBot)
		players.push_back( new Player(sf::Vector2f(0, 0), &world->entitiesToCreate));

	else if(type == GameType::oneVsOne || type == GameType::twoVsBot) {
		players.push_back( new Player(sf::Vector2f(0, 0), &world->entitiesToCreate));
		players.push_back( new Player(sf::Vector2f(1, 1), &world->entitiesToCreate));
	}

	if(type == GameType::oneVsBot || type == GameType::twoVsBot)
		throwHp = true;

	/** Music **/
	music[0] = SoundManager::instance().getMusic("game.ff");
	music[0]->Stop();
	music[0]->SetLoop(false);
	music[0]->SetVolume(20.0f);

	music[1] = SoundManager::instance().getMusic("game.ffs");
	music[1]->Stop();
	music[1]->SetLoop(false);
	music[1]->SetVolume(30.0f);

	music[2] = SoundManager::instance().getMusic("game.ffd");
	music[2]->Stop();
	music[2]->SetLoop(false);
	music[2]->SetVolume(30.0f);

	musicId = sf::Randomizer::Random(0, 2);
	music[musicId]->Play();

	game();

	music[musicId]->Stop();
}

void Game::game() {
	gameEnded = false;

	while(!gameEnded) {
		playingLevel = true;

		++level;

		sf::Clock clock;
		sf::Clock bonusTime;

		sf::Event event;

		UI ui;
		addUI(ui);

		sf::Shape border = this->border();

		if(type == GameType::oneVsBot)
			world->loadWorld(this, 1, level);
		else
			world->loadWorld(this, 2, level);

		while(playingLevel) {
			changeMusic();

			while(Window::instance()->getRW()->GetEvent(event)) {
				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
					float old_volume = music[musicId]->GetVolume();
					music[musicId]->SetVolume(old_volume*0.1);
//					music[musicId]->Pause();

					bool done = false;

					while(!done) {
						sf::Key::Code code = windowPauseMenu();

						if(code == sf::Key::Q) {
							playingLevel = false;
							done = gameEnded = true;
						}

						else if(code == sf::Key::R){
							playingLevel = false;
							done = gameEnded = true;
						}

						else if(code == sf::Key::H) {
							Window::instance()->getRW()->Clear();
							world->draw(0);
							ui.show(0);

							Window::instance()->getRW()->Draw(border);
							Window::instance()->getRW()->Display();
							Window::instance()->getRW()->Display(); // 2nd is required, due to witchcraft

							windowHelp();

						} else if(code == sf::Key::Escape)
							done = true;
					}

//					music[musicId]->Play();
					music[musicId]->SetVolume(old_volume);
					clock.Reset();
				}

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Z)
					Window::instance()->showHitbox = !Window::instance()->showHitbox;

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::O)
					world->manhole->open();

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::C)
					world->manhole->close();

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::B) {
					players.at(1)->putBomb();

					static_cast<Bomb*> (world->entitiesToCreate.back())->move(2.0f, 0);

				}

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::R) {
					raid();


				}



				playerKeyboardControl(event);
				//playerJoyControl(event);

				Window::instance()->process(event);
			}

			Window::instance()->getRW()->Clear();

			float dt = clock.GetElapsedTime();
			clock.Reset();

			if(bonusTime.GetElapsedTime() > 5.0f) {
				throwCollectible(
						toPos( sf::Randomizer::Random(0, world->emptyField.size()-1)), true
						);
				bonusTime.Reset();

				LOG("restart");
			}

			world->draw(dt);
			ui.show(dt);

			Window::instance()->getRW()->Draw(border);

			playerControlRealtime();
			checkEntityEntityCollisions(dt);

			Window::instance()->getRW()->Display();

			world->removeAndAddEntities();

			if(type == GameType::oneVsBot && !players.at(0)->isAlive()) {
				// TODO: GAME OVER screen here
				playingLevel = false;
				gameEnded = windowGameOver_1vBot();

			} else if(type == GameType::twoVsBot || type == GameType::oneVsOne) {

				if(!players.at(0)->isAlive() || !players.at(1)->isAlive()) {
					// TODO: GAME OVER screen here
					playingLevel = false;
					if(type == GameType::oneVsOne) {
						gameEnded = windowGameOver_1v1(!players.at(0)->isAlive() ? 1 : 0);
					}
					else {
						gameEnded = windowGameOver_2vBot(!players.at(0)->isAlive() ? 1 : 0);
					}
				}

			}
		}
	}
}

sf::Vector2f Game::toPos(int id) {
		return sf::Vector2f(50 * (world->emptyField.at(id) % world->mapDimensions.x), 50 * (world->emptyField.at(id) / world->mapDimensions.x) + 150);
	}

void Game::throwCollectible(sf::Vector2f position, bool ignore) {
	int i = sf::Randomizer::Random(0, 10);

	if(i == 0 || ignore) {
		int k = sf::Randomizer::Random(0, 1);

		if(k == 0) {
			sf::Vector2f offset;
			BombBonus::Amount amount;

			switch(sf::Randomizer::Random(0, 3)) {
			    case 0: offset = sf::Vector2f(12, -5);  amount = BombBonus::Amount::minusone;  break;
			    case 1: offset = sf::Vector2f(12, -5);  amount = BombBonus::Amount::one;       break;
			    case 2: offset = sf::Vector2f( 6, -5);  amount = BombBonus::Amount::many;      break;
			    case 3: offset = sf::Vector2f( 4, -5);  amount = BombBonus::Amount::max;       break;
			    default: break;
			}

			world->entitiesToCreate.push( new BombBonus(position + offset, &world->entitiesToCreate, amount));

		} else if(k == 1 && throwHp) {
			sf::Vector2f offset;
			HealthBonus::Amount amount;

			switch(sf::Randomizer::Random(0, 3)) {
			    case 0: offset = sf::Vector2f(12, -5);  amount = HealthBonus::Amount::minusone;  break;
			    case 1: offset = sf::Vector2f(12, -5);  amount = HealthBonus::Amount::one;       break;
			    case 2: offset = sf::Vector2f( 6, -5);  amount = HealthBonus::Amount::many;      break;
			    case 3: offset = sf::Vector2f( 4, -5);  amount = HealthBonus::Amount::max;       break;
			    default: break;
			}

			world->entitiesToCreate.push( new HealthBonus(position + offset, &world->entitiesToCreate, amount));
		}
	}
}

void inline Game::addUI(UI &ui) {
	/** Gracz 1 **/
	ui.add(new Avatar(                  sf::Vector2f(Constants::UI::Avatar::X,    Constants::UI::Avatar::Y)));
	ui.add(new HealthBar(players.at(0), sf::Vector2f(Constants::UI::HealthBar::X, Constants::UI::HealthBar::Y)));
	ui.add(new BombBar(  players.at(0), sf::Vector2f(Constants::UI::BombBar::X,   Constants::UI::BombBar::Y)));
	ui.add(new Scores(   players.at(0), sf::Vector2f(Constants::UI::Scores::X,    Constants::UI::Scores::Y + 10)));

	/** Gracz 2 **/
	//TODO: Set up constants for second UI
	if(type == GameType::oneVsOne || type == GameType::twoVsBot) {
		ui.add(new Avatar(                  sf::Vector2f(Window::instance()->getWidth() - 280 - Constants::UI::Avatar::X, Constants::UI::Avatar::Y), true));
		ui.add(new HealthBar(players.at(1), sf::Vector2f(Window::instance()->getWidth() - 210 - Constants::UI::Avatar::X, Constants::UI::HealthBar::Y)));
		ui.add(new BombBar(  players.at(1), sf::Vector2f(Window::instance()->getWidth() - 210 - Constants::UI::Avatar::X, Constants::UI::BombBar::Y)));
		ui.add(new Scores(   players.at(1), sf::Vector2f(Window::instance()->getWidth() - 210 - Constants::UI::Avatar::X, Constants::UI::Scores::Y + 10)));
	}
}

sf::Shape inline Game::border() {
	int size = Constants::Video::SCREEN_BORDER();

	int x = size / 2;
	int y = size / 2;

	int maxX = Window::instance()->getWidth() - size / 2;
	int maxY = Window::instance()->getHeight() - size / 2;

  return sf::Shape::Rectangle(x, y, maxX, maxY, sf::Color(255, 255, 255, 0), size, sf::Color::Black);
}

void inline Game::changeMusic() {
	if(music[musicId]->GetStatus() == sf::Music::Status::Stopped) {
		int id = musicId;

		while(id == musicId)
			musicId = sf::Randomizer::Random(0, 2);

		music[musicId]->Play();
	}
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
		}
	}
}

void inline Game::playerControl(int i, int j, Player* player, Entity::EntityState state) {
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

		if(input.GetJoystickAxis(i , sf::Joy::AxisPOV) == j) {
			if(!player->lockKey) {
				(player->*ptrFun)();
				player->lockKey = true;
			}
		} else if(player->getState() == state && player->lockKey) {
			(player->*ptrNegFun)();
			player->lockKey = false;
		}
	}
}

void Game::playerKeyboardControl(sf::Event &event) {
	if(players.size() > 0 && !players.at(0)->lockMovement) {

		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
			players.at(0)->goingToCenter();

	}

	if(players.size() > 1 && !players.at(1)->lockMovement) {

		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::LShift)
			players.at(1)->goingToCenter();

	}
}

void Game::playerJoyControl(sf::Event &event) {
	if(players.size() > 0 && !players.at(0)->lockMovement) {

		if(event.Type == sf::Event::JoyButtonPressed && event.JoyButton.JoystickId == 0 && event.JoyButton.Button == 0)
			players.at(0)->goingToCenter();

	}

	if(players.size() > 1 && !players.at(1)->lockMovement) {

		if(event.Type == sf::Event::JoyButtonPressed && event.JoyButton.JoystickId == 1 && event.JoyButton.Button == 0)
			players.at(1)->goingToCenter();

	}
}


void Game::playerControlRealtime() {
	if(players.size() > 0) {
		//NOTE: PS3 - Controller
//		playerControl(0, 180, players.at(0), Entity::EntityState::goDown);
//		playerControl(0, 0,   players.at(0), Entity::EntityState::goTop);
//		playerControl(0, 90,  players.at(0), Entity::EntityState::goRight);
//		playerControl(0, 270, players.at(0), Entity::EntityState::goLeft);
		//NOTE: Keyboard
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

void Game::raid() {
	int amount = sf::Randomizer::Random(2, 5);
	int id, x, y;

	while(amount--) {
		id = sf::Randomizer::Random(0, world->emptyField.size() - 1);
		y = world->floorData.dimensions.y * (world->emptyField.at(id) / world->mapDimensions.x) + 150 - 20;
		x = world->floorData.dimensions.x * (world->emptyField.at(id) % world->mapDimensions.x) + 12;

		Bomb *bomb = new Bomb(sf::Vector2f(x, y), players.at(1), &world->entitiesToCreate);
		bomb->move(sf::Randomizer::Random(1.5f, 2.0f), 0);

		world->entitiesToCreate.push(bomb);
	}
}

/***********************************************************************************
 Game :: methods :: collision
 *********************/

void Game::checkCollisionOfOnePair(
               Entity *entityFirst, Entity::EntityType firstType,
               Entity *entitySecond, Entity::EntityType secondType, float dt) {

		if(!entityFirst->getNextHitbox(dt).collidesWith(entitySecond->getNextHitbox(dt)))
			return;

		/** makro SWAP_IF pozwala zamieniæ znaczenie argumentów fst* z snd*    **
		 ** w ten sposób, ¿e sprawdzaj¹c kolizjê otrzymujemy wska¿niki zawsze  **
		 ** w dobrej kolejnoœci, tzn. tak, aby ka¿d¹ parê obs³ugiwaæ jeden raz **/

		#define SWAP_IF(type_a, type_b)  \
	            if(firstType == type_a && secondType == type_b) {  \
    	            std::swap(entityFirst, entitySecond);   \
                    std::swap(firstType, secondType);   \
	            }

		SWAP_IF(Entity::EntityType::stone, Entity::EntityType::player);
		SWAP_IF(Entity::EntityType::box, Entity::EntityType::player);
	    SWAP_IF(Entity::EntityType::enemy, Entity::EntityType::player);
	    SWAP_IF(Entity::EntityType::bomb, Entity::EntityType::player);
	    SWAP_IF(Entity::EntityType::collectible, Entity::EntityType::player);
		SWAP_IF(Entity::EntityType::explosion, Entity::EntityType::player);

		SWAP_IF(Entity::EntityType::stone, Entity::EntityType::enemy);
        SWAP_IF(Entity::EntityType::box, Entity::EntityType::enemy);
        SWAP_IF(Entity::EntityType::explosion, Entity::EntityType::enemy);

        SWAP_IF(Entity::EntityType::stone, Entity::EntityType::explosion);
        SWAP_IF(Entity::EntityType::box, Entity::EntityType::explosion);

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
        	(entityFirst->*movePtr[ sf::Randomizer::Random(0, 3) ])();
        }

        if(firstType == Entity::EntityType::player && secondType == Entity::EntityType::bomb) {
        	Player *player = static_cast<Player*> (entityFirst);
        	Bomb *bomb = static_cast<Bomb*> (entitySecond);

        	if(bomb->getPlayerPtr() != player) {
        		if(entityFirst->getState() == Entity::EntityState::goDown)
        			entityFirst->stopDown();

        		else if(entityFirst->getState() == Entity::EntityState::goTop)
        			entityFirst->stopTop();

        		else if(entityFirst->getState() == Entity::EntityState::goLeft)
        			entityFirst->stopLeft();

        		else if(entityFirst->getState() == Entity::EntityState::goRight)
        			entityFirst->stopRight();

        		player->lockKey = false;
        	}
        }

        if(firstType == Entity::EntityType::player && secondType == Entity::EntityType::collectible) {
        	Player *player = static_cast<Player*> (entityFirst);
        	Collectible *collectible = static_cast<Collectible*> (entitySecond);

        	collectible->collect(player);
        	collectible->remove();
        }

        if(firstType == Entity::EntityType::player && (secondType == Entity::EntityType::stone || secondType == Entity::EntityType::box)) {
        	if(entityFirst->getState() == Entity::EntityState::goDown)
        		entityFirst->stopDown();

        	else if(entityFirst->getState() == Entity::EntityState::goTop)
        		entityFirst->stopTop();

        	else if(entityFirst->getState() == Entity::EntityState::goLeft)
        		entityFirst->stopLeft();

        	else if(entityFirst->getState() == Entity::EntityState::goRight)
        		entityFirst->stopRight();

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

        if(firstType == Entity::EntityType::explosion && secondType == Entity::EntityType::box)
        	entityFirst->remove();

        if(firstType == Entity::EntityType::explosion && secondType == Entity::EntityType::stone) {
        	Player *player = static_cast<Explosion*>(entityFirst)->getPlayerPtr();

        	world->entitiesToCreate.push(new Smoke(entityFirst->getPosition() + sf::Vector2f(-7, 0), &world->entitiesToCreate));
        	throwCollectible(entitySecond->getPosition());

        	int x = entitySecond->getPosition().x / 50;
        	int y = (entitySecond->getPosition().y - 150) / 50;

        	world->emptyField.push_back(y * world->mapDimensions.x + x);

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

    	if(entityFirst->isAlive()) {
    		itSecond = itFirst;
    		++itSecond;

    		while(itSecond != world->entities.end()) {
    			entitySecond = *itSecond;
    			secondType = entitySecond->getType();

    			if(entitySecond->isAlive())
    				checkCollisionOfOnePair(entityFirst, fistType, entitySecond, secondType, dt);

    			++itSecond;
    		}
    	}
    }
}


/***********************************************************************************
 Game :: methods :: sub-window
 *********************/
sf::Key::Code Game::windowPauseMenu() {
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

	sW.setTransitionEffect(0.5f);

	sf::Key::Code result = sW.show([](sf::Event &event, sf::Key::Code &result, bool &done)->void {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
			result = sf::Key::Escape;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::R) {
			result = sf::Key::R;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::H) {
			result = sf::Key::H;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Q) {
			result = sf::Key::Q;
			done = true;
		}
	});

  return result;
}

void Game::windowHelp() {
	SubWindow sW;

	sW.init(490, 390, (Window::instance()->getWidth() - 490) / 2, (Window::instance()->getHeight() - 390) / 2);

	sW.setAplha(255);

	sW.add(SpriteManager::instance()->getSprite("button.top"),   sf::Vector2i(105, 210));
	sW.add(SpriteManager::instance()->getSprite("button.left"),  sf::Vector2i( 57, 257));
	sW.add(SpriteManager::instance()->getSprite("button.down"),  sf::Vector2i(105, 257));
	sW.add(SpriteManager::instance()->getSprite("button.right"), sf::Vector2i(151, 257));
	sW.add(SpriteManager::instance()->getSprite("button.space"), sf::Vector2i( 48, 349));

	sW.add(SpriteManager::instance()->getSprite("ps3_button.move"), sf::Vector2i(326, 257));
	sW.add(SpriteManager::instance()->getSprite("ps3_button.x"),    sf::Vector2i(351, 351));

	sW.add(SpriteManager::instance()->getSprite("text.you_can_use"), sf::Vector2i(118,  52));
	sW.add(SpriteManager::instance()->getSprite("text.keyboard"),    sf::Vector2i( 89, 130));
	sW.add(SpriteManager::instance()->getSprite("text.ps3_pad"),     sf::Vector2i(342, 127));
	sW.add(SpriteManager::instance()->getSprite("text.move"),        sf::Vector2i(244, 220));
	sW.add(SpriteManager::instance()->getSprite("text.put_bomb"),    sf::Vector2i(231, 338));

	sW.setTransitionEffect(0.5f);

	sW.show([](sf::Event &event, sf::Key::Code &result, bool &done)->void {
		if(event.Type == sf::Event::KeyPressed) {
			result = sf::Key::Escape;
			done = true;
		}
	});
}

bool Game::windowGameOver_1v1(int winner) {
	SubWindow sW;
	int width = 400;
	int height = 400;
	sW.init(width, height,
		(Window::instance()->getWidth() - width) / 2,
		(Window::instance()->getHeight() - height) / 2
	);

	sW.add(SpriteManager::instance()->getSprite("endscreen.1v1"),
			sf::Vector2i(0, height));

	// Who is the winner - show avatar
	std::string winnerAvatar = winner == 0 ? "ui.white_avatar" : "ui.black_avatar";
	sW.add(SpriteManager::instance()->getSprite(winnerAvatar), sf::Vector2i(255, 316));

	// Scores

	sW.setTransitionEffect(0.5f);
	sf::Key::Code result = sW.show(endWindow_KeyPress); // Catch key presses
	return (result == sf::Key::Q); // Exits to main menu
}

bool Game::windowGameOver_1vBot() {
	SubWindow sW;
	int width = 400;
	int height = 400;
	sW.init(width, height,
		(Window::instance()->getWidth() - width) / 2,
		(Window::instance()->getHeight() - height) / 2
	);

	// TODO: Add window graphic
	// sW.add(SpriteManager::instance()->getSprite("endscreen.1v1"), sf::Vector2i(0, height));

	sW.setTransitionEffect(0.5f);
	sf::Key::Code result = sW.show(endWindow_KeyPress);
	return (result == sf::Key::Q); // Exits to main menu
}

bool Game::windowGameOver_2vBot(int survivor) {
	SubWindow sW;
	int width = 400;
	int height = 400;
	sW.init(width, height,
		(Window::instance()->getWidth() - width) / 2,
		(Window::instance()->getHeight() - height) / 2
	);

	// TODO: Add window graphic
	// sW.add(SpriteManager::instance()->getSprite("endscreen.1v1"), sf::Vector2i(0, height));

	sW.setTransitionEffect(0.5f);
	sf::Key::Code result = sW.show(endWindow_KeyPress);
	return (result == sf::Key::Q); // Exits to main menu
}
