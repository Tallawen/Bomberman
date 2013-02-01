#ifndef __AABB_H__
#define __AABB_H__

#include "../StdAfx.h"

class Aabb {
public:

private:
	sf::Vector2f lowerRightVertex;
	sf::Vector2f upperLeftVertex;

public:
    Aabb(sf::Vector2f _upperLeftVertex, sf::Vector2f _lowerRightVertex);

    bool collides(const Aabb &box) const;
    bool isOver(const Aabb &box) const;
    bool isUnder(const Aabb &box) const;
    bool isOnLeftOf(const Aabb &box) const;
    bool isOnRightOf(const Aabb &box) const;

    float getLRVertexX() const { return lowerRightVertex.x; }
    float getLRVertexY() const { return lowerRightVertex.y; }
    float getULVertexX() const { return upperLeftVertex.x; }
    float getULVertexY() const { return upperLeftVertex.y; }

    sf::Vector2f getLRVertex() const { return lowerRightVertex; }
    sf::Vector2f getULVertex() const { return upperLeftVertex; }

    /*Aabb move(double min_x_offset, double min_y_offset, double max_x_offset, double max_y_offset) {
        return Aabb(m_min_x + min_x_offset, m_min_y + min_y_offset, m_max_x + max_x_offset, m_max_y + max_y_offset);
    }*/

private:

};

#endif /*__AABB_H__*/

