#include "Player.h"

#include "../Hitbox.h"

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

	animation = new Animation(sprite.at(0), spriteData.at(0));

	goDown = goUp = goLeft = goRight = false;
	lockChangeDirection = false;

	// See World::loadWorld()
	position = _position;

	/// Offset of animation sprite from
	animation_offset = sf::Vector2f(-12,10);

	animation->setPos(position+animation_offset);
}

void Player::update(float dt) {
	if(!goDown && !goRight && !goLeft && !goUp) {
		animation->stop();
	} else {
		animation->play();
		position += velocity * dt;
		animation->setPos(position+animation_offset);
	}
}

// Choose which tiles to check based on movement
void Player::detectTileCollisions(World *ptr) {
	sf::Vector2i currField = ptr->getNField(position);
	int width = ptr->mapDimensions.x;

	/* Fig.1: Tile checking pattern.
	 *
	 *   % % %   . . %   . . .   % . .
	 *   . ^ .   . > %   . v .   % < .
	 *   . . .   . . %   % % %   % . .
	 *
	 * */
	if(goDown) {
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x    ) );
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x + 1) );
	}
	if(goUp) {
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x    ) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x + 1) );
	}
	if(goRight){
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x + 1) );
		collideWithTile(ptr, (currField.y    ) * width + (currField.x + 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x + 1) );
	}
	if(goLeft) {
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y    ) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x - 1) );
	}
}

// Check for collision, correct position if necessary
// Colliding will stop the player and push them back.
void Player::collideWithTile(World *ptr, int id){
	if(ptr->world.find(id) == ptr->world.end()) return; //No such field on map
	if(ptr->world[id].find(World::DisplayOrder::block) == ptr->world[id].end()) return; //Field has no blocks

	Entity* entity = ptr->world[id][World::DisplayOrder::block];

	Hitbox self = getHitbox();
	Hitbox block = entity->getHitbox();

	if( Hitbox::collide(self, block) ) {
		sf::Vector2f offset(0,0);

		// calculate where to push the player
		if(goDown)  offset.y =  block.getMinY() - self.getMaxY() - 1; // Negative value -- push up and a little more
		if(goUp)    offset.y =  block.getMaxY() - self.getMinY() + 1; // Positive value -- push down
		if(goRight) offset.x =  block.getMinX() - self.getMaxX() - 1; // push left
		if(goLeft)  offset.x =  block.getMaxX() - self.getMinX() + 1; // push right

		// Correct position and update player
		position += offset;
		update(0); // instant correction, no velocity

		// TODO: Going towards a wall causes player's sprite to derp out -- find out why

		// Lock further movement
		if(goDown)  goDown  = lockChangeDirection = false;
		if(goUp)    goUp    = lockChangeDirection = false;
		if(goRight) goRight = lockChangeDirection = false;
		if(goLeft)  goLeft  = lockChangeDirection = false;
	}
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

	Window::instance()->drawHitbox(getHitbox(),sf::Color::Red);
}

// TODO: Usunac blad wysrodkowywania hitboxa => usunax hitboxOffset
Hitbox Player::getHitbox() const {
	// square 22*22 centered on player -- to be placed somewhere else.
	return Hitbox( position + sf::Vector2f(-11,-11) + hitboxOffset, position + sf::Vector2f(11,11) + hitboxOffset );
}
