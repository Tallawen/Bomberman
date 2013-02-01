#include "Player.h"

#include "../Aabb.h"

Player::Player(int _fieldId, int _priority, sf::Vector2f _position) {
	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite.push_back(Sprite::instance()->getSprite("Player_White_Down"));
	sprite.push_back(Sprite::instance()->getSprite("Player_White_Top"));
	sprite.push_back(Sprite::instance()->getSprite("Player_White_Right"));
	sprite.push_back(Sprite::instance()->getSprite("Player_White_Left"));

	spriteData.push_back(Sprite::instance()->getSpriteData("Player_White_Down"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Player_White_Top"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Player_White_Right"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Player_White_Left"));

	animation = new Animation(&sprite.at(0), spriteData.at(0));

	goDown = goTop = goLeft = goRight = false;
	lockChangeDirection = false;

	position = _position + sf::Vector2f(12, -10);
	sprite.at(0).SetPosition(position);
}

void Player::update(float dt) {
	if(!goDown && !goRight && !goLeft && !goTop)
		animation->stop();

	if(goDown) {
		animation->play();

		position += velocity * dt;
		animation->setPos(position);
	}

	if(goTop) {
		animation->play();

		position += velocity * dt;
		animation->setPos(position);
	}

	if(goLeft) {
		animation->play();

		position += velocity * dt;
		animation->setPos(position);

	}

	if(goRight) {
		animation->play();
			position += velocity * dt;
			animation->setPos(position);
	}
}

bool Player::isAnyFieldBelowMe(World *ptr, sf::Vector2i pos) {
	if(pos.x < 0 || pos.y+1 > ptr->mapDimensions.y) return true;
	if(ptr->world.find((pos.y+1) * ptr->mapDimensions.x + pos.x) == ptr->world.end()) return false;
	if(ptr->world[(pos.y+1) * ptr->mapDimensions.x + pos.x].find(0) == ptr->world[(pos.y+1) * ptr->mapDimensions.x + pos.x].end()) return false;

	Entity* entityPtr = ptr->world[(pos.y+1) * ptr->mapDimensions.x + pos.x][0];

	//sf::Vector2f startAabb = entityPtr->info.position;
	sf::Vector2f startAabb = entityPtr->info.position + sf::Vector2f(0, -18);
	sf::Vector2f stopAabb = entityPtr->info.position + sf::Vector2f(ptr->floorData.dimensions.x, -ptr->floorData.dimensions.y);

	Aabb tileAabb(startAabb, stopAabb);
	Aabb currentAabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y));

	Window::instance()->drawAabb(tileAabb, sf::Color::Blue);

  return currentAabb.collides(tileAabb);
}

bool Player::isAnyFieldAboveMe(World *ptr, sf::Vector2i pos) {
	if(pos.x < 0 || pos.y-1 < 0) return true;
	if(ptr->world.find((pos.y-1) * ptr->mapDimensions.x + pos.x) == ptr->world.end()) return false;
	if(ptr->world[(pos.y-1) * ptr->mapDimensions.x + pos.x].find(0) == ptr->world[(pos.y-1) * ptr->mapDimensions.x + pos.x].end()) return false;

	Entity* entityPtr = ptr->world[(pos.y-1) * ptr->mapDimensions.x + pos.x][0];

	sf::Vector2f startAabb = entityPtr->info.position + sf::Vector2f(0, -18);
	sf::Vector2f stopAabb = entityPtr->info.position + sf::Vector2f(ptr->floorData.dimensions.x, -ptr->floorData.dimensions.y);

	Aabb tileAabb(startAabb, stopAabb);
	Aabb currentAabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y));

	Window::instance()->drawAabb(tileAabb, sf::Color::Blue);

  return currentAabb.collides(tileAabb);
}

bool Player::isAnyFieldOnRight(World *ptr, sf::Vector2i pos) {
	if(pos.x+1 > ptr->mapDimensions.x || pos.y < 0) return true;
	if(ptr->world.find(pos.y * ptr->mapDimensions.x + (pos.x+1)) == ptr->world.end()) return false;
	if(ptr->world[pos.y * ptr->mapDimensions.x + (pos.x+1)].find(0) == ptr->world[pos.y * ptr->mapDimensions.x + (pos.x+1)].end()) return false;

	Entity* entityPtr = ptr->world[pos.y * ptr->mapDimensions.x + (pos.x+1)][0];

	//sf::Vector2f startAabb = entityPtr->info.position;
	sf::Vector2f startAabb = entityPtr->info.position + sf::Vector2f(0, -18);
	sf::Vector2f stopAabb = entityPtr->info.position + sf::Vector2f(entityPtr->sp.dimensions.x, -entityPtr->sp.dimensions.y);

	Aabb tileAabb(startAabb, stopAabb);
	Aabb currentAabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y));

	Window::instance()->drawAabb(tileAabb, sf::Color::Blue);

  return currentAabb.collides(tileAabb);
}

