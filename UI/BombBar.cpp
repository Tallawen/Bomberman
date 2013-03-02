#include "BombBar.h"

#include "../Renderer/Window.h"

BombBar::BombBar(Player *_playerPtr, sf::Vector2f _position) {
	playerPtr = _playerPtr;

	position = _position;
	amount = 0;

	sprite = SpriteManager::instance()->getSprite("game.bomb");
	sd = SpriteManager::instance()->getSpriteData("game.bomb");
}

void BombBar::draw(float dt) {
	if(amount < -1) amount = 0;
	else if(amount > Constants::Bomb::MAX_AMOUNT + 1) amount = Constants::Bomb::MAX_AMOUNT;

	int i = 0, xTmp;

	sprite.SetColor(sf::Color(255, 255, 255, 255));

	while(i < amount) {
		xTmp = position.x + i * sd.dimensions.x + i * Constants::UI::BombBar::OFFSET();

		sprite.SetPosition(xTmp, position.y);
	    Window::instance()->getRW()->Draw(sprite);

	    ++i;
	}

	sprite.SetColor( sf::Color(255, 255, 255, Constants::UI::BombBar::ALPHA) );

	while(i < Constants::Bomb::MAX_AMOUNT) {
		xTmp = position.x + i * sd.dimensions.x + i * Constants::UI::BombBar::OFFSET();

		sprite.SetPosition(xTmp, position.y);
		Window::instance()->getRW()->Draw(sprite);

		++i;
	}
}

void BombBar::update(float dt) {
	amount = playerPtr->getBombAmount();
}
