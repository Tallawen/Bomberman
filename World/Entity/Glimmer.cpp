#include "Glimmer.h"

#include "../../constants.h"

Glimmer::Glimmer(World *_ptr, int _id, sf::Vector2f _position) {
	ptr = _ptr;

	info.id = _id;
	info.position = _position;

	sprite.push_back(Sprite::instance()->getSprite("Enemi_down"));
	sprite.push_back(Sprite::instance()->getSprite("Enemi_top"));
	sprite.push_back(Sprite::instance()->getSprite("Enemi_right"));
	sprite.push_back(Sprite::instance()->getSprite("Enemi_left"));

	spriteData.push_back(Sprite::instance()->getSpriteData("Enemi_down"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Enemi_top"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Enemi_right"));
	spriteData.push_back(Sprite::instance()->getSpriteData("Enemi_left"));

	animation = new Animation(sprite.at(0), spriteData.at(0));

	goDown = goUp = goLeft = goRight = false;

	// See World::loadWorld()
	position = _position;

	/// Offset of animation sprite from
	animation_offset = sf::Vector2f(-12,10);

	animation->setPos(position+animation_offset);

	hitboxColor = sf::Color::Red;

	movement(Direction::right);
}

void Glimmer::movement(Glimmer::Direction direction) {
	animation->setSprite(sprite.at( int(direction) ), spriteData.at( int(direction) ));
	animation->setPos(position + animation_offset);

	switch(direction) {
	    case Direction::down:
	    	goDown = true;
	    	velocity = sf::Vector2f(0, 50);

			hitboxOffset = sf::Vector2f(0, 0);
	      break;

	    case Direction::top:
	    	goUp = true;
	    	velocity = sf::Vector2f(0, -50);

			hitboxOffset = sf::Vector2f(0, 0);
	      break;

	    case Direction::right:
	    	goRight = true;
	    	velocity = sf::Vector2f(50, 0);

			hitboxOffset = sf::Vector2f(10, 0);
	      break;

	    case Direction::left:
	    	goLeft = true;
	    	velocity = sf::Vector2f(-50, 0);

			hitboxOffset = sf::Vector2f(0, 0);
	      break;
	}
}

void Glimmer::update(float dt) {
	if(!goDown && !goRight && !goLeft && !goUp) {
		animation->stop();
	} else {
		detectTileCollisions();

		animation->play();
		position += velocity * dt;
		animation->setPos(position+animation_offset);

		sf::Vector2i newId = ptr->getNField(position);
		if(newId.x != ptr->xByID(info.id) || newId.y != ptr->yByID(info.id)) {
			ptr->world[ptr->ID(newId.x, newId.y)][LayerType::LAYER_CHARACTERS] = ptr->world[info.id][LayerType::LAYER_CHARACTERS];

			ptr->world[info.id].erase(LayerType::LAYER_CHARACTERS);

			info.id = ptr->ID(newId.x, newId.y);
		}
	}
}

// Choose which tiles to check based on movement
void Glimmer::detectTileCollisions() {
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
void Glimmer::collideWithTile(World *ptr, int id){
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
		route(true);
	}
}

void Glimmer::route(bool current) {
	int k = sf::Randomizer::Random(0, 2);

	if(goDown) {
		goDown = false;
		if(k == 0)
			movement(Direction::left);

		if(k == 1)
					movement(Direction::top);

		if(k == 2)
					movement(Direction::right);

	} else if(goUp) {
		goUp = false;
		if(k == 0)
					movement(Direction::left);

				if(k == 1)
							movement(Direction::down);

				if(k == 2)
							movement(Direction::right);

	} else if(goRight) {
		goRight = false;
		if(k == 0)
					movement(Direction::left);

				if(k == 1)
							movement(Direction::top);

				if(k == 2)
							movement(Direction::down);

	} else if(goLeft) {
		goLeft = false;
		if(k == 0)
					movement(Direction::down);

				if(k == 1)
							movement(Direction::top);

				if(k == 2)
							movement(Direction::right);

	}
}

void Glimmer::draw(float dt) {
	animation->process(dt);
	animation->draw();

	Window::instance()->drawHitbox(getHitbox(), hitboxColor);
}

// TODO: Usunac blad wysrodkowywania hitboxa => usunax hitboxOffset
Hitbox Glimmer::getHitbox() const {
	// square 22*22 centered on player -- to be placed somewhere else.
	return Hitbox(position + sf::Vector2f(-11,-11) + hitboxOffset, position + sf::Vector2f(11,11) + hitboxOffset);
}
