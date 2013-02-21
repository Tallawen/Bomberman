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
	//lockMoving = true;

	// See World::loadWorld()
	position = _position;

	/// Offset of animation sprite from
	animation_offset = sf::Vector2f(-12,10);

	animation->setPos(position);

	hitboxColor = sf::Color::Red;
}

void Player::update(float dt) {
	if(!goDown && !goRight && !goLeft && !goUp) {
		animation->stop();
	} else {
		animation->play();
		position += velocity * dt;
		animation->setPos(position);

	//	goTo(velocity * dt);

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

	//if(goDown) {
	//	collideWithTile(ptr, (currField.y + 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x    ) );
		//collideWithTile(ptr, (currField.y + 1) * width + (currField.x + 1) );
	//}
	//if(goUp) {
		//collideWithTile(ptr, (currField.y - 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x    ) );
		//collideWithTile(ptr, (currField.y - 1) * width + (currField.x + 1) );
	//}
	//if(goRight){
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x + 1) );
		collideWithTile(ptr, (currField.y    ) * width + (currField.x + 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x + 1) );
	//}
	//if(goLeft) {
		collideWithTile(ptr, (currField.y + 1) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y    ) * width + (currField.x - 1) );
		collideWithTile(ptr, (currField.y - 1) * width + (currField.x - 1) );
	//b}
}

// Check for collision, correct position if necessary
// Colliding will stop the player and push them back.
void Player::collideWithTile(World *ptr, int id){
	if(ptr->world.find(id) == ptr->world.end()) return; //No such field on map

	Entity *entity = nullptr;
	LayerType lt;

	if(ptr->world[id].find(LayerType::LAYER_STONES) != ptr->world[id].end()) {
		entity = ptr->world[id][LayerType::LAYER_STONES];
		lt = LayerType::LAYER_STONES;

	} else if(ptr->world[id].find(LayerType::LAYER_BLOCKS) != ptr->world[id].end()) {
		entity = ptr->world[id][LayerType::LAYER_BLOCKS];
		lt = LayerType::LAYER_BLOCKS;

	} else if(ptr->world[id].find(LayerType::LAYER_OPPONENTS) != ptr->world[id].end()) {
		entity = ptr->world[id][LayerType::LAYER_OPPONENTS];
		lt = LayerType::LAYER_OPPONENTS;

	} else
		return; //Field has no blocks and stones

	Hitbox self = getHitbox();
	Hitbox block = entity->getHitbox();

	if(Hitbox::collide(self, block)) {
		if(lt == LayerType::LAYER_OPPONENTS) {
			entity->remove = true;

		}

		sf::Vector2f offset(0, 0);

		// calculate where to push the player
		if(goDown || (!goDown && lastMove == Dire::down)) {
			offset.y =  block.getMinY() - self.getMaxY() - 4.0f; // Negative value -- push up and a little more
			LOG("OVER");
			lastMove = Dire::none;
		}
		if(goUp || (!goUp && lastMove == Dire::top)) {
			offset.y =  block.getMaxY() - self.getMinY() + 4.0f; // Positive value -- push down
			LOG("UPPER");
		}
		if(goLeft || (!goLeft && lastMove == Dire::left)) {
			offset.x =  block.getMaxX() - self.getMinX() + 4.0f; // push right
			LOG("RIGHT");
		}
		if(goRight || (!goRight && lastMove == Dire::right)) {
			offset.x =  block.getMinX() - self.getMaxX() - 4.0f; // push left

			LOG("LEFT");
		}

		// Correct position and update player
		position += offset;
		animation->setPos(position);
		//update(1); // instant correction, no velocity

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

	sf::Vector2i tileCoord = ptr->getNField(position);
	int id = ptr->ID(tileCoord.x, tileCoord.y);

	sf::Vector2f position = ptr->getPixelPosition(id);
	position.x += ptr->floorData.dimensions.x / 2;
	position.y -= ptr->floorData.dimensions.y / 2;

	Bomb *bomb = new Bomb(ptr, bombAmount, explosionLength, id, position);

	if(ptr->world[id].find(LayerType::LAYER_BOMBS) == ptr->world[id].end())
		ptr->world[id].insert(std::make_pair(LayerType::LAYER_BOMBS, bomb));
}

void Player::draw(float dt) {
	animation->process(dt);
	animation->draw();

	std::ostringstream ss;
				ss << info.id;

		sf::String id(ss.str());
		id.SetPosition(position);
		//sf::Shape shape = sf::Shape::Rectangle(position.x, position.y, position.x + 1, position.y + 1, sf::Color::White);
		Window::instance()->getRW()->Draw(id);


	Window::instance()->drawHitbox(getHitbox(), hitboxColor);
}
/*
void Player::goTo(sf::Vector2f offset) {
	if(!lockMoving) return;

	if(distanceToGo.x != 0) {
		if(distanceToGo.x > 0 && !goRight)
			right();
		else if(distanceToGo.x > 0 && goRight) {
			distanceToGo += offset;

			if(distanceToGo.x <= 0)
				distanceToGo.x = 0;

		} else if(distanceToGo.x < 0 && !goLeft)
			left();
		else if(distanceToGo.x < 0 && goLeft) {
			distanceToGo += offset;

			if(distanceToGo.x >= 0)
				distanceToGo.x = 0;
		}

	} else if(distanceToGo.y != 0) {
		if(distanceToGo.y > 0 && !goDown)
			down();
		else if(distanceToGo.y > 0 && goDown) {
			distanceToGo += offset;

			if(distanceToGo.y <= 0)
				distanceToGo.y = 0;

		} else if(distanceToGo.y < 0 && !goUp)
			top();
		else if(distanceToGo.y < 0 && goUp) {
			distanceToGo += offset;

			if(distanceToGo.y >= 0)
				distanceToGo.y = 0;
		}
	}

	if(distanceToGo.x == 0 && distanceToGo.y == 0)
		m
}
*/
// TODO: Usunac blad wysrodkowywania hitboxa => usunax hitboxOffset
Hitbox Player::getHitbox() const {
	// square 22*22 centered on player -- to be placed somewhere else.
	return Hitbox(position + sf::Vector2f(-11,-11) + hitboxOffset, position + sf::Vector2f(11,11) + hitboxOffset);
}
