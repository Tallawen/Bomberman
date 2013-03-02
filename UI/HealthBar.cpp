#include "HealthBar.h"

#include "../constants.h"

HealthBar::HealthBar(Player *_playerPtr, sf::Vector2f _position) : MAX_LENGHT(Constants::UI::HealthBar::LENGHT), amountText("Data/gfx/text/comfortaa.ttf") {
	playerPtr = _playerPtr;
	healthAmount = playerPtr->getHealthAmount();

	position = _position;

	hpSd = SpriteManager::instance()->getSpriteData("text.hp");
	sd = SpriteManager::instance()->getSpriteData("gui.health_bar");

	barPosition = sf::Vector2f(position.x + hpSd.dimensions.x + 5, position.y);
	lenght = MAX_LENGHT / Constants::Player::MAX_HEALTH * healthAmount;

	create();
}

void HealthBar::create() {
	hpText = SpriteManager:: instance()->getSprite("text.hp");
	hpText.SetPosition(position.x, position.y - 2);

	/** ryzowanie lewej czesci belki **/
	sprite = SpriteManager::instance()->getSprite("gui.health_bar_left");

	sprite.SetPosition(barPosition);
	Window::instance()->getRW()->Draw(sprite);

	/** rysowanie srodkowej czesci belki **/
	sprite = SpriteManager::instance()->getSprite("gui.health_bar");

	for(int i = 0; i < MAX_LENGHT; ++i) {
		sprite.SetPosition(barPosition.x + i + 2, barPosition.y);
		Window::instance()->getRW()->Draw(sprite);
	}

	/** rysowanie prawej czesci belki **/
	sprite = SpriteManager::instance()->getSprite("gui.health_bar_right");

	sprite.SetPosition(barPosition.x + MAX_LENGHT + 2, barPosition.y);
	Window::instance()->getRW()->Draw(sprite);


	img = Window::instance()->getRW()->Capture();
	img.SetSmooth(false);

	bar.SetImage(img);
	barAlpha.SetImage(img);

	bar.SetCenter(0, sd.dimensions.y);
	barAlpha.SetCenter(0, sd.dimensions.y);

	bar.SetPosition(barPosition);
	barAlpha.SetPosition(barPosition);

	bar.SetSubRect(sf::IntRect(barPosition.x,
			                   barPosition.y - sd.dimensions.y,
			                   barPosition.x + MAX_LENGHT + 2,
			                   barPosition.y));

	barAlpha.SetSubRect(sf::IntRect(barPosition.x,
			                        barPosition.y - sd.dimensions.y,
			                        barPosition.x + MAX_LENGHT + 4,
			                        barPosition.y));

	barAlpha.SetColor(sf::Color(255, 255, 255, Constants::UI::HealthBar::ALPHA));


	/** dorysowywanie prawej czesci belki oznaczajacej zycie (przy zmianie) **/
	sprite = SpriteManager::instance()->getSprite("gui.health_bar_right");
	sprite.SetPosition(barPosition.x + lenght + 1, barPosition.y);

	amountText.setColor(sf::Color(255, 255, 255, 20));
	amountText.setSize(9);
	amountText.setStyle(sf::String::Style::Bold);
	amountText.setPosition(barPosition.x + (MAX_LENGHT - 20) / 2, barPosition.y - 13);
	amountText.setText(intToStr(healthAmount) + " / " + intToStr(Constants::Player::MAX_HEALTH));
}

void HealthBar::update(float dt) {
	if(playerPtr->getHealthAmount() > -1 && playerPtr->getHealthAmount() < Constants::Player::MAX_HEALTH + 1 && healthAmount != playerPtr->getHealthAmount() ) {
		healthAmount = playerPtr->getHealthAmount();

		lenght = MAX_LENGHT / Constants::Player::MAX_HEALTH * healthAmount;

		bar.SetSubRect(sf::IntRect(barPosition.x,
				                   barPosition.y - sd.dimensions.y,
				                   barPosition.x + lenght + 2,
				                   barPosition.y));

		sprite.SetPosition(barPosition.x + lenght + 2, barPosition.y);

		amountText.setText(intToStr(healthAmount) + " / " + intToStr(Constants::Player::MAX_HEALTH));
	}
}

void HealthBar::draw(float dt) {
	Window::instance()->getRW()->Draw(hpText);
	Window::instance()->getRW()->Draw(barAlpha);
	Window::instance()->getRW()->Draw(bar);
	Window::instance()->getRW()->Draw(amountText);
	Window::instance()->getRW()->Draw(sprite);
}


std::string HealthBar::intToStr(int i) {
	std::ostringstream ss;
	ss << i;

  return ss.str();
}
