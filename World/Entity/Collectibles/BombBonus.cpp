#include "BombBonus.h"

BombBonus::BombBonus(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate, Amount health) : Collectible(_position, _entitiesToCreate) {
	amount = health;

	// set texture based on amount
	 std::string spriteName;
	switch(health) {
	    case Amount::minusone: spriteName = "collectible.bomb.minusone"; break;
	    case Amount::one: spriteName = "collectible.bomb.one"; break;
	    case Amount::many: spriteName = "collectible.bomb.many"; break;
	    case Amount::max: spriteName = "collectible.bomb.max"; break;
	}

	sprite = SpriteManager::instance()->getSprite(spriteName);
	sd = SpriteManager::instance()->getSpriteData(spriteName);

	sprite.SetPosition(position);
}

void BombBonus::collect(Player* player) {
	int currBombs = player->getBombAmount();
	int newBombs = currBombs + int(amount);
	int points = (newBombs > Constants::Bomb::MAX_AMOUNT) ? newBombs - Constants::Bomb::MAX_AMOUNT : 0;

	if (newBombs <= 0)  // Bonus can't kill player
		player->setBombAmount(1);

	else {
		player->setBombAmount(newBombs);
		player->addScores(points);
	}
}
