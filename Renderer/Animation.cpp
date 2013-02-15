#include "Animation.h"

/***********************************************************************************
 Animation :: methods
 *********************/
Animation::Animation(sf::Sprite _sprite, const SpriteData &_info, bool _autoDraw, bool _autoStop) : sprite(_sprite), info(_info), playAnimation(false), autoDraw(_autoDraw), autoStop(_autoStop) {
	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0;

	rotationAngle = 0.f;
	rotationSpeed = 0.f;
	rotationTimeAccumulation = 0.f;
	rotationDirection = Animation::RotationDirection::none;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::setSprite(sf::Sprite _sprite, const SpriteData &_info) {
	sprite = _sprite;
	info = _info;

	timePerFrame = float(1 / float(info.frame));
	timeAccumulation = 0;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::process(float dt) {
	if(playAnimation) {
		if(delayAccumulation >= delayPerFrame) {

			timeAccumulation += dt;
			while(timeAccumulation > timePerFrame) {
				sf::IntRect rect = sprite.GetSubRect();
				rect.Offset(info.dimensions.x, 0);

				if(rect.Right >= (info.frame*info.dimensions.x)) {
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

	rotate(dt);

	if(autoDraw) draw();
}

void Animation::play() {
	if(!playAnimation) timeAccumulation = 0;
	playAnimation = true;
}

void Animation::stop() {
	playAnimation = false;

	delayAccumulation = 0;

	sprite.SetSubRect(sf::IntRect(0, 0, info.dimensions.x, info.dimensions.y));
}

void Animation::pause() {
	playAnimation = false;
}

sf::Sprite* Animation::getSprite() {
  return &sprite;
}

void Animation::setAutoStop(bool _autoStop) {
	autoStop = _autoStop;
}

void Animation::setAutoDraw(bool _autoDraw) {
	autoDraw = _autoDraw;
}

void Animation::setDelay(float delay) {
	delayAccumulation = 0;
	delayPerFrame = delay;
}

void Animation::draw() {
	Window::instance()->getRW()->Draw(sprite);
}


void Animation::setPos(sf::Vector2f newPos) {
	sprite.SetPosition(newPos);
}


sf::Vector2f Animation::getPos() {
  return sprite.GetPosition();
}


SpriteData Animation::getSpriteInfo() {
  return info;
}


void Animation::rotate(RotationDirection rd, float speed) {
	if(rotationDirection == RotationDirection::none && rd != RotationDirection::none) {
		sprite.SetCenter(info.dimensions.x / 2, info.dimensions.y / 2);
		sprite.Move(info.dimensions.x / 2, -info.dimensions.y / 2);
	} else 	if(rotationDirection != RotationDirection::none && rd != RotationDirection::none) {
		sprite.SetCenter(info.dimensions.x / 2, info.dimensions.y / 2);
		sprite.Move(-info.dimensions.x / 2, info.dimensions.y / 2);
		sprite.Move(info.dimensions.x / 2, -info.dimensions.y / 2);
	} else if (rotationDirection != RotationDirection::none && rd == RotationDirection::none) {
		sprite.SetCenter(0, info.dimensions.y);
		sprite.Move(-info.dimensions.x / 2, info.dimensions.y / 2);
	}

	rotationSpeed = 1.f / (speed * 60);
	rotationTimeAccumulation = 0;
	rotationDirection = rd;

	rotationDirection == RotationDirection::left ? rotationAngle = -1 : rotationAngle = 1;
}


void Animation::rotate(float dt) {
	if(rotationDirection == RotationDirection::none) return;

	rotationTimeAccumulation += dt;
	while(rotationTimeAccumulation > rotationSpeed) {
		sprite.Rotate(rotationAngle * dt);

		rotationTimeAccumulation -= rotationSpeed;
	}
}
