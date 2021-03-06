#include "Player.h"

#include "../../constants.h"

#include "Bomb.h"

Player::Player(int _id, sf::Vector2f _position) {
	info.id = _id;
	info.position = _position;

	maxBombAmount = Constants::Bomb::MAX_AMOUNT;
	bombAmount  = Constants::Bomb::START_AMOUNT;

	healthAmount = Constants::Player::HEALTH;
	maxHealthAmount = Constants::Player::MAX_HEALTH;

	explosionLength = Constants::Explosion::LENGTH;

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

	hitboxColor = sf::Color::Red;
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

	Entity *entity = nullptr;

	if(ptr->world[id].find(LayerType::LAYER_STONES) != ptr->world[id].end())
		entity = ptr->world[id][LayerType::LAYER_STONES];
	else if(ptr->world[id].find(LayerType::LAYER_BLOCKS) != ptr->world[id].end())
		entity = ptr->world[id][LayerType::LAYER_BLOCKS];
	else
		return; //Field has no blocks and stones

	Hitbox self = getHitbox();
	Hitbox block = entity->getHitbox();

	if(Hitbox::collide(self, block)) {
		sf::Vector2f offset(0, 0);

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
	if(bombAmount == 0) return;

	sf::Vector2i pPos = ptr->getNField(position);
	int id = pPos.y * ptr->mapDimensions.x + pPos.x;

	Bomb *bomb = new Bomb(ptr, bombAmount, explosionLength, id, position + animation_offset);

	if(ptr->world[id].find(LayerType::LAYER_BOMBS) == ptr->world[id].end())
		ptr->world[pPos.y * ptr->mapDimensions.x + pPos.x].insert(std::make_pair(LayerType::LAYER_BOMBS, bomb));
}

void Player::draw(float dt) {
	animation->process(dt);
	animation->draw();

	Window::instance()->drawHitbox(getHitbox(), hitboxColor);
}

// TODO: Usunac blad wysrodkowywania hitboxa => usunax hitboxOffset
Hitbox Player::getHitbox() const {
	// square 22*22 centered on player -- to be placed somewhere else.
	return Hitbox(position + sf::Vector2f(-11,-11) + hitboxOffset, position + sf::Vector2f(11,11) + hitboxOffset);
}
