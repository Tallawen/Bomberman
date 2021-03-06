#ifndef __TEXT_H__
#define __TEXT_H__

#include "../StdAfx.h"

#include "Window.h"

class Text {
public:

private:
	sf::Font font;
	sf::String text;
	sf::Color color;

	int size;
	unsigned int style;

public:
	Text(std::string filename);

	void setText(std::string newText) { text.SetText(newText); }
	void setColor(sf::Color newColor);
	void setSize(int newSize);
	void setStyle(unsigned int newStyle);

	sf::String getText() { return text; }

private:

};

#endif /*__TEXT_H__*/

