#include "StdAfx.h"

#include "constants.h"

#include "Renderer/Window.h"
#include "Renderer/SpriteManager.h"
#include "Renderer/SoundManager.h"

#include "World/World.h"

#include "Menu.h"
#include "Game.h"

int main() {
	/* Load Texture */
	SpriteManager::instance()->insertTexture("Data/gfx/menu/elements/main_menu_background.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/choose/main_menu_play.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/choose/main_menu_about.png");

	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_background.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_background_spots.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_background_block.png");

	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_bomb.png", true);
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_bomb_black.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_bomb_red.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_explosion.png", true);
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_smoke.png", true);

	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_hp_minuone.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_hp_one.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_hp_three.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_hp_five.png");

	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_bomb_minuone.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_bomb_one.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_bomb_three.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/collectible_bomb_five.png");

	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_player_white_down.png",  true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_player_white_top.png",   true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_player_white_left.png",  true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_player_white_right.png", true);

	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_bat_left.png",  true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_bat_right.png", true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_bat_top.png",   true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_bat_down.png",  true);

	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_death_left.png",  true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_death_right.png", true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_death_top.png",   true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_death_down.png",  true);

	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_glimmer_left.png",  true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_glimmer_right.png", true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_glimmer_top.png",   true);
	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_glimmer_down.png",  true);

	SpriteManager::instance()->insertTexture("Data/gfx/characters/character_zombie_down.png",  true);

	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_wall.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_ledder.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_door_close.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/game_door_open.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/dative.png");

	SpriteManager::instance()->insertTexture("Data/gfx/elements/gui_health_bar.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/ui_white_avatar.png");
	SpriteManager::instance()->insertTexture("Data/gfx/elements/ui_black_avatar.png");

	SpriteManager::instance()->insertTexture("Data/gfx/menu/elements/button.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/elements/ps3_button.png");

	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/text_exit_to_main_menu.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/text_help.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/text_restart.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/text_resume.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/text_vs.png");

	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/keyboard.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/move.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/ps3_pad.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/put_bomb.png");
	SpriteManager::instance()->insertTexture("Data/gfx/menu/text/you_can_use.png");

	SpriteManager::instance()->insertTexture("Data/gfx/text/text_hp.png");
	SpriteManager::instance()->insertTexture("Data/gfx/text/text_score.png");

	SpriteManager::instance()->insertTexture("Data/gfx/text/text_win_white.png");
	SpriteManager::instance()->insertTexture("Data/gfx/text/text_win_black.png");


	/* Load Sprite */
	SpriteManager::instance()->insertSprite("main_menu.background", "main_menu_background", 456, 456, 0,  0);

	SpriteManager::instance()->insertSprite("main_menu.play_active",  "main_menu_play",  50, 20,  0,  0);
	SpriteManager::instance()->insertSprite("main_menu.play",         "main_menu_play",  50, 20, 50,  0);
	SpriteManager::instance()->insertSprite("main_menu.about_active", "main_menu_about", 67, 20,  0,  0);
	SpriteManager::instance()->insertSprite("main_menu.about",        "main_menu_about", 67, 20, 67,  0);

	SpriteManager::instance()->insertSprite("button.esc",   "button",  37, 28,   0, 9);
	SpriteManager::instance()->insertSprite("button.q",     "button",  37, 37,  37, 0);
	SpriteManager::instance()->insertSprite("button.r",     "button",  37, 37,  74, 0);
	SpriteManager::instance()->insertSprite("button.h",     "button",  37, 37, 111, 0);
	SpriteManager::instance()->insertSprite("button.1",     "button",  37, 37, 148, 0);
	SpriteManager::instance()->insertSprite("button.2",     "button",  37, 37, 185, 0);
	SpriteManager::instance()->insertSprite("button.3",     "button",  37, 37, 222, 0);
	SpriteManager::instance()->insertSprite("button.top",   "button",  37, 37, 259, 0);
	SpriteManager::instance()->insertSprite("button.left",  "button",  37, 37, 296, 0);
	SpriteManager::instance()->insertSprite("button.down",  "button",  37, 37, 333, 0);
	SpriteManager::instance()->insertSprite("button.right", "button",  37, 37, 370, 0);
	SpriteManager::instance()->insertSprite("button.space", "button", 152, 37, 406, 0);

	SpriteManager::instance()->insertSprite("ps3_button.move", "ps3_button", 84, 84,  0,  0);
	SpriteManager::instance()->insertSprite("ps3_button.x",    "ps3_button", 35, 35, 84, 49);

	SpriteManager::instance()->insertSprite("text.exit_to_main_menu", "text_exit_to_main_menu", 125, 13, 0, 0);
	SpriteManager::instance()->insertSprite("text.help",              "text_help",               33, 16, 0, 0);
	SpriteManager::instance()->insertSprite("text.restart",           "text_restart",            53, 13, 0, 0);
	SpriteManager::instance()->insertSprite("text.resume",            "text_resume",             56, 13, 0, 0);
	SpriteManager::instance()->insertSprite("text.vs",                "text_vs",                 17, 10, 0, 0);

	SpriteManager::instance()->insertSprite("text.keyboard",    "keyboard",     69, 16, 0, 0);
	SpriteManager::instance()->insertSprite("text.move",        "move",         39, 10, 0, 0);
	SpriteManager::instance()->insertSprite("text.ps3_pad",     "ps3_pad",      55, 13, 0, 0);
	SpriteManager::instance()->insertSprite("text.put_bomb",    "put_bomb",     69, 16, 0, 0);
	SpriteManager::instance()->insertSprite("text.you_can_use", "you_can_use", 256, 13, 0, 0);

	SpriteManager::instance()->insertSprite("game.floor_dark",   "game_background",   50,   50,   0, 0);
	SpriteManager::instance()->insertSprite("game.floor_bright", "game_background",   50,   50,  50, 0);
	SpriteManager::instance()->insertSprite("game.floor_shadow", "game_background",   50,   50, 100, 0);
	SpriteManager::instance()->insertSprite("game.floor_spots",  "game_background_spots", 3840, 2160,   0, 0);

	SpriteManager::instance()->insertSprite("game.dative",   "dative", 50, 50, 0, 0);

	SpriteManager::instance()->insertSprite("game.box",   "game_background_block", 50, 70, 50, 0);
	SpriteManager::instance()->insertSprite("game.stone", "game_background_block", 50, 70,  0, 0);

	SpriteManager::instance()->insertSprite("game.door_close", "game_door_close", 45, 47,  0, 0);
	SpriteManager::instance()->insertSprite("game.door_open", "game_door_open", 45, 47,  0, 0);

	SpriteManager::instance()->insertSprite("game.wall",   "game_wall",    1, 108, 0, 0);
	SpriteManager::instance()->insertSprite("game.ledder", "game_ledder", 18,  99, 0, 0);

	SpriteManager::instance()->insertSprite("text.hp", "text_hp", 19, 12, 0, 0);
	SpriteManager::instance()->insertSprite("text.score", "text_score", 37, 10, 0, 0);

	SpriteManager::instance()->insertSprite("text.white_player_win", "text_win_white", 192, 14, 0, 0);
	SpriteManager::instance()->insertSprite("text.black_player_win", "text_win_black", 194, 14, 0, 0);

	SpriteManager::instance()->insertSprite("gui.health_bar",       "gui_health_bar", 1, 16, 0, 0);
	SpriteManager::instance()->insertSprite("gui.health_bar_left",  "gui_health_bar", 2, 16, 1, 0);
	SpriteManager::instance()->insertSprite("gui.health_bar_right", "gui_health_bar", 2, 16, 3, 0);

	SpriteManager::instance()->insertSprite("ui.white_avatar", "ui_white_avatar", 63, 63, 0, 0);
	SpriteManager::instance()->insertSprite("ui.black_avatar", "ui_black_avatar", 63, 63, 0, 0);

	SpriteManager::instance()->insertSprite("game.bomb", "game_bomb", 23, 25, 0, 0);
	SpriteManager::instance()->insertSprite("game.bomb_red", "game_bomb_red", 22, 28, 0, 0);
	SpriteManager::instance()->insertSprite("game.bomb_black", "game_bomb_black", 22, 28, 0, 0);

	SpriteManager::instance()->insertSprite("game.explosion", "game_explosion", 50, 50, 0, 0, true, 60);
	SpriteManager::instance()->insertSprite("game.smoke", "game_smoke", 50, 50, 0, 0, true, 60);

	SpriteManager::instance()->insertSprite("collectible.hp.minusone", "collectible_hp_minuone", 25, 28, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.hp.one",      "collectible_hp_one",     25, 28, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.hp.many",     "collectible_hp_three",   37, 31, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.hp.max",      "collectible_hp_five",    41, 39, 0, 0);

	SpriteManager::instance()->insertSprite("collectible.bomb.minusone", "collectible_bomb_minuone", 26, 36, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.bomb.one",      "collectible_bomb_one",     26, 36, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.bomb.many",     "collectible_bomb_three",   36, 36, 0, 0);
	SpriteManager::instance()->insertSprite("collectible.bomb.max",      "collectible_bomb_five",    42, 46, 0, 0);

	SpriteManager::instance()->insertSprite("player.white_down",  "character_player_white_down",  27, 42, 0, 0, true, 15);
	SpriteManager::instance()->insertSprite("player.white_top",   "character_player_white_top",   27, 41, 0, 0, true, 15);
	SpriteManager::instance()->insertSprite("player.white_left",  "character_player_white_left",  32, 42, 0, 0, true, 15);
	SpriteManager::instance()->insertSprite("player.white_right", "character_player_white_right", 33, 42, 0, 0, true, 15);

	/*Sprite::instance()->insertSprite("Enemi_down",  "Enemy1_GoDown", 33, 32, 0, 0,  true, 3);
	Sprite::instance()->insertSprite("Enemi_right", "Enemy1_GoRight", 33, 32, 0, 0, true, 3);
	Sprite::instance()->insertSprite("Enemi_left",  "Enemy1_GoLeft", 33, 32, 0, 0,  true, 3);
	Sprite::instance()->insertSprite("Enemi_top",   "Enemy1_GoTop", 33, 32, 0, 0,   true, 3);
*/
	SpriteManager::instance()->insertSprite("enemy.bat_top",   "character_bat_top",   32, 43, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.bat_down",  "character_bat_down",  32, 43, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.bat_left",  "character_bat_left",  32, 43, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.bat_right", "character_bat_right", 32, 43, 0, 0, true, 4);

	SpriteManager::instance()->insertSprite("enemy.death_top",   "character_death_top",   48, 46, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.death_down",  "character_death_down",  48, 46, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.death_left",  "character_death_left",  48, 46, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.death_right", "character_death_right", 48, 46, 0, 0, true, 4);

	SpriteManager::instance()->insertSprite("enemy.glimmer_left",  "character_glimmer_left",  33, 32, 0, 0, true, 3);
	SpriteManager::instance()->insertSprite("enemy.glimmer_right", "character_glimmer_right", 33, 32, 0, 0, true, 3);
	SpriteManager::instance()->insertSprite("enemy.glimmer_top",   "character_glimmer_top",   33, 32, 0, 0, true, 3);
	SpriteManager::instance()->insertSprite("enemy.glimmer_down",  "character_glimmer_down",  33, 32, 0, 0, true, 3);

	SpriteManager::instance()->insertSprite("enemy.zombie_top",   "character_death_top",   48, 46, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.zombie_down",  "character_zombie_down", 40, 54, 0, 0, true, 3);
	SpriteManager::instance()->insertSprite("enemy.zombie_left",  "character_death_left",  48, 46, 0, 0, true, 4);
	SpriteManager::instance()->insertSprite("enemy.zombie_right", "character_death_right", 48, 46, 0, 0, true, 4);

	/*Sprite::instance()->insertSprite("Death_top",  "Death_Top", 47, 46, 0, 0,  true, 4);
	Sprite::instance()->insertSprite("Death_down", "Death_Down", 47, 46, 0, 0, true, 4);
	Sprite::instance()->insertSprite("Death_left",  "Death_Left", 47, 46, 0, 0,  true, 4);
	Sprite::instance()->insertSprite("Death_right",   "Death_Right", 47, 46, 0, 0,   true, 4);*/

	/* Load sounds */
	SoundManager::registerSound("Data/audio/Bomb_Explode.ogg", "bomb.explode");
	SoundManager::registerSound("Data/audio/bonus.ogg", "bonus.put_up");
	SoundManager::registerSound("Data/audio/bombard.ogg", "bomb.bombard");
	SoundManager::registerSound("Data/audio/player_hit.ogg", "player.hit");
	SoundManager::registerSound("Data/audio/bomb_put.ogg", "bomb.put");

	/* Load music */
	SoundManager::registerMusic("Data/audio/menu_aurora.ogg", "menu.aurora");

	SoundManager::registerMusic("Data/audio/game_1.ogg", "game.ff");
	SoundManager::registerMusic("Data/audio/game_2.ogg", "game.ffs");
	SoundManager::registerMusic("Data/audio/game_3.ogg", "game.ffd");

	Menu menu;

	bool done = false;
	while(!done) {
		Game::GameType type = menu.show(Menu::OptionsType::play);

		uint sceen_width = (Window::instance()->desktopWidth - 100) / 50;
		uint sceen_height = (Window::instance()->desktopHeight - 100) / 50;

		if(type == Game::GameType::oneVsBot || type == Game::GameType::twoVsBot || type == Game::GameType::oneVsOne) {
			Window::instance()->init(sceen_width * 50, sceen_height * 50, Constants::Video::SCREEN_TITLE, sf::Style::None);

			Game game;
			game.init(type);

		} else if(type == Game::GameType::none)
			done = true;
	}

	Window::instance()->close();

	while(Window::instance()->isOpen()) {

		Window::instance()->getRW()->Clear();

		Window::instance()->getRW()->Display();
	}
}

