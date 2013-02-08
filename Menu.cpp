#include "Menu.h"

/***********************************************************************************
 Game :: methods
 *********************/
Menu::Menu() : maxOptions(4) {
	background = Sprite::instance()->getSprite("Menu_Background");

	text[0] = Sprite::instance()->getSprite("Menu_TextStart");
	text[1] = Sprite::instance()->getSprite("Menu_TextStartActive");
	text[2] = Sprite::instance()->getSprite("Menu_TextOptions");
	text[3] = Sprite::instance()->getSprite("Menu_TextOptionsActive");
	text[4] = Sprite::instance()->getSprite("Menu_TextAbout");
	text[5] = Sprite::instance()->getSprite("Menu_TextAboutActive");
	text[6] = Sprite::instance()->getSprite("Menu_TextExit");
	text[7] = Sprite::instance()->getSprite("Menu_TextExitActive");

	background.SetCenter(0, 0);
	background.SetPosition(0, 0);

	text[0].SetPosition(73, 266);
	text[1].SetPosition(73, 266);
	text[2].SetPosition(73, 305);
	text[3].SetPosition(73, 305);
	text[4].SetPosition(73, 337);
	text[5].SetPosition(73, 337);
	text[6].SetPosition(73, 376);
	text[7].SetPosition(73, 376);
}

int Menu::main(int id) {
	Window::instance()->init(570, 570, "Bomberman", sf::Style::None);

	bool done = false;
	sf::Event event;

	while(!done) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Down)
				if(id < maxOptions-1) id++;

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Up)
				if(id > 0) id--;

			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return) {
				if(id == (int) OptionsType::Options)
					createTest();
				else
					done = true;
			}
			Window::instance()->process(event);
		}

		Window::instance()->getRW()->Clear();
		Window::instance()->getRW()->Draw(background);

		//LOG("test");
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

	    case (int)OptionsType::Options:
	    		Window::instance()->close();

          break;

	    case (int)OptionsType::About:
	    	Window::instance()->close();
	      break;

	    case (int)OptionsType::Exit:
	    	Window::instance()->close();
	      break;
	}

   return 0;
}

void Menu::createTest() {
	SubWindow sb;
	Text text("Data/comfortaa.ttf");

	sb.init(sf::Vector2i(446, 446), sf::Vector2i(62, 62));

	sb.add(Sprite::instance()->getSprite("About_Info"),   sf::Vector2i(0, 446));

	/*sb.add(Sprite::instance()->getSprite("About_Description"),   sf::Vector2i(47, 50));
	sb.add(Sprite::instance()->getSprite("About_GoodLuck"),   sf::Vector2i(350, 100));

	text.setText("Szymon Kuchnia");
	text.setColor(sf::Color::White);
	sb.add(text.getText(),  sf::Vector2i(200, 250));

	text.setText("lead programmer and graphics");
	text.setColor(sf::Color::Yellow);
	sb.add(text.getText(),  sf::Vector2i(200, 280));

	text.setText("Pawe³ Maniecki");
	text.setColor(sf::Color::White);
	sb.add(text.getText(),  sf::Vector2i(200, 330));

	text.setText("programmer");
	text.setColor(sf::Color::Yellow);
	sb.add(text.getText(),  sf::Vector2i(200, 360));

	text.setText("Jakub Nowak");
	text.setColor(sf::Color::White);
	sb.add(text.getText(),  sf::Vector2i(200, 410));

	text.setText("programmer");
	text.setColor(sf::Color::Yellow);
	sb.add(text.getText(),  sf::Vector2i(200, 440));
*/
	sb.show();
}
