#include "StdAfx.h"

#include "Constants.h"

#include "Renderer/Window.h"
#include "Renderer/Sprite.h"
#include "Renderer/SoundManager.h"

#include "World/World.h"

#include "Menu.h"
#include "Game.h"

int main() {
	/* Load Texture */
	Sprite::instance()->insertTexture("Data/gfx/menu/elements/Menu_Background.png");
	Sprite::instance()->insertTexture("Data/gfx/menu/choose/Menu_TextStart.png");
	Sprite::instance()->insertTexture("Data/gfx/menu/choose/Menu_TextOptions.png");
	Sprite::instance()->insertTexture("Data/gfx/menu/choose/Menu_TextAbout.png");
	Sprite::instance()->insertTexture("Data/gfx/menu/choose/Menu_TextExit.png");

	Sprite::instance()->insertTexture("Data/gfx/menu/text/About_Info.png");

	Sprite::instance()->insertTexture("Data/gfx/elements/Block.png");
	Sprite::instance()->insertTexture("Data/gfx/elements/Game_Background.png");
	Sprite::instance()->insertTexture("Data/gfx/elements/Game_Background_Spots.png");
	Sprite::instance()->insertTexture("Data/gfx/elements/Game_Blocks.png");

	Sprite::instance()->insertTexture("Data/gfx/characters/Enemy1_GoDown.png",  true);
    Sprite::instance()->insertTexture("Data/gfx/characters/Enemy1_GoLeft.png",  true);
	Sprite::instance()->insertTexture("Data/gfx/characters/Enemy1_GoRight.png", true);
	Sprite::instance()->insertTexture("Data/gfx/characters/Enemy1_GoTop.png",   true);

	Sprite::instance()->insertTexture("Data/gfx/elements/Bomb.png", true);

	Sprite::instance()->insertTexture("Data/gfx/explosions/explosion3.png", true);

	Sprite::instance()->insertTexture("Data/gfx/characters/Player_White.png",   true);
	Sprite::instance()->insertTexture("Data/gfx/characters/PlayerGoRight2.png", true);
	Sprite::instance()->insertTexture("Data/gfx/characters/PlayerGoLeft.png",   true);
	Sprite::instance()->insertTexture("Data/gfx/characters/PlayerGoTop.png",    true);

	Sprite::instance()->insertTexture("Data/gfx/elements/test.png");
	Sprite::instance()->insertTexture("Data/gfx/elements/test2.png");
	Sprite::instance()->insertTexture("Data/gfx/elements/test3.png");

	/* Load Sprite */
	Sprite::instance()->insertSprite("Menu_Background",        "Menu_Background",  570, 570, 0,  0);
	Sprite::instance()->insertSprite("Menu_TextStart",         "Menu_TextStart",   158,  35, 0,  0);
	Sprite::instance()->insertSprite("Menu_TextStartActive",   "Menu_TextStart",   158,  35, 0, 35);
	Sprite::instance()->insertSprite("Menu_TextOptions",       "Menu_TextOptions", 118,  35, 0,  0);
	Sprite::instance()->insertSprite("Menu_TextOptionsActive", "Menu_TextOptions", 118,  35, 0, 35);
	Sprite::instance()->insertSprite("Menu_TextAbout",         "Menu_TextAbout",    91,  28, 0,  0);
	Sprite::instance()->insertSprite("Menu_TextAboutActive",   "Menu_TextAbout",    91,  28, 0, 28);
	Sprite::instance()->insertSprite("Menu_TextExit",          "Menu_TextExit",     57,  28, 0,  0);
	Sprite::instance()->insertSprite("Menu_TextExitActive",    "Menu_TextExit",     57,  28, 0, 28);

	Sprite::instance()->insertSprite("About_Info", "About_Info", 446, 446, 0, 0);

	Sprite::instance()->insertSprite("FloorDark",   "Game_Background", 50, 50,  0, 0);
	Sprite::instance()->insertSprite("FloorBright", "Game_Background", 50, 50,  50, 0);
	Sprite::instance()->insertSprite("FloorShadow", "Game_Background", 50, 50, 100, 0);

	Sprite::instance()->insertSprite("FloorStop", "Game_Background_Spots", 3840, 2160, 0, 0);

	Sprite::instance()->insertSprite("newBracket", "Game_Blocks", 50, 70, 50, 0);
	Sprite::instance()->insertSprite("newStone",   "Game_Blocks", 50, 70, 0, 0);

	Sprite::instance()->insertSprite("Background", "Block", 51, 40,   0, 21);
	Sprite::instance()->insertSprite("Floor",      "Block", 51, 40,  51, 21);
	Sprite::instance()->insertSprite("Stone",      "Block", 51, 60, 102,  1);
	Sprite::instance()->insertSprite("Bracket",    "Block", 51, 60, 153,  1);
	Sprite::instance()->insertSprite("RampTop",    "Block", 51, 41, 204, 20);
	Sprite::instance()->insertSprite("RampDown",   "Block", 51, 61, 255,  0);
	Sprite::instance()->insertSprite("RampLeft",   "Block", 51, 59, 306,  2);
	Sprite::instance()->insertSprite("RampRight",  "Block", 51, 59, 357,  2);
	Sprite::instance()->insertSprite("DoorClose",  "Block", 51, 60, 408,  1);
	Sprite::instance()->insertSprite("DoorOpen",   "Block", 51, 34, 459, 27);
	Sprite::instance()->insertSprite("Shadow",     "Block", 51, 40, 530, 21);

	Sprite::instance()->insertSprite("UI_HealtBar",     "test", 1, 16, 0, 0);
	Sprite::instance()->insertSprite("UI_HealtBarLeft",     "test2", 2, 16, 0, 0);
	Sprite::instance()->insertSprite("UI_HealtBarRight",     "test3", 2, 16, 0, 0);

	Sprite::instance()->insertSprite("Bomb", "Bomb", 23, 25, 0, 0);

	Sprite::instance()->insertSprite("Explosion", "explosion3", 50, 50, 0, 0, true, 60);

	Sprite::instance()->insertSprite("Player_White_Down",  "Player_White", 27, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Right", "PlayerGoRight2", 33, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Left",  "PlayerGoLeft", 32, 42, 0, 0, true, 15);
	Sprite::instance()->insertSprite("Player_White_Top",   "PlayerGoTop", 27, 41, 0, 0, true, 15);

	Sprite::instance()->insertSprite("Enemi_down",  "Enemy1_GoDown", 33, 32, 0, 0,  true, 3);
	Sprite::instance()->insertSprite("Enemi_right", "Enemy1_GoRight", 33, 32, 0, 0, true, 3);
	Sprite::instance()->insertSprite("Enemi_left",  "Enemy1_GoLeft", 33, 32, 0, 0,  true, 3);
	Sprite::instance()->insertSprite("Enemi_top",   "Enemy1_GoTop", 33, 32, 0, 0,   true, 3);

	/* Load sounds */
	SoundManager::instance().registerSound("Data/audio/Bomb_Explode.ogg", "bomb.explode");

	Menu menu;
	Game *game;

	bool done = false;
	while(!done) {
		int id = menu.main(0);

		uint sceen_width = (Window::instance()->desktopWidth - 100) / 50;
		uint sceen_height = (Window::instance()->desktopHeight - 100) / 50;



		if(id == 1) {
			std::cerr << sceen_width << ", " <<sceen_height << std::endl;

			Window::instance()->init(sceen_width *50,
					sceen_height*50,
					                 Constants::Video::SCREEN_TITLE,
					                 sf::Style::None);

			game = new Game;
			game->startGame(0);
		}

		if(id == 0)
			done = true;
	}

	while(Window::instance()->isOpen()) {

		Window::instance()->getRW()->Clear();

		Window::instance()->getRW()->Display();
	}
}
