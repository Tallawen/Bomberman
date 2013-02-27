#ifndef __GAME_H__
#define __GAME_H__

#include "StdAfx.h"

#include "World/World.h"

#include "World/Entity/Player.h"

class World;

class Game {
public:
	World *world;

	const sf::Input& input;

	std::vector<Player*> players;

	bool play;
	bool end;

	enum class PlayType {
		oneVsBot,
		twoVsBot,
		oneVsOne,
		none
	};


private:
	int level;

	sf::Music *musics[3];
	int musicId;

public:
	Game();
	~Game();

	void game(int id);
	void init(int id);

private:
	/// Eventy wymagajace tylko reakcji na klikniecie
	void playerControl(sf::Event &event);

	/// Eventy dzialajace w czasie trzymania klawisza
	void playerControlRealtime();

	void inline playerControl(sf::Key::Code keyCode, Player* player, Entity::EntityState state);

	void checkCollisionOfOnePair(
		     Entity *entityFirst, Entity::EntityType firstType,
		     Entity *entitySecond, Entity::EntityType secondType, float dt
		 );

	void checkEntityEntityCollisions(float dt);

	sf::Key::Code pauseMenu();
};

#endif /*__GAME_H__*/
