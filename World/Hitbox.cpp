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

	if (a.max.x < b.min.x) {
//		std::cerr<<"\ta left of b"<<std::endl;
		return false;
	}
	if (a.min.x > b.max.x) {
//		std::cerr<<"\ta right of b"<<std::endl;
		return false;
	}
    if (a.max.y < b.min.y) {
//		std::cerr<<"\ta above b"<<std::endl;
		return false;
    }
    if (a.min.y > b.max.y) {
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

bool Hitbox::isOver(const Hitbox &box) const {
	//std::cerr << "upper " << std::endl;
//	std::cerr << "min.x = " << min.x << ", min.y = " << min.y << ", max.x = " << max.x << ", max.y = " << max.y << std::endl;
//	std::cerr << "box.min.x = " << box.min.x << ", box.min.y = " << box.min.y << ", box.max.x = " << box.max.x << ", box.max.y = " << box.max.y << std::endl;
	//std::cerr << "min.y < box.max.y = " << (min.y < box.max.y) << ", box.max.y < max.y = " << (box.max.y < max.y) << std::endl;

	//if(collidesWith(box) && (box.min.y < max.y) && (min.y < box.min.y)) std::cerr << "over" << std::endl;
    return collidesWith(box) && (box.min.y < max.y) && (min.y < box.min.y);
}

bool Hitbox::isUnder(const Hitbox &box) const {
//	std::cerr << "over" << std::endl;
    return box.isOver(*this);
}

bool Hitbox::isOnLeft(const Hitbox &box) const {
//	std::cerr << "right" << std::endl;
	return collidesWith(box) && (min.x < box.min.x) && (box.min.x < max.x);
}

bool Hitbox::isOnRight(const Hitbox &box) const {

//	std::cerr << "left " << std::endl;
//	std::cerr << "min.x = " << min.x << ", min.y = " << min.y << ", max.x = " << max.x << ", max.y = " << max.y << std::endl;
//	std::cerr << "box.min.x = " << box.min.x << ", box.min.y = " << box.min.y << ", box.max.x = " << box.max.x << ", box.max.y = " << box.max.y << std::endl;
//	std::cerr << "box.min.x < max.x = " << (box.min.x < max.x) << ", min.x < box.min.x = " << (min.x < box.min.x) << std::endl;

	return box.isOnLeft(*this);
}


