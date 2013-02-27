#include "UI.h"

#include "constants.h"

#include "Renderer/Window.h"


UI::UI(bool secondPlayer) {
	health = -1;
	newLenght = 0;
	healthBar = nullptr;
	fps = nullptr;
	scoresPtr = nullptr;

	float xHealthBar = Constants::UI::HealthBar::X;

	float xBombBarPos = Constants::UI::BombBar::X;

	if(secondPlayer) {
		xHealthBar  = Window::instance()->getWidth() - Constants::UI::HealthBar::LENGHT - Constants::UI::HealthBar::X;
		xBombBarPos = Window::instance()->getWidth() - Constants::UI::HealthBar::LENGHT - Constants::UI::BombBar::X;
	}

	healthBarPos = sf::Vector2f(xHealthBar, Constants::UI::HealthBar::Y);
	bombBarPos   = sf::Vector2f(xBombBarPos, Constants::UI::BombBar::Y);
}

void UI::drawHealthBar(int newHealth) {
	uint lenght = Constants::UI::HealthBar::LENGHT;
	SpriteData sd = SpriteManager::instance()->getSpriteData("gui.health_bar");

	if(healthBar == nullptr) {
		/** ryzowanie lewej czesci belki **/
		sprite = SpriteManager::instance()->getSprite("gui.health_bar_left");

		sprite.SetPosition(healthBarPos.x, healthBarPos.y);
		Window::instance()->getRW()->Draw(sprite);

		/** rysowanie srodkowej czesci belki **/
		sprite = SpriteManager::instance()->getSprite("gui.health_bar");

		for(uint i = 0; i < lenght; ++i) {
			sprite.SetPosition(healthBarPos.x + i + 2, healthBarPos.y);
			Window::instance()->getRW()->Draw(sprite);
		}

		/** rysowanie prawej czesci belki **/
		sprite = SpriteManager::instance()->getSprite("gui.health_bar_right");

		sprite.SetPosition(healthBarPos.x + lenght + 2, healthBarPos.y);
		Window::instance()->getRW()->Draw(sprite);

		/** koniec rysowania **/

		newHealthBarImg = Window::instance()->getRW()->Capture();
		newHealthBarImg.SetSmooth(false);

		healthBar = new sf::Sprite(newHealthBarImg);
		healthBarAlpha = new sf::Sprite(newHealthBarImg);

		healthBar->SetCenter(0, sd.dimensions.y);
		healthBarAlpha->SetCenter(0, sd.dimensions.y);

		healthBar->SetPosition(healthBarPos);
		healthBarAlpha->SetPosition(healthBarPos);

		healthBar->SetSubRect( sf::IntRect(healthBarPos.x,
				                           healthBarPos.y - sd.dimensions.y,
				                           healthBarPos.x + lenght,
				                           healthBarPos.y) );

		healthBarAlpha->SetSubRect( sf::IntRect(healthBarPos.x,
				                                healthBarPos.y - sd.dimensions.y,
						                        healthBarPos.x + lenght + 4,
						                        healthBarPos.y) );

		healthBarAlpha->SetColor( sf::Color(255, 255, 255, Constants::UI::HealthBar::ALPHA) );
	}

	if(newHealth > -1 && newHealth < Constants::Player::MAX_HEALTH + 1 && health != newHealth ) {
		newLenght = lenght / Constants::Player::MAX_HEALTH * newHealth;

		healthBar->SetSubRect( sf::IntRect(healthBarPos.x,
				                           healthBarPos.y - sd.dimensions.y,
						                   healthBarPos.x + newLenght + 2,
						                   healthBarPos.y) );

		health = newHealth;
	}

	Window::instance()->getRW()->Draw(*healthBarAlpha);
	Window::instance()->getRW()->Draw(*healthBar);

	/** rysowanie prawej czesci belki **/
	sprite = SpriteManager::instance()->getSprite("gui.health_bar_right");

	sprite.SetPosition(healthBarPos.x + newLenght + 2, healthBarPos.y);
	Window::instance()->getRW()->Draw(sprite);
}

void UI::drawBombBar(int bombAmount) {
	if(bombAmount < -1) bombAmount = 0;
	else if(bombAmount > Constants::Bomb::MAX_AMOUNT + 1) bombAmount = Constants::Bomb::MAX_AMOUNT;

	int i = 0, xTmp;

	SpriteData sd = SpriteManager::instance()->getSpriteData("game.bomb");

	sprite = SpriteManager::instance()->getSprite("game.bomb");

	while(i < bombAmount) {
		xTmp = bombBarPos.x + i * sd.dimensions.x + i * Constants::UI::BombBar::OFFSET();

		sprite.SetPosition(xTmp, bombBarPos.y);
		Window::instance()->getRW()->Draw(sprite);

		++i;
	}

	sprite.SetColor( sf::Color(255, 255, 255, Constants::UI::BombBar::ALPHA) );

	while(i < Constants::Bomb::MAX_AMOUNT) {
		xTmp = bombBarPos.x + i * sd.dimensions.x + i * Constants::UI::BombBar::OFFSET();

		sprite.SetPosition(xTmp, bombBarPos.y);
		Window::instance()->getRW()->Draw(sprite);

		++i;
	}
}

void UI::drawFPS(float dt) {
	static float time = 0;
	static float frames = 0;
	static float nFPS = 0;

	if(fps == nullptr) {
		fps = new sf::String;

		fps->SetPosition(Constants::UI::FPS::X, Constants::UI::FPS::Y);
		fps->SetColor(sf::Color::White);
		fps->SetSize(Constants::UI::FPS::SIZE);

		fps->SetText("FPS");
	}

	time += dt;
	++frames;

	if(time >= 1.0f) {
		nFPS = frames / time;

		frames = 0;
		time = 0.0f;

		std::ostringstream ss;
		ss << nFPS;

		fps->SetText(ss.str());
	}

	Window::instance()->getRW()->Draw(*fps);
}

void UI::drawBoard() {
	static bool create = false;

	if(!create) {
		board = sf::Shape::Rectangle(
				2,
				2,
				Window::instance()->getWidth()-2,
				Window::instance()->getHeight()-2,
				sf::Color(255, 255, 255, 0),
				4,
				sf::Color::Black
		);

		create = true;
	}
	else
		Window::instance()->getRW()->Draw(board);


}

void UI::drawScores(int scores) {
	if(scoresPtr == nullptr) {
		scoresPtr = new sf::String;

		scoresPtr->SetPosition(30, 100);
		scoresPtr->SetColor(sf::Color::White);
		scoresPtr->SetSize(Constants::UI::FPS::SIZE);

		scoresPtr->SetText("scores");
	}


	std::ostringstream ss;
	ss << scores;

	scoresPtr->SetText(ss.str());

	Window::instance()->getRW()->Draw(*scoresPtr);
}
