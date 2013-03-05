#ifndef __SUBWINDOW_H__
#define __SUBWINDOW_H__

#include "../StdAfx.h"

class SubWindow {
public:

private:
	/** rozmiar okna **/
	int width;
	int height;

	sf::Vector2f position;

	sf::Image newBackgroundImg;
	sf::Sprite *background;

	sf::Shape window;
	sf::Color windowColor;
	int alpha; /// ustalona alpha okna

	std::vector<sf::Drawable*> queue; /// kolejka obiektów do wyswietlenia

	/** Zmienne odnosnie efektu przejscia **/
	float tETime; /// Czas trwania efektu
	float tETimeTmp;

	/** pole sf::Color::a jest typu uint8 dlatego i wartosci z przedzialu (0; 1) **
	 ** nie sa uwzgledniane dlatego wykorzystujemy zmienne pomocnicze            **/

	float tEWindowAlpha; /// przejscie krycia okna
	float tESpriteAlpha; /// przejscie krycia dodanych elementow

public:
	SubWindow();
	~SubWindow();

	bool init();
	bool init(int _width, int _height);
	bool init(int _width, int _height, int _x, int _y);
	bool init(sf::Vector2f dimensions, sf::Vector2f _position);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	/**
	 * wyswietla okno i obsluguje zdarzenia przekazane jako adres funkcji lub lembde
	 * @param keypress adres funkcji lub lambda  z obsluga zdarzen
	 * @return zwraca kog klawisza (zalezne od funkcji ktora metoda przyjmuje)
	 */
	sf::Key::Code show(std::function<void(sf::Event&, sf::Key::Code&, bool&)> keypress);

	/*void setPosition(const sf::Vector2f &newPos);
	void setPosition(const float &x, const float &y);*/

	sf::Vector2f getPosition() const { return position; };

	/**
	 * zmienia krycie okna
	 * @param a (0 .. 255) (255 by default)
	 */
	void setAplha(int a = 255) {
		windowColor.a = a;

		window.SetColor(windowColor);
	}

	/** zmienia kolor okna **/
	void setColor(sf::Color color = sf::Color::Black);

	void setTransitionEffect(float second);

	/**
	 * Dodaje obiekt do kolejki (na koncu)
	 * @param pos wspolrzedne obiektu w oknie
	 */
	void add(sf::Sprite sprite, sf::Vector2i pos);

public:
	/** odtwarze efekt przenikania **/
	void transitionEffect(float dt);

	void exit();
};

#endif /*__SUBWINDOW_H__*/

