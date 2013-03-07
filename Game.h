#ifndef __GAME_H__
#define __GAME_H__

#include "StdAfx.h"

#include "UI/UI.h"

#include "World/World.h"
#include "World/Entity/Player.h"

class World;

class Game {
public:
	enum class GameType {
		oneVsBot,
		twoVsBot,
		oneVsOne,
		none
	};

	enum class PS3Button {
		triangle = 0,
		cross = 2,
		quad = 3,
		circle = 1,
		R1 = 7,
		L1 = 6,
		start = 9,
		select = 8
	};

	enum class PS3Move {
		top = 0,
		right = 90,
		down = 180,
		left = 270
	};

	enum class PS3Joystic {
		first = 0,
		second = 1
	};

public:
	World *world;
	const sf::Input& input;

	std::vector<Player*> players;

	bool play;
	bool end;

private:
	int level;

	bool throwHp;

	/**
	 * Wskaznik na funkcje ruchu jednostek
	 * 0 - goLeft
	 * 1 - goRight
	 * 2 - goTop
	 * 3 - goDown
	 */
	void (Entity::*movePtr[4])();

	GameType type; /// typ gry

	int musicId;
	sf::Music *music[3];

public:
	Game();
	~Game();

	void init(GameType type);
	void game();

private:
	/// Eventy wymagajace tylko reakcji na klikniecie
	void playerControl(sf::Event &event, sf::Clock &clock);

	/// Eventy dzialajace w czasie trzymania klawisza
	void playerControlRealtime();

	void inline playerControl(sf::Key::Code keyCode, PS3Joystic ps3JoysticId, PS3Move ps3Move, Player* player, Entity::EntityState state);

	void raid(int playerId);
	void dativeOn(sf::Event &event, int playerId);

	void checkCollisionOfOnePair(
		     Entity *entityFirst, Entity::EntityType firstType,
		     Entity *entitySecond, Entity::EntityType secondType, float dt
		 );

	void checkEntityEntityCollisions(float dt);

	void throwCollectible(sf::Vector2f position, bool ignore = false);

	void inline addUI(UI &ui);

	sf::Shape inline border();

	void inline changeMusic();

	sf::Vector2f idToPosition(int id);

	bool inline keyPressed(sf::Event &event, sf::Key::Code keyCode);
	bool inline buttonPressed(sf::Event &event, PS3Joystic joystic, PS3Button button);
	bool inline buttonPressed(sf::Event &event, PS3Joystic joystic, PS3Move move);


	/**
	 * Wywouje sub-onko (menu)
	 * @return kod wcisnietego klawisza
	 */
	sf::Key::Code pauseMenu();

	/**
	 * Wywoluje sub-okno z informacjami o sterowaniu
	 */
	void helpWindow();

	/**
	 * Wywo³uje sub-okno z informacja kto wygral
	 * @param playerId id gracza ktory wygral
	 *
	 * @retval false jesli gracz chce zrestartowac gre
	 * @retval true jesli gracz chce wyjsc do glownego menu
	 **/
	bool winWindow(int playerId);
};

#endif /*__GAME_H__*/