bool Player::isAnyFieldOnLeft(World *ptr, sf::Vector2i pos) {
	if(pos.x-1 < 0 || pos.y < 0) return true;
	if(ptr->world.find(pos.y * ptr->mapDimensions.x + (pos.x-1)) == ptr->world.end()) return false;
	if(ptr->world[pos.y * ptr->mapDimensions.x + (pos.x-1)].find(0) == ptr->world[pos.y * ptr->mapDimensions.x + (pos.x-1)].end()) return false;

	Entity* entityPtr = ptr->world[pos.y * ptr->mapDimensions.x + (pos.x-1)][0];

	//sf::Vector2f startAabb = entityPtr->info.position;
	sf::Vector2f startAabb = entityPtr->info.position + sf::Vector2f(0, -18);
	sf::Vector2f stopAabb = entityPtr->info.position + sf::Vector2f(entityPtr->sp.dimensions.x, -entityPtr->sp.dimensions.y);

	Aabb tileAabb(startAabb, stopAabb);
	Aabb currentAabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y));

	Window::instance()->drawAabb(tileAabb, sf::Color::Blue);

  return currentAabb.collides(tileAabb);
}

void Player::checkCollisionsWorld(World *ptr) {
	//sf::Shape s = sf::Shape::Rectangle(position, position + sf::Vector2f(10, -10), sf::Color::Cyan);
	//Window::instance()->getRW()->Draw(s);

	sf::Vector2i pPosLeftUpperCorner = ptr->getNField(position);
	sf::Vector2i pPosRightUpperCorner = ptr->getNField(position.x + 30, position.y);
	sf::Vector2i pPosLeftLowerCorner = ptr->getNField(position.x, position.y - 40);
	sf::Vector2i pPosRightLowerCorner = ptr->getNField(position.x + 30, position.y - 40);

	if(isAnyFieldBelowMe(ptr, pPosLeftUpperCorner) || isAnyFieldBelowMe(ptr, pPosRightUpperCorner) || isAnyFieldBelowMe(ptr, pPosLeftLowerCorner) || isAnyFieldBelowMe(ptr, pPosRightLowerCorner))
		if(goDown) goDown = lockChangeDirection = false;

	if(isAnyFieldAboveMe(ptr, pPosLeftUpperCorner) || isAnyFieldAboveMe(ptr, pPosRightUpperCorner) || isAnyFieldAboveMe(ptr, pPosLeftLowerCorner) || isAnyFieldAboveMe(ptr, pPosRightLowerCorner))
		if(goTop) goTop = lockChangeDirection = false;

	if(isAnyFieldOnRight(ptr, pPosLeftUpperCorner) || isAnyFieldOnRight(ptr, pPosRightUpperCorner) || isAnyFieldOnRight(ptr, pPosLeftLowerCorner) || isAnyFieldOnRight(ptr, pPosRightLowerCorner))
		if(goRight) goRight = lockChangeDirection = false;

	if(isAnyFieldOnLeft(ptr, pPosLeftUpperCorner) || isAnyFieldOnLeft(ptr, pPosRightUpperCorner) || isAnyFieldOnLeft(ptr, pPosLeftLowerCorner) || isAnyFieldOnLeft(ptr, pPosRightLowerCorner))
		if(goLeft) goLeft = lockChangeDirection = false;
}

void Player::setBomb(World *ptr) {
	sf::Vector2i pPos = ptr->getNField(position);

	Bomb *newBomb = new Bomb(ptr, pPos.y * ptr->mapDimensions.x + pPos.x, 2, position);
	if(ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].find(2) == ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].end()) {
		ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].insert(std::make_pair(2, newBomb));
		ptr->bomb.push_back(newBomb);
	}
}

void Player::draw(float dt) {
	animation->process(dt);
	animation->draw();
	Window::instance()->drawAabb(Aabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y)), sf::Color::Red);
}
