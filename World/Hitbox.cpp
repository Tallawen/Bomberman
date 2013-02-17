#include "Hitbox.h"

/***********************************************************************************
 Hitbox :: methods
 *********************/

Hitbox::Hitbox(sf::Vector2f v1, sf::Vector2f v2) {
	min=sf::Vector2f();
	max=sf::Vector2f();
	// Corners can be added in any order.
	// Sort them:
    min.x = v1.x < v2.x ? v1.x : v2.x;
    min.y = v1.y < v2.y ? v1.y : v2.y;

    max.x = v1.x > v2.x ? v1.x : v2.x;
    max.y = v1.y > v2.y ? v1.y : v2.y;
}

bool Hitbox::isNone() const {
	return min.x == max.x || min.y == max.y;
}

bool Hitbox::collide(const Hitbox &a, const Hitbox &b) { //static method
//	// Debug
//	std::cerr<<"Collide:\n";
//    std::printf("\ta: [%3.2f %3.2f] [%3.2f %3.2f]\n", a.min.x, a.min.y, a.max.x, a.max.y);
//    std::printf("\tb: [%3.2f %3.2f] [%3.2f %3.2f]\n", b.min.x, b.min.y, b.max.x, b.max.y);

	if (a.isNone() || b.isNone())
		return false; // Hitboxes of area 0 don't collide with anything.

	if (a.max.x <= b.min.x) {
//		std::cerr<<"\ta left of b"<<std::endl;
		return false;
	}
	if (a.min.x >= b.max.x) {
//		std::cerr<<"\ta right of b"<<std::endl;
		return false;
	}
    if (a.max.y <= b.min.y) {
//		std::cerr<<"\ta above b"<<std::endl;
		return false;
    }
    if (a.min.y >= b.max.y) {
//		std::cerr<<"\ta below b"<<std::endl;
		return false;
//        return false; // a is completely left/right/above/below b
	}

//    std::cerr<<"\tcollision"<<std::endl;
    return true; // overlap
}

bool Hitbox::collidesWith(const Hitbox &box) const {
  return collide(*this, box);
}

