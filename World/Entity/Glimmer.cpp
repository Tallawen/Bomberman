#include "Glimmer.h"

//Glimmer::Glimmer(World *_ptr, sf::Vector2f _position) : Entity(_position.x, _position.y, 30.0f, 30.0f) {
//	ptr = _ptr;
//
///*	left = new Animation(
//			       Sprite::instance()->getSprite("Enemi_left"),
//			       Sprite::instance()->getSpriteData("Enemi_left")
//			   );
//
//	right = new Animation(
//			       Sprite::instance()->getSprite("Enemi_right"),
//			       Sprite::instance()->getSpriteData("Enemi_right")
//			   );
//
//	top = new Animation(
//			       Sprite::instance()->getSprite("Enemi_top"),
//			       Sprite::instance()->getSpriteData("Enemi_top")
//			   );
//
//	down = new Animation(
//			       Sprite::instance()->getSprite("Enemi_down"),
//			       Sprite::instance()->getSpriteData("Enemi_down")
//			   );*/
//}
///*
//void Glimmer::update(float dt) {
//	if(fabsf(velocity.x) < 0.01) {
//		state = EntityState::stand;
//		velocity.x = 0;
//
//		left->stop();
//		right->stop();
//
//	} else if(velocity.x > 0.0) {
//		state = EntityState::goRight;
//
//		left->stop();
//		right->play();
//	} else {
//		state = EntityState::goLeft;
//
//		right->stop();
//	    left->play();
//	}
//
//    switch(state) {
//        case EntityState::stand:
//
//          break;
//
//	    case EntityState::goLeft:
//
//	        left->process(dt);
//	        left->setPos(position);
//	      break;
//
//	    case EntityState::goRight:
//
//	    	right->process(dt);
//	    	right->setPos(position);
//	      break;
//    }
//}
//
//void Glimmer::draw(float dt) {
//	switch(state) {
//	    case EntityState::stand:
//
//	      break;
//
//	    case EntityState::goLeft:
//	    	left->draw();
//	      break;
//
//	    case EntityState::goRight:
//	    	right->draw();
//	      break;
//	}
//}
//*/
