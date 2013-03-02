#include "HealthBonus.h"

HealthBonus::HealthBonus(sf::Vector2f _position,
		std::queue<Entity*> *_entitiesToCreate, Amount health) :
	Collectible(_position, _entitiesToCreate) {

	amount = health;

	// set texture based on amount
	std::string spriteName;
	switch(health){
	case Amount::minusone: spriteName = "collectible.hp.minusone"; break;
	case Amount::one: spriteName = "collectible.hp.one"; break;
	case Amount::many: spriteName = "collectible.hp.many"; break;
	case Amount::max: spriteName = "collectible.hp.max"; break;
	}
	sprite = SpriteManager::instance()->getSprite(spriteName);
	sd = SpriteManager::instance()->getSpriteData(spriteName);

}

void HealthBonus::collect(Player* player) {
	int currHealth = player->getHealthAmount();
	int newHealth = currHealth+int(amount);
	int points = (newHealth > Constants::Player::MAX_HEALTH)
			? newHealth - Constants::Player::MAX_HEALTH
			: 0 ;

	if (newHealth <= 0) { // Bonus can't kill player
		player->setHealthAmount(1);
	} else {
		player->setHealthAmount(newHealth);
		player->addScores(points);
	}
}
