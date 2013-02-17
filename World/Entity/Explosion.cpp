#include "Explosion.h"

#include "../../constants.h"

#include "Bomb.h"

Explosion::Explosion(World *_ptr, int _fieldId, float _delay, int _priority, sf::Vector2f _position, int _explosionLength, Directions _directions) {
	ptr = _ptr;

	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	explosionLength = _explosionLength;
	directions = _directions;

	delay = _delay;
	first = false;

	id[0] = info.fieldId + 1;
	id[1] = info.fieldId - 1;
	id[2] = info.fieldId + ptr->mapDimensions.x;
	id[3] = info.fieldId - ptr->mapDimensions.x;

	position[0] = info.position;  position[0].x += ptr->floorData.dimensions.x;
	position[1] = info.position;  position[1].x -= ptr->floorData.dimensions.x;
	position[2] = info.position;  position[2].y += ptr->floorData.dimensions.y;
	position[3] = info.position;  position[3].y -= ptr->floorData.dimensions.y;

	sp = Sprite::instance()->getSpriteData("Explosion");
	animation = new Animation(Sprite::instance()->getSprite("Explosion"), sp);

	animation->setAutoStop();
	animation->setAutoDraw(true);
	animation->setPos(info.position);
	animation->setDelay(delay);
	animation->play();

	//LOG("Create explosion ");
	std::cerr << "Create explosion: " << explosionLength << std::endl;
}

Explosion::~Explosion() {
	LOG("Delete explosion");
}

void Explosion::draw(float dt) {
	if(animation == nullptr) return;

	animation->process(dt);
	Window::instance()->drawHitbox(getHitbox(),sf::Color::Green);
}

void Explosion::update(float dt) {
	if(animation == nullptr) return;

	if(!first && !animation->isDelay()) {
		if(explosionLength > 0) {

			switch(directions) {
			    case Directions::none: //

			      break;

			    case Directions::allSite: // -1
			    	for(int i = 0; i < 4; ++i)
			    		create(i);

			      break;

			    case Directions::right: // 0
			    	create(0);
			      break;

			    case Directions::left: // 1
			    	create(1);
			      break;

			    case Directions::top: // 2
			    	create(2);
			      break;

			    case Directions::down: // 3
			    	create(3);
			      break;
			}

		}

		first = true;
	}

	if(!animation->isPlay())
		setRemove();
}

void Explosion::setDelay(float delay) {
	if(animation != nullptr)
		animation->setDelay(delay);
}

void Explosion::create(int _id) {
	Explosion *newExplosion = nullptr;

	checkTile(ptr, id[_id], LayerType::LAYER_EXPLOSIONS, &Explosion::explosion);

	if(checkTile(ptr, id[_id], LayerType::LAYER_STONES, &Explosion::stone) || checkTile(ptr, id[_id], LayerType::LAYER_BOMBS, &Explosion::bomb))
		newExplosion = new Explosion(ptr, id[_id], delay + Constants::Explosion::DELAY, 0, position[_id], explosionLength - 1, Directions::none);

	else if(!checkTile(ptr, id[_id], LayerType::LAYER_BLOCKS, &Explosion::block))
		newExplosion = new Explosion(ptr, id[_id], delay + Constants::Explosion::DELAY, 0, position[_id], explosionLength - 1, Directions(_id));

	if(newExplosion != nullptr)
		ptr->world[ id[_id] ].insert( std::make_pair(LayerType::LAYER_EXPLOSIONS, newExplosion) );
}

bool Explosion::checkTile(World *ptr, int id, LayerType layer, bool(Explosion::*ptrFun)(World*, int)) {
	if(ptr->world.find(id) == ptr->world.end()) return false; /// Brak danego kafla
	if(ptr->world[id].find(layer) == ptr->world[id].end()) return false; /// Kafel nie posiada danej warstwy

  return (this->*ptrFun)(ptr, id);
}

bool Explosion::stone(World *ptr, int id) {
	Entity* entity = ptr->world[id][LayerType::LAYER_STONES];

	entity->remove = true;

  return true;
}

bool Explosion::block(World *ptr, int id) {
  return true;
}

bool Explosion::explosion(World *ptr, int id) {
	Entity* entity = ptr->world[id][LayerType::LAYER_EXPLOSIONS];

	ptr->world[id].erase(LayerType::LAYER_EXPLOSIONS);

	static_cast<Explosion*>(entity)->setRemove();
	delete entity;

  return false;
}

bool Explosion::bomb(World *ptr, int id) {
	Entity* entity = ptr->world[id][LayerType::LAYER_BOMBS];

	static_cast<Bomb*> (entity)->live = false;

  return true;
}

void Explosion::setRemove() {
	if(animation == nullptr) return;

	remove = true;

	delete animation;
	animation = nullptr;
}

Hitbox Explosion::getHitbox() const {
    return Hitbox( info.position + sf::Vector2f(10, -10), info.position + sf::Vector2f(sp.dimensions.x, -sp.dimensions.y) + sf::Vector2f(-10, 10));
}
