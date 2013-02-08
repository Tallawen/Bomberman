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

bool Player::isAnyField(World *ptr, sf::Vector2i pos, Aabb::Position pos2, sf::Color color) {
	int id;
	switch(pos2) {
	    case Aabb::Position::above:
	    	if(pos.x < 0 || pos.y-1 < 0) return true;
	    	id = (pos.y-1) * ptr->mapDimensions.x + pos.x;
	      break;

	    case Aabb::Position::below:
	    	if(pos.x < 0 || pos.y+1 > ptr->mapDimensions.y) return true;
	    	id = (pos.y+1) * ptr->mapDimensions.x + pos.x;
	      break;

	    case Aabb::Position::left:
	    	if(pos.x-1 < 0 || pos.y < 0) return true;
	    	id = pos.y * ptr->mapDimensions.x + (pos.x-1);
	      break;

	    case Aabb::Position::right:
	    	if(pos.x+1 > ptr->mapDimensions.x || pos.y < 0) return true;
	    	id = pos.y * ptr->mapDimensions.x + (pos.x+1);
	      break;
	}

	if(ptr->world.find(id) == ptr->world.end()) return false;
	if(ptr->world[id].find(World::DisplayOrder::block) == ptr->world[id].end()) return false;

	Entity* entityPtr = ptr->world[id][World::DisplayOrder::block];

	sf::Vector2f startAabb = entityPtr->info.position + sf::Vector2f(0, -18);
	sf::Vector2f stopAabb = entityPtr->info.position + sf::Vector2f(ptr->floorData.dimensions.x, -ptr->floorData.dimensions.y);

	Aabb tileAabb(startAabb, stopAabb);
	Aabb currentAabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y));

	Window::instance()->drawAabb(tileAabb, color);

  return currentAabb.collides(tileAabb);
}


void Player::checkCollisionsWorld(World *ptr) {
	sf::Vector2i pPosLeftUpperCorner = ptr->getNField(position);
	sf::Vector2i pPosRightUpperCorner = ptr->getNField(position.x + 30, position.y);
	sf::Vector2i pPosLeftLowerCorner = ptr->getNField(position.x, position.y - 40);
	sf::Vector2i pPosRightLowerCorner = ptr->getNField(position.x + 30, position.y - 40);

	if(isAnyField(ptr, pPosLeftLowerCorner, Aabb::Position::below) || isAnyField(ptr, pPosRightLowerCorner, Aabb::Position::below))
		if(goDown) goDown = lockChangeDirection = false;

	if(isAnyField(ptr, pPosLeftUpperCorner, Aabb::Position::above) || isAnyField(ptr, pPosRightUpperCorner, Aabb::Position::above))
		if(goTop) goTop = lockChangeDirection = false;

	if(isAnyField(ptr, pPosRightUpperCorner, Aabb::Position::right, sf::Color::Cyan) || isAnyField(ptr, pPosRightLowerCorner, Aabb::Position::right, sf::Color::Cyan))
		if(goRight) goRight = lockChangeDirection = false;

	if(isAnyField(ptr, pPosLeftUpperCorner, Aabb::Position::left, sf::Color::Cyan) || isAnyField(ptr, pPosLeftLowerCorner, Aabb::Position::left, sf::Color::Cyan))
		if(goLeft) goLeft = lockChangeDirection = false;
}

void Player::setBomb(World *ptr) {
	sf::Vector2i pPos = ptr->getNField(position);

	Bomb *newBomb = new Bomb(ptr, pPos.y * ptr->mapDimensions.x + pPos.x, 2, position);

	if(ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].find(World::DisplayOrder::bomb) == ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].end()) {

		ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].insert(std::make_pair(World::DisplayOrder::bomb, newBomb));
		ptr->bombs.push_back(newBomb);
	}
}

void Player::draw(float dt) {
	animation->process(dt);
	animation->draw();

	Window::instance()->drawAabb(Aabb(animation->getPos(), animation->getPos() + sf::Vector2f(animation->getSpriteInfo().dimensions.x, -animation->getSpriteInfo().dimensions.y)), sf::Color::Red);
}
