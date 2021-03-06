#include "Text.h"

Text::Text(std::string filename) {
	if (!font.LoadFromFile(filename))
		LOG("Wczytanie czcionki nie powiodlo sie");

	size = 12;
	style = sf::String::Regular;
	color = sf::Color::Black;

	text.SetFont(font);
	text.SetSize(size);
	text.SetStyle(style);
	text.SetColor(color);
}

void Text::setColor(sf::Color newColor) {
	color = newColor;

	text.SetColor(color);
}

void Text::setSize(int newSize) {
	size = newSize;

	text.SetSize(size);
}

void Text::setStyle(unsigned int newStyle) {
	style = newStyle;

	text.SetStyle(style);

}
