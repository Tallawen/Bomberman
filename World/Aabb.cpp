#include "Aabb.h"

/***********************************************************************************
 Aabb :: methods
 *********************/
Aabb::Aabb(sf::Vector2f _upperLeftVertex, sf::Vector2f _lowerRightVertex) : upperLeftVertex(_upperLeftVertex), lowerRightVertex(_lowerRightVertex) {

}

bool Aabb::collides(const Aabb &box) const {
	if(upperLeftVertex.x > box.lowerRightVertex.x || lowerRightVertex.x < box.upperLeftVertex.x || upperLeftVertex.y < box.lowerRightVertex.y || lowerRightVertex.y > box.upperLeftVertex.y)
    	return false;
  return true;
}

/* bool Aabb::isOver(const Aabb &box) const {
  return collides(box) && lowerLeftVertex.y < box.upperRightVertex.y && box.upperRightVertex.y < upperRightVertex.y;
} */

/* bool Aabb::isUnder(const Aabb &box) const {
  return box.isOver(*this);
} */

/* bool Aabb::isOnLeftOf(const Aabb &box) const {
  return collides(box) && lowerLeftVertex.x < box.lowerLeftVertex.x && box.lowerLeftVertex.x < upperRightVertex.x;
} */

/*bool Aabb::isOnRightOf(const Aabb &box) const {
  return box.isOnLeftOf(*this);
}*/
