#ifndef __MENU_H__
#define __MENU_H__

#include "StdAfx.h"

#include "Game.h"

class Menu {
private:
	/**
	 * 0 - StartGame
	 * 1 - StartGameActive
	 * 2 - About
	 * 3 - AboutActive
	 *
	 */
	sf::Sprite text[4];
	sf::Sprite background;

	/**
	 * Liczba opcji wyswietlanych w glownym oknie menu
	 */
	const int maxOptions;

public:
	/**
	 * Kolejnosc wedlug id*2 z tablicy text[]
	 */
	enum class OptionsType {
		play, // 0
		about, // 1
		exit
	};

public:
	Menu();

	/**
	 * Uruchamia glowne menu
	 *
	 * @param type typ opcji ktort ma byc wybrana na poczatku
	 *
	 */
	Game::PlayType show(OptionsType type);

	/**
	 * Wyswietla subwindow z informacjami
	 *
	 */
	void about();

	Game::PlayType play();
};

#endif /*__MENU_H__*/
