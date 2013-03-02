#ifndef __UI_H__
#define __UI_H__

#include "../StdAfx.h"

#include "UIElement.h"

class UI {
private:
	std::vector<UIElement*> queue;

public:
	UI();
	~UI() { }

	void show(float dt);
	void add(UIElement *element);

	UIElement* getLast();

};


#endif /*__UI_H__*/
