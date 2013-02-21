#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "../StdAfx.h"

/// Defines a hitbox of an entity.
/// Boxes of area 0 do not collide with anything
class Hitbox {
public:
	/// Return true if a and b collide
	static bool collide(const Hitbox &a, const Hitbox &b);

private:
	/// Upper left corner
	sf::Vector2f min;

	/// Lower right corner
	sf::Vector2f max;

public:
	/// Construct from any two opposing corners v1, v2.
    Hitbox(sf::Vector2f v1, sf::Vector2f v2);

    /// Return true if hitbox has area of 0
    bool isNone() const;

    /// Return true if this hitbox collides with `box`
    bool collidesWith(const Hitbox &box) const;

    /// Return vector for top-left corner
    sf::Vector2f getMin() const { return min; }

    /// Return left x coordinate
    float getMinX() const { return min.x; }

    /// Return top y coordinate
    float getMinY() const { return min.y; }

    /// Return vector for bottom-right corner
    sf::Vector2f getMax() const { return max; }

    /// Return right x coordinate
    float getMaxX() const { return max.x; }

    /// Return bottom y coordinate
    float getMaxY() const { return max.y; }

    bool isOver(const Hitbox &box) const;

    bool isUpper(const Hitbox &box) const;

    bool isOnLeft(const Hitbox &box) const;

    bool isOnRight(const Hitbox &box) const;

};

#endif /* __HITBOX_H__ */

