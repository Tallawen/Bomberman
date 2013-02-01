#ifndef __GAME_H__
#define __GAME_H__

#include "StdAfx.h"

#include "Renderer/Window.h"

#include "World/World.h"

class Game {
public:

private:
	World *world;

	const sf::Input& input;

public:
	Game();

	void startGame(int id);

private:
	void playerControl();
	void changePlayerField();

};





#endif /*__GAME_H__*/
