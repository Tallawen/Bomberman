#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
//
//#include "../../StdAfx.h"
//
//#include "../World.h"
//#include "../Entity.h"
//
//#include "../../Renderer/Sprite.h"
//#include "../../Renderer/Animation.h"
//#include "../../Renderer/Window.h"
//
//class Explosion : public Entity {
//public:
//	enum class Directions {
//		none = -2,
//		allSite,
//		right,
//		left,
//		top,
//		down,
//	};
//
//private:
//	World *ptr;
//	Animation *animation;
//
//	/* right, left, top, bottom */
//	int id[4];
//	sf::Vector2f position[4];
//
//	int explosionLength;
//	Directions directions;
//
//	float delay;
//
//	bool firstCheck;
//
//public:
//	Explosion(World *_ptr, int _fieldId, float delay, int _priority, sf::Vector2f _position, int _explosionLength, Directions _directions);
//	~Explosion();
//
//	void draw(float dt);
//	void update(float dt);
//
//
//	bool checkTile(World *ptr, int id, DisplayOrder displayOrder,  bool (*ptrFun)(World*, int));
//	bool stone(World *ptr, int id);
//
//
//	bool collideWithStone(World *ptr, int id);
//	bool collideWithExplosion(World *ptr, int id);
//	bool collideWithBomb(World *ptr, int id);
//
//	Hitbox getHitbox() const;
//
//	void setDelay(float delay);
//	void setRemove();
//
//private:
//
//};
//
#endif /*__EXPLOSION_H__*/
