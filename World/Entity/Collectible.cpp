#include "Collectible.h"

Collectible::Collectible(sf::Vector2f _position, std::queue<Entity*> *_entitiesToCreate) : Entity(_position.x, _position.y, 0, 0, _entitiesToCreate) {


}

void Collectible::draw(float dt) {
	Window::instance()->getRW()->Draw(sprite);

	Window::instance()->drawHitbox(getHitbox(), sf::Color::Magenta);
}
