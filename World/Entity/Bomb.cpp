#include "Bomb.h"

Bomb::Bomb(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position) {
	ptr = _ptr;

	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("Bomb");
	sp = Sprite::instance()->getSpriteData("Bomb");
	sprite.SetPosition(info.position);

	lifeTime = 2;
	live = true;
}

void Bomb::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);

	lifeTime -= dt;

	if(lifeTime < 0) {
		live = false;
		destroyStone(ptr, info.position, 2);
	}
	Window::instance()->drawAabb(Aabb(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y)), sf::Color::Green);
}

void Bomb::destroyStone(World *ptr, sf::Vector2f position, int dis) {
	sf::Vector2i bPos = ptr->getNField(position);

	bool findRight = false;
	bool findLeft  = false;
	bool findTop   = false;
	bool findBottom  = false;

	for(int i=1; i<=dis; ++i) {
		if(bPos.x-i > -1 && bPos.y-i > -1 && bPos.x+i < ptr->mapDimensions.x && bPos.y < ptr->mapDimensions.y) {
			if(!findRight) {
				FOREACH(ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x+i], it) {
					if(it->second->sp.title == "Bomb")
						static_cast<Bomb*>(it->second)->lifeTime = -1;

					if(it->second->sp.title == "Stone") {
						delete it->second;
						ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x+i].erase(it);

						findRight = true;
					  break;
					}

					if(it->second->sp.title != "Stone") {
						findRight = true;
					  break;
					}
				}
			}

			if(!findLeft) {
				FOREACH(ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x-i], it) {
					if(it->second->sp.title == "Bomb")
						static_cast<Bomb*>(it->second)->lifeTime = -1;

					if(it->second->sp.title == "Stone") {
						delete it->second;
						ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x-i].erase(it);

						findLeft = true;
					  break;
					}

					if(it->second->sp.title != "Stone") {
						findLeft = true;
					  break;
					}
				}
			}

			if(!findTop) {
				FOREACH(ptr->world[(bPos.y-i) * ptr->mapDimensions.x + bPos.x], it) {
					if(it->second->sp.title == "Bomb")
						static_cast<Bomb*>(it->second)->lifeTime = -1;

					if(it->second->sp.title == "Stone") {
						delete it->second;
						ptr->world[(bPos.y-i) * ptr->mapDimensions.x + bPos.x].erase(it);

						findTop = true;
					  break;
					}

					if(it->second->sp.title != "Stone") {
						findTop = true;
					  break;
					}
				}
			}

			if(!findBottom) {
				FOREACH(ptr->world[(bPos.y+i) * ptr->mapDimensions.x + bPos.x], it) {
					if(it->second->sp.title == "Bomb")
						static_cast<Bomb*>(it->second)->lifeTime = -1;

					if(it->second->sp.title == "Stone") {
						delete it->second;
						ptr->world[(bPos.y+i) * ptr->mapDimensions.x + bPos.x].erase(it);

						findBottom = true;
					  break;
					}

					if(it->second->sp.title != "Stone") {
						findBottom = true;
					  break;
					}
				}
			}
		}
	}

	FOREACH(ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x], bombIt) {
		if(bombIt->second->sp.title == "Bomb" && bombIt->second == this)
			ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x].erase(bombIt);
	}
}
