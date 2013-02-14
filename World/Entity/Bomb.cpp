#include "Bomb.h"

Bomb::Bomb(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position) {
	ptr = _ptr;

	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("Bomb");
	sp = Sprite::instance()->getSpriteData("Bomb");

	sprite.SetPosition(info.position);

	lifeTime = 3;
	live = true;
	detonated = false;
}

Bomb::~Bomb() {
	LOG("Usunieta");
}

/**
 * pisane o 2 w nocy (jesli komus chce sie poprawic to prosze bardzo)
 *
 */
void Bomb::draw(float dt) {
	if(lifeTime > 0) {
		lifeTime -= dt;

		Window::instance()->getRW()->Draw(sprite);
		Window::instance()->drawHitbox(getHitbox(), sf::Color::Yellow);

	} else {
		/*if(live && !detonated) {
			destroyStone(ptr, info.position, 2);
			detonated = true;

		} else if(live && detonated) {

	/*		if(!animationArray.empty()) {
				for(int i=0; i<animationArray.size(); ++i) {
					if(!animationArray[i].isPlay()) {
						animationArray.erase(animationArray.begin()+i);
						i--;
					} else
						animationArray[i].process(dt);
				}

				LOG("2");
			} else {
				live = false;

				ptr->world[ptr->getNField(info.position).y * ptr->mapDimensions.x + ptr->getNField(info.position).x].erase(World::DisplayOrder::bomb);
			}
		}*/
	}
}

Hitbox Bomb::getHitbox() const {
   return Hitbox(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y));
}

void Bomb::destroyStone(World *ptr, sf::Vector2f position, int dis) {
	sf::Vector2i bPos = ptr->getNField(position);

	/* right, left, top, bottom */
	bool found[] = {false, false, false, false};
	int  id[] = {0, 0, 0, 0};

	for(int i=1; i<=dis; ++i) {
		if(bPos.x-i > -1 && bPos.y-i > -1 && bPos.x+i < ptr->mapDimensions.x && bPos.y < ptr->mapDimensions.y) {
			id[0] = bPos.y * ptr->mapDimensions.x + bPos.x+i;
			id[1] = bPos.y * ptr->mapDimensions.x + bPos.x-i;
			id[2] = (bPos.y-i) * ptr->mapDimensions.x + bPos.x;
			id[3] = (bPos.y+i) * ptr->mapDimensions.x + bPos.x;

			for(int j=0; j<4; ++j) {
				if(!found[j]) {
					if(ptr->world[ id[j] ].find(World::DisplayOrder::bomb) != ptr->world[ id[j] ].end()) {
						static_cast<Bomb*>(ptr->world[ id[j] ][World::DisplayOrder::bomb])->lifeTime = -1;

						found[j] = true;

					} else if(ptr->world[ id[j] ].find(World::DisplayOrder::block) != ptr->world[ id[j] ].end()) {
						if(ptr->world[ id[j] ][World::DisplayOrder::block]->sp.title == "Stone") { // TODO: nie za ciekawie (string)

							delete ptr->world[ id[j] ][World::DisplayOrder::block];
							ptr->world[ id[j] ].erase(World::DisplayOrder::block);

							found[j] = true;

						} else if(ptr->world[ id[j] ][World::DisplayOrder::block]->sp.title == "Bracket") // TODO: nie za ciekawie (string)
							found[j] = true;
					} else {
						sf::Sprite sprite2 = Sprite::instance()->getSprite("explosion");
						SpriteData spriteDate = Sprite::instance()->getSpriteData("explosion");

						sf::Vector2i pos = ptr->getPixelPosition(id[j]);

						std::clog << pos.x << ", " << pos.y << std::endl;

						sprite2.SetPosition(pos.x, pos.y);

						animationArray.push_back(Animation(sprite2, spriteDate, true, true));
						animationArray.back().play();
					}
				}
			}
		}
	}
	//ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x].erase(World::DisplayOrder::bomb);
}
