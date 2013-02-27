#include "Animation.h"

#include "Window.h"

/***********************************************************************************
 Animation :: methods
 *********************/
Animation::Animation(sf::Sprite _sprite, SpriteData _info, bool _autoDraw, bool _autoStop) {
	sprite = _sprite;
	info = _info;
	autoDraw = _autoDraw;
	autoStop = _autoStop;
	playAnimation = false;

	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0.0f;

	delayAccumulation = 0.0f;
	delayTime = 0.0f;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::play() {
	if(!playAnimation)
		timeAccumulation = 0.0f;

	playAnimation = true;
}

void Animation::stop() {
	playAnimation = false;

	delayAccumulation = 0.0f;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::pause() {
	playAnimation = false;
}

void Animation::setDelay(float delay) {
	if(delay <= 0) return;

	delayAccumulation = 0.0f;
	delayTime = delay;
}

void Animation::setSprite(sf::Sprite _sprite, const SpriteData &_info) {
	sprite = _sprite;
	info = _info;

	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::draw() {
	Window::instance()->getRW()->Draw(sprite);
}

void Animation::process(float dt) {
	if(playAnimation) {
		if(delayAccumulation >= delayTime) {

			timeAccumulation += dt;
			while(timeAccumulation > timePerFrame) {
				sf::IntRect rect = sprite.GetSubRect();
				rect.Offset(info.dimensions.x, 0);

				if(rect.Right >= (info.frame * info.dimensions.x)) {
					rect.Left = 0;
					rect.Right = info.dimensions.x;

					if(autoStop) stop();
				}

				sprite.SetSubRect(rect);

				timeAccumulation -= timePerFrame;
			}
		} else
			delayAccumulation += dt;
	}

	if(autoDraw) draw();
}

void Animation::setPosition(sf::Vector2f newPosition) {
	if(newPosition.x < 0 || newPosition.y < 0) return;

	sprite.SetPosition(newPosition);
}
