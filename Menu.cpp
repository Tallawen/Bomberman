#include "Menu.h"

#include "Constants.h"

#include "Renderer/Window.h"
#include "Renderer/SubWindow.h"
#include "Renderer/SpriteManager.h"
#include "Renderer/SoundManager.h"

/***********************************************************************************
 Menu :: methods
 *********************/
Menu::Menu() : maxOptions(2) {
	background = SpriteManager::instance()->getSprite("main_menu.background");

	text[0] = SpriteManager::instance()->getSprite("main_menu.play");
	text[1] = SpriteManager::instance()->getSprite("main_menu.play_active");
	text[2] = SpriteManager::instance()->getSprite("main_menu.about");
	text[3] = SpriteManager::instance()->getSprite("main_menu.about_active");

	background.SetCenter(0, 0);
	background.SetPosition(0, 0);

	text[0].SetPosition(29, 316);
	text[1].SetPosition(29, 316);
	text[2].SetPosition(76, 327);
	text[3].SetPosition(76, 327);
}

Game::GameType Menu::show(OptionsType type) {
	Window::instance()->init(Constants::Menu::SCREEN_WIDTH,
			                 Constants::Menu::SCREEN_HEIGHT,
			                 Constants::Menu::SCREEN_TITLE,
                             sf::Style::None);

	bool done = false;
	int id = int(type);

	Game::GameType playType = Game::GameType::none;

	sf::Event event;

	sf::Music* menuTheme  = SoundManager::instance().getMusic("menu.aurora");
	menuTheme->SetLoop(true);
	menuTheme->SetVolume(50.0f);
	menuTheme->Play();

	while(!done) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
				type = OptionsType::exit;
				playType = Game::GameType::none;
				Window::instance()->close();
				done = true;

			} else if(event.Type == sf::Event::KeyPressed && (event.Key.Code == sf::Key::Down || event.Key.Code == sf::Key::Right)) {
				if(id < maxOptions-1) id++;

			} else if(event.Type == sf::Event::KeyPressed && (event.Key.Code == sf::Key::Up || event.Key.Code == sf::Key::Left)) {
				if(id > 0) id--;

			} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return) {
				type = OptionsType(id);

				switch(type) {
				    case OptionsType::about:
				    	about();
				      break;

				    case OptionsType::play:
				    	playType = play();
				      break;

				    default:

				      break;
				}

				if(playType != Game::GameType::none) done = true;
			}

			Window::instance()->process(event);
		}

		Window::instance()->getRW()->Clear();
		Window::instance()->getRW()->Draw(background);

		for(int i=0; i<maxOptions; ++i) {
			if(id != i)
				Window::instance()->getRW()->Draw(text[i*2]);
			else
				Window::instance()->getRW()->Draw(text[i*2+1]);
		}

		Window::instance()->getRW()->Display();
	}

	Window::instance()->close();

	menuTheme->Stop();

  return playType;
}

void Menu::about() {
	//SubWindow sW;

	//sW.init(sf::Vector2f(100, 100), sf::Vector2f(62, 62));
	//sW.add(Sprite::instance()->getSprite("About_Info"), sf::Vector2i(0, 50));

	//sW.show();
}

Game::GameType Menu::play() {
	sf::Sprite player = SpriteManager::instance()->getSprite("player.white_down");
	sf::Sprite bat = SpriteManager::instance()->getSprite("enemy.bat_down");

	SpriteData sdPlayer = SpriteManager::instance()->getSpriteData("player.white_down");
	SpriteData sdBat = SpriteManager::instance()->getSpriteData("enemy.bat_down");

	player.SetSubRect(sf::IntRect(0, 0, sdPlayer.dimensions.x, sdPlayer.dimensions.y));
	bat.SetSubRect(sf::IntRect(0, 0, sdBat.dimensions.x, sdBat.dimensions.y));

	SubWindow sW;

	int sWXPosition = (Constants::Menu::SCREEN_WIDTH - 307) / 2;
	int sWYPosition = (Constants::Menu::SCREEN_HEIGHT - 307) / 2;

	sW.init(sf::Vector2f(307, 307), sf::Vector2f(sWXPosition, sWYPosition));

	sW.add(SpriteManager::instance()->getSprite("button.1"), sf::Vector2i(45,  92));
	sW.add(SpriteManager::instance()->getSprite("button.2"), sf::Vector2i(45, 172));
	sW.add(SpriteManager::instance()->getSprite("button.3"), sf::Vector2i(45, 252));

	sW.add(player, sf::Vector2i(110, 92));
	sW.add(player, sf::Vector2i(110, 172));
	sW.add(player, sf::Vector2i(140, 172));
	sW.add(player, sf::Vector2i(110, 252));
	sW.add(player, sf::Vector2i(230, 252));

	sW.add(bat, sf::Vector2i(230, 92));
	sW.add(bat, sf::Vector2i(230, 172));

	sW.add(SpriteManager::instance()->getSprite("text.vs"), sf::Vector2i(188, 79));
	sW.add(SpriteManager::instance()->getSprite("text.vs"), sf::Vector2i(188, 159));
	sW.add(SpriteManager::instance()->getSprite("text.vs"), sf::Vector2i(188, 239));

	sW.setTransitionEffect(1);

	sf::Key::Code value = sW.show([](sf::Event &event, sf::Key::Code &result, bool &done)->void {
		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Num1) {
			result = sf::Key::Num1;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Num2) {
			result = sf::Key::Num2;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Num3) {
			result = sf::Key::Num3;
			done = true;

		} else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape) {
			result = sf::Key::Escape;
			done = true;
		}
	});

	switch(value) {
	    case sf::Key::Num1:
	    	return Game::GameType::oneVsBot;
	      break;

	    case sf::Key::Num2:
	    	return Game::GameType::twoVsBot;
	      break;

	    case sf::Key::Num3:
	    	return Game::GameType::oneVsOne;
	      break;

	    default:
	      break;
	}

  return Game::GameType::none;
}
