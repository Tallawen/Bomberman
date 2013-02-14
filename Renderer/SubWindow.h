#ifndef __SUBWINDOW_H__
#define __SUBWINDOW_H__

#include "../StdAfx.h"

#include "Window.h"

class SubWindow {
public:

private:
	/* Window info */
	unsigned int width;
	unsigned int height;

	sf::Vector2f position;

	sf::Image newBackgroundImg;
	sf::Sprite *background;

	sf::Shape window;
	sf::Color windowColor;
	int alpha;

	sf::Event event;

	/**
	 * kolejka obiektów do wyswietlenia
	 */
	std::vector<sf::Drawable*> queue;

public:
	SubWindow();

	bool init();
	bool init(unsigned int _width, unsigned int _height);
	bool init(sf::Vector2i dimensions, sf::Vector2i pos);

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }

	void show(void(* processPtr)(sf::Event) = nullptr);
	void close();

	void setPosition(const sf::Vector2f &newPos);
	void setPosition(const float &x, const float &y);

	sf::Vector2f getPosition() const { return position; };

	/**
	 * Zmienia krycie okna
	 * @param a (0 .. 255) (255 by default)
	 *
	 */
	void setAplha(int a = 255);

	/**
	 * Zmienia kolor okna
	 *
	 */
	void setColor(sf::Color color = sf::Color::Black);

	/**
	 * Dodaje obiekt do kolejki (na koncu)
	 * @param pos wspolrzedne obiektu w oknie
	 */
	void add(sf::Sprite sprite, sf::Vector2i pos);
	void add(sf::String text, sf::Vector2i pos);

	/**
	 * Zwraca referencje do osatniego dodanego sprite
	 *
	 */

	void process(sf::Event &event);

private:

};

#endif /*__SUBWINDOW_H__*/

