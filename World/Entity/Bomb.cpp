#include "Bomb.h"

Bomb::Bomb(World *_ptr, int _fieldId, int _priority, sf::Vector2f _position) {
	ptr = _ptr;

	info.fieldId = _fieldId;
	info.priority = _priority;
	info.position = _position;

	sprite = Sprite::instance()->getSprite("Bomb");
	sp = Sprite::instance()->getSpriteData("Bomb");
	sprite.SetPosition(info.position);

	animation = new Animation(&sprite, sp, true);

	animation->rotate(Animation::RotationDirection::left, 360);
	lifeTime = 3;
	live = true;
}

Bomb::~Bomb() {
	LOG("Usunieta");
}
void Bomb::draw(float dt) {
	//Window::instance()->getRW()->Draw(sprite);
	animation->process(dt);

	lifeTime -= dt;

	if(lifeTime < 0) {
		live = false;
		destroyStone(ptr, info.position, 2);
	}

	Window::instance()->drawAabb(Aabb(info.position, info.position + sf::Vector2f(sprite.GetSize().x, -sprite.GetSize().y)), sf::Color::Green);
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
					}
				}
			}
		}
	}

	ptr->world[bPos.y * ptr->mapDimensions.x + bPos.x].erase(World::DisplayOrder::bomb);
}
