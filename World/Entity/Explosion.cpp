#include "Explosion.h"
//
//Explosion::Explosion(World *_ptr, int _fieldId, float _delay, int _priority, sf::Vector2f _position, int _explosionLength, Directions _directions) {
//	ptr = _ptr;
//
//	info.fieldId = _fieldId;
//	info.priority = _priority;
//	info.position = _position;
//
//	explosionLength = _explosionLength;
//	directions = _directions;
//
//	delay = _delay;
//
//	firstCheck = false;
//
//	id[0] = info.fieldId + 1;
//	id[1] = info.fieldId - 1;
//	id[2] = info.fieldId + ptr->mapDimensions.x;
//	id[3] = info.fieldId - ptr->mapDimensions.x;
//
//	position[0] = info.position;  position[0].x += ptr->floorData.dimensions.x;
//	position[1] = info.position;  position[1].x -= ptr->floorData.dimensions.x;
//	position[2] = info.position;  position[2].y += ptr->floorData.dimensions.y;
//	position[3] = info.position;  position[3].y -= ptr->floorData.dimensions.y;
//
//	sp = Sprite::instance()->getSpriteData("Explosion");
//	animation = new Animation(Sprite::instance()->getSprite("Explosion"), sp);
//
//	animation->setAutoStop();
//	animation->setAutoDraw(true);
//	animation->setPos(info.position);
//	animation->setDelay(delay);
//	animation->play();
//
//	LOG("Create explosion");
//}
//
//Explosion::~Explosion() {
//	LOG("Delete explosion");
//}
//
//void Explosion::draw(float dt) {
//	if(animation == nullptr) return;
//
//	animation->process(dt);
//	Window::instance()->drawHitbox(getHitbox(),sf::Color::Green);
//}
//
//void Explosion::update(float dt) {
//	if(animation == nullptr) return;
//
//	Explosion *newExplosion;
//
//	if(!firstCheck) {
//		if(explosionLength > 0) {
//
//			switch(directions) {
//			    case Directions::allSite: // -1
//			    	for(int i = 0; i < 4; ++i) {
//			    		if(checkTile(ptr, id[i], DisplayOrder::block, stone))
//			    			newExplosion = new Explosion(ptr, id[i], delay + 0.1f, 0, position[i], explosionLength - 1, Directions::none);
//
//			    		else
//			    			newExplosion = new Explosion(ptr, id[i], delay + 0.1f, 0, position[i], explosionLength - 1, Directions(i));
//
//			    		ptr->world[ id[i] ].insert( std::make_pair(DisplayOrder::explosion, newExplosion) );
//			    	}
//			       break;
//
//			    case Directions::right: // 0
//			    	if(checkTile(ptr, id[0], DisplayOrder::block, stone))
//			    		newExplosion = new Explosion(ptr, id[0], delay + 0.1f, 0, position[0], explosionLength - 1, Directions::none);
//
//			    /*	else if(collideWithExplosion(ptr, id[0]))
//			    		newExplosion = new Explosion(ptr, id[0], delay + 0.1f, 0, position[0], explosionLength - 1, Directions::none);
//*/
//			    	else
//			    		newExplosion = new Explosion(ptr, id[0], delay + 0.1f, 0, position[0], explosionLength - 1, Directions::right);
//
//			    	ptr->world[ id[0] ].insert( std::make_pair(DisplayOrder::explosion, newExplosion) );
//			       break;
//
//			    case Directions::left: // 1
//			    	if(checkTile(ptr, id[1], DisplayOrder::block, stone))
//			    		newExplosion = new Explosion(ptr, id[1], delay + 0.1f, 0, position[1], explosionLength - 1, Directions::none);
//
//			    /*	else if(collideWithExplosion(ptr, id[1]))
//			    		newExplosion = new Explosion(ptr, id[1], delay + 0.1f, 0, position[1], explosionLength - 1, Directions::none);
//*/
//			    	else
//			    		newExplosion = new Explosion(ptr, id[1], delay + 0.1f, 0, position[1], explosionLength - 1, Directions::left);
//
//			    	ptr->world[ id[1] ].insert( std::make_pair(DisplayOrder::explosion, newExplosion) );
//			       break;
//
//			    case Directions::top: // 2
//			    	if(checkTile(ptr, id[2], DisplayOrder::block, stone))
//			    		newExplosion = new Explosion(ptr, id[2], delay + 0.1f, 0, position[2], explosionLength - 1, Directions::none);
//
//			    	/*else if(collideWithExplosion(ptr, id[2]))
//			    		newExplosion = new Explosion(ptr, id[0], delay + 0.1f, 0, position[2], explosionLength - 1, Directions::none);
//*/
//			    	else
//			    		newExplosion = new Explosion(ptr, id[2], delay + 0.1f, 0, position[2], explosionLength - 1, Directions::top);
//
//			    	ptr->world[ id[2] ].insert( std::make_pair(DisplayOrder::explosion, newExplosion) );
//			       break;
//
//			    case Directions::down: // 3
//			    	if(checkTile(ptr, id[3], DisplayOrder::block, stone))
//			    		newExplosion = new Explosion(ptr, id[3], delay + 0.1f, 0, position[3], explosionLength - 1, Directions::none);
//
//			    /*	else if(collideWithExplosion(ptr, id[3]))
//			    		newExplosion = new Explosion(ptr, id[3], delay + 0.1f, 0, position[3], explosionLength - 1, Directions::none);
//*/
//			    	else
//			    		newExplosion = new Explosion(ptr, id[3], delay + 0.1f, 0, position[3], explosionLength - 1, Directions::left);
//
//			    	ptr->world[ id[3] ].insert( std::make_pair(DisplayOrder::explosion, newExplosion) );
//			       break;
//			}
//
//		}
//
//		firstCheck = true;
//	}
//
//	if(!animation->isPlay())
//		setRemove();
//}
//
//void Explosion::setDelay(float delay) {
//	if(animation != nullptr)
//		animation->setDelay(delay);
//}
//
//bool Explosion::checkTile(World *ptr, int id, DisplayOrder displayOrder,  bool (*ptrFun)(World*, int) ) {
//	if(ptr->world.find(id) == ptr->world.end()) return false; //No such field on map
//	if(ptr->world[id].find(displayOrder) == ptr->world[id].end()) return false; //Field has no displayOrder
//
//	return (ptrFun)(ptr, id);
//
//  return false;
//}
//
//bool Explosion::stone(World *ptr, int id) {
//	Entity* entity = ptr->world[id][DisplayOrder::block];
//
//	if(!entity->remove) {
//		entity->remove = true;
//	  return true;
//	}
//
//  return false;
//}
///*
//bool Explosion::bomb(World *ptr, int id) {
//	if(ptr->world.find(id) == ptr->world.end()) return false; //No such field on map
//	if(ptr->world[id].find(DisplayOrder::bomb) == ptr->world[id].end()) return false; //Field has no bomb
//
//	Entity* entity = ptr->world[id][DisplayOrder::bomb];
//
//	Hitbox self = getHitbox();
//	Hitbox bomb = entity->getHitbox();
//
//	if( Hitbox::collide(self, bomb) ) {
//		if(!entity->remove)
//			static_cast<Bomb*> (entity)->live = false;
//
//	  return true;
//	}
//  return false;
//}
//*/
//void Explosion::setRemove() {
//	if(animation == nullptr) return;
//
//	remove = true;
//
//	delete animation;
//	animation = nullptr;
//}
//
//
//Hitbox Explosion::getHitbox() const {
//    return Hitbox( info.position + sf::Vector2f(10, -10), info.position + sf::Vector2f(sp.dimensions.x, -sp.dimensions.y) + sf::Vector2f(-10, 10));
//}
//
