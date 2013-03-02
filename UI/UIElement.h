#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

class UIElement {
public:
	UIElement() { }
	virtual ~UIElement() { }

	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;
};

#endif /*__UIELEMENT_H__*/
