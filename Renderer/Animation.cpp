#include "Animation.h"

/***********************************************************************************
 Animation :: methods
 *********************/
Animation::Animation(sf::Sprite *_sprite, const SpriteData &_info, bool _autoDraw) : sprite(_sprite), info(_info), playAnimation(false), autoDraw(_autoDraw) {
	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0;

	sprite->SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::setSprite(sf::Sprite *_sprite, const SpriteData &_info) {
	sprite = _sprite;
	info = _info;

	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0;

	sprite->SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::process(float dt) {
	if(playAnimation) {

		timeAccumulation += dt;
		while(timeAccumulation > timePerFrame) {

			sf::IntRect rect = sprite->GetSubRect();
			rect.Offset(info.dimensions.x, 0);

			if(rect.Right >= (info.frame*info.dimensions.x)) {
				rect.Left = 0;
				rect.Right = info.dimensions.x;
			}

			sprite->SetSubRect(rect);

			timeAccumulation -= timePerFrame;
		}
	}

if(autoDraw) draw();
}

void Animation::play() {
	if(!playAnimation) timeAccumulation = 0;
	playAnimation = true;
}

void Animation::stop() {
	playAnimation = false;

	sprite->SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::pause() {
	playAnimation = false;
}

sf::Sprite* Animation::getSprite() {
  return sprite;
}

void Animation::draw() {
	Window::instance()->getRW()->Draw(*sprite);
}

void Animation::setPos(sf::Vector2f newPos) {
	sprite->SetPosition(newPos);
}

sf::Vector2f Animation::getPos() {
  return sprite->GetPosition();
}

SpriteData Animation::getSpriteInfo() {
  return info;
}
