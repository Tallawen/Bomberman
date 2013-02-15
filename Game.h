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
	/// Eventy wymagajace tylko reakcji na klikniecie
	void playerControl(sf::Event &event);

	/// Eventy dzialajace w czasie trzymania klawisza
	void playerControlRealtime();

	void inline playerControl(sf::Key::Code keyCode, sf::Vector2f velocity, Player* player, World::Direction direction);

	void changePlayerField();

};

#endif /*__GAME_H__*/
