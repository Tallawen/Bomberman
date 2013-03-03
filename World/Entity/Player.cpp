#include "Player.h"

#include "Bomb.h"

Player::Player(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 100.0f, 100.0f, _entitiesToCreate) {
	hitboxOffset = sf::Vector2f(0, 0);

	maxBombAmount = Constants::Bomb::MAX_AMOUNT;
	bombAmount  = Constants::Bomb::START_AMOUNT;

	healthAmount = Constants::Player::HEALTH;
	maxHealthAmount = Constants::Player::MAX_HEALTH;

	explosionLength = Constants::Explosion::LENGTH;

	totalScores = 0;

	immortal = false;

	goingDone = true;
	isGoing = false;

	lockMovement = false;
	lockKey = false;

	state = EntityState::stand;

	sprite = SpriteManager::instance()->getSprite("player.white_down");
	sd = SpriteManager::instance()->getSpriteData("player.white_down");

	left = new Animation(
			SpriteManager::instance()->getSprite("player.white_left"),
			SpriteManager::instance()->getSpriteData("player.white_left"));

	right = new Animation(
			SpriteManager::instance()->getSprite("player.white_right"),
			SpriteManager::instance()->getSpriteData("player.white_right"));

	top = new Animation(
			SpriteManager::instance()->getSprite("player.white_top"),
			SpriteManager::instance()->getSpriteData("player.white_top"));

	down = new Animation(
			SpriteManager::instance()->getSprite("player.white_down"),
			SpriteManager::instance()->getSpriteData("player.white_down"));

	stopDown();
}

Player::~Player() { }

void Player::update(float dt) {
	if(healthAmount <= 0)
		isDead = true;

	going(dt);

	if(immortal) {
		if(blinkingTime > Constants::Player::BLINK_TIME && blinkingSign == -1.0f) {
			blinkingSign = 1.0f;
			blinkingValue = 0.0f;
		}

		if(blinkingTime > Constants::Player::BLINK_TIME * 2 && blinkingSign == 1.0f) {
			blinkingTime = 0.0f;
			blinkingValue = 255.0f;
			blinkingSign = -1.0f;
		}

		blinkingValue += blinkingSign * 255 / Constants::Player::BLINK_TIME * dt;

		if(immortalTime <= 0) {
			immortal = false;

			blinkingValue = 255.0f;
		}

		left->getSpritePtr()->SetColor(sf::Color(255, 255, 255, blinkingValue));
		right->getSpritePtr()->SetColor(sf::Color(255, 255, 255, blinkingValue));
		top->getSpritePtr()->SetColor(sf::Color(255, 255, 255, blinkingValue));
		down->getSpritePtr()->SetColor(sf::Color(255, 255, 255, blinkingValue));
		sprite.SetColor(sf::Color(255, 255, 255, blinkingValue));

		immortalTime -= dt;
		blinkingTime += dt;
	}

	if(getNextHitbox(dt).getMinX() <= 0)
		stopLeft();

	else if(getNextHitbox(dt).getMinY() <= 100)
		stopTop();

	else if(getNextHitbox(dt).getMaxX() >= Window::instance()->getWidth() - 40)
		stopRight();

	else if(getNextHitbox(dt).getMaxY() >= Window::instance()->getHeight())
		stopDown();

	if(state != EntityState::stand)
		position = getNextPosition(dt);

	sprite.SetPosition(position);

	left->setPosition(position);
	right->setPosition(position);
	top->setPosition(position);
	down->setPosition(position);

	switch(state) {
	    case EntityState::stand:
	      break;

	    case EntityState::goLeft:
	    	left->process(dt);
	      break;

	    case EntityState::goRight:
	    	right->process(dt);
	      break;

	    case EntityState::goTop:
	    	top->process(dt);
	      break;

	    case EntityState::goDown:
	    	down->process(dt);
	      break;
	}
}

