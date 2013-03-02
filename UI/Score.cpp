#include "Score.h"

Scores::Scores(Player *_playerPtr, sf::Vector2f _position) : scores("Data/gfx/text/comfortaa.ttf") {
	playerPtr = _playerPtr;

	position = _position;

	sprite = SpriteManager::instance()->getSprite("text.score");
	sd = SpriteManager::instance()->getSpriteData("text.score");

	sprite.SetPosition(position);

	scores.setSize(10);
	scores.setStyle(sf::String::Style::Bold);
	scores.setColor(sf::Color(182, 182, 173));
	scores.setPosition(position.x + 43, position.y - 10);
}

void Scores::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);
	Window::instance()->getRW()->Draw(scores);
}

void Scores::update(float dt) {
	scores.setText(intToStr(playerPtr->getScores()));
}

std::string Scores::intToStr(int i) {
	std::ostringstream ss;
	ss << i;

  return ss.str();
}
