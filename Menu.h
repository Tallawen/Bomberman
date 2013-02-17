#ifndef __MENU_H__
#define __MENU_H__

#include "StdAfx.h"

class Menu {
public:

private:
	/**
	 * 0 - StartGame
	 * 1 - StartGameActive
	 * 2 - About
	 * 3 - AboutActive
	 * 4 - Exit
	 * 5 - ExitActive
	 *
	 */
	sf::Sprite text[6];
	sf::Sprite background;

	/**
	 * Liczba opcji wyswietlanych w glownym oknie menu
	 */
	const int maxOptions;

	/**
	 * Kolejnosc wedlug id*2 z tablicy text[]
	 */
	enum class OptionsType {
		StartGame, // 0
		About,     // 1
		Exit       // 2
	};

public:
	Menu();

	/**
	 * Uruchamia glowne menu
	 *
	 * @param id id opcji ktora ma byc wybrana na poczatku
	 * @return 1 jesli uruchomilismy gre
	 * @return 0 jesli wyszlismy
	 *
	 */
	int main(int id);

	/**
	 * Wyswietla subwindow z opcjami
	 *
	 */
	void options();

	/**
	 * Wyswietla subwindow z informacjami
	 *
	 */
	void about();

	void createTest();

private:

};

#endif /*__MENU_H__*/