void Player::draw(float dt) {
	switch(state) {
	    case EntityState::stand:
	    	Window::instance()->getRW()->Draw(sprite);
	      break;

	    case EntityState::goLeft:
	    	left->draw();
	      break;

	    case EntityState::goRight:
	    	right->draw();
	      break;

	    case EntityState::goTop:
	    	top->draw();
	      break;

	    case EntityState::goDown:
	    	down->draw();
	      break;
	}

	Window::instance()->drawHitbox(getHitbox(), sf::Color::Red);
}

void Player::looseLife() {
	--healthAmount;
	immortal = true;
	immortalTime = Constants::Player::IMMORTAL_TIME;

	blinkingTime = 0.0f;
	blinkingValue = 255.0f;
	blinkingSign = -1.0f;
}

void Player::putBomb() {
	entitiesToCreate->push( new Bomb(position, this, entitiesToCreate));
}

void Player::going(float dt) {
	if(goingDone) return;

	if(distanceToGoQueue.front().x > 0) {
		if(!isGoing)
			goRight();

	} else if(distanceToGoQueue.front().x < 0) {
		if(!isGoing)
			goLeft();

	} if(distanceToGoQueue.front().y > 0) {
		if(!isGoing)
			goDown();

	} else if(distanceToGoQueue.front().y < 0) {
		if(!isGoing)
			goTop();
	}

	isGoing = true;

	switch(state) {
	    case EntityState::goLeft:
	    	distanceToGo += getXVelocity() * dt;
	      break;

	    case EntityState::goRight:
	    	distanceToGo -= getXVelocity() * dt;
	      break;

	    case EntityState::goTop:
	    	distanceToGo += getYVelocity() * dt;
	      break;

	    case EntityState::goDown:
	    	distanceToGo -= getYVelocity() * dt;
	      break;

	    default:

	      break;
	}

	if(distanceToGo < 0) {
		switch(state) {
		    case EntityState::goLeft:
		    	stopLeft();
		      break;

		    case EntityState::goRight:
		    	stopRight();
		      break;

		    case EntityState::goTop:
		    	stopTop();
		      break;

		    case EntityState::goDown:
		    	stopDown();
		      break;

		    default:

		      break;
		}

		isGoing = false;

		distanceToGoQueue.pop();

		if(!distanceToGoQueue.empty()) {
			if(distanceToGoQueue.front().x != 0.0f)
				distanceToGo = fabsf(distanceToGoQueue.front().x);
			else
				distanceToGo = fabsf(distanceToGoQueue.front().y);

		} else distanceToGo = 0.0f;
	}

	if(distanceToGo == 0.0f) {
		LOG("a");

		isGoing = false;
		goingDone = true;
		lockMovement = false;
		lockKey = false;

		putBomb();
	}
}

void Player::goingToCenter() {
	int x = position.x / 50;
	float toX = x * 50 + 12 - position.x;

	int y = position.y / 50;
	float toY = y * 50 + 35 - position.y;

	distanceToGoQueue.push(sf::Vector2f(0, toY));
	distanceToGoQueue.push(sf::Vector2f(toX, 0));

	distanceToGo = fabsf(distanceToGoQueue.front().y);

	goingDone = false;
	isGoing = false;
	lockMovement = true;
	lockKey = true;

   	stopMovement();
}

void Player::setBombAmount(int targetValue) {
	if (targetValue < 0)
		bombAmount = 0;
	else if (targetValue > Constants::Bomb::MAX_AMOUNT) {
		bombAmount = Constants::Bomb::MAX_AMOUNT;
	  return;
	} else
		bombAmount = targetValue;
}

void Player::setHealthAmount(int targetValue) {
	if (targetValue < 0)
		healthAmount = 0;
	else if (targetValue > Constants::Bomb::MAX_AMOUNT) {
		healthAmount = Constants::Bomb::MAX_AMOUNT;
	  return;
	} else
		healthAmount = targetValue;
}

