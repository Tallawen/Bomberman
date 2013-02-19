#include "Menu.h"

#include "Constants.h"

#include "Renderer/Window.h"
#include "Renderer/SubWindow.h"
#include "Renderer/Sprite.h"

/***********************************************************************************
 Game :: methods
 *********************/
Menu::Menu() : maxOptions(3) {
	background = Sprite::instance()->getSprite("Menu_Background");

	text[0] = Sprite::instance()->getSprite("Menu_TextStart");
	text[1] = Sprite::instance()->getSprite("Menu_TextStartActive");
	text[2] = Sprite::instance()->getSprite("Menu_TextAbout");
	text[3] = Sprite::instance()->getSprite("Menu_TextAboutActive");
	text[4] = Sprite::instance()->getSprite("Menu_TextExit");
	text[5] = Sprite::instance()->getSprite("Menu_TextExitActive");

	background.SetCenter(0, 0);
	background.SetPosition(0, 0);

	text[0].SetPosition(73, 266);
	text[1].SetPosition(73, 266);
	text[2].SetPosition(73, 298);
	text[3].SetPosition(73, 298);
	text[4].SetPosition(73, 337);
	text[5].SetPosition(73, 337);
}

int Menu::main(int id) {
	Window::instance()->init(Constants::Menu::SCREEN_WIDTH,
			                 Constants::Menu::SCREEN_HEIGHT,
			                 Constants::Menu::SCREEN_TITLE,
                             sf::Style::None);

	bool done = false;
	sf::Event event;

	while(!done) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Down)
				if(id < maxOptions-1) id++;

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Up)
				if(id > 0) id--;

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return) {
				if(id == (int)OptionsType::About)
					about();
				else
					done = true;
			}

			Window::instance()->process(event);
		}

		Window::instance()->getRW()->Clear(sf::Color(255,255,255, 0));
		Window::instance()->getRW()->Draw(background);

		for(int i=0; i<maxOptions; ++i) {
			if(id != i)
				Window::instance()->getRW()->Draw(text[i*2]);
			else
				Window::instance()->getRW()->Draw(text[i*2+1]);
		}

		Window::instance()->getRW()->Display();
	}

	switch(id) {
	    case (int)OptionsType::StartGame:
	    	LOG("Start");
	       return 1;
	      break;

	    case (int)OptionsType::Exit:
	    	Window::instance()->close();
	      break;
	}

   return 0;
}

void Menu::about() {
	SubWindow sb;

	sb.init(sf::Vector2i(446, 446), sf::Vector2i(62, 62));
	sb.add(Sprite::instance()->getSprite("About_Info"), sf::Vector2i(0, 446));

	sb.show();
}
