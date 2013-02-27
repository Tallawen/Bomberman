#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../StdAfx.h"

#include "../World/Hitbox.h"

class Window { /** Singleton **/
public:
	bool showHitbox;

	const uint desktopHeight;
	const uint desktopWidth;

private:
	static Window *_instance;

	sf::RenderWindow app;

	/** Window info **/
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	unsigned int style;
	std::string title;
	sf::Uint8 *icon;
	sf::Vector2i position;

public:
	static Window* instance();

	~Window();

	bool init();
	bool init(unsigned int _width, unsigned int _height, std::string _title, unsigned int _style = sf::Style::Close, unsigned int _bpp = 32);

	bool onFullscreen() = delete;
	bool offFullscreen() = delete;

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }

	unsigned int getBpp() const { return bpp; }
	std::string getTitle() const { return title; }
	unsigned int getStyle() const { return style; }
	//sf::Uint8* getIcon() const { return icon; }

	sf::RenderWindow* getRW() { return &app; }

	bool isOpen() const { return app.IsOpened(); }
	bool close();

	void setPosition(const sf::Vector2i &newPosition);
	void setPosition(const int &x, const int &y) { setPosition(sf::Vector2i(x, y)); }

	sf::Vector2i getPosition() const { return position; };

	void process(sf::Event &event);

	void drawHitbox(const Hitbox &box, sf::Color color);

private:
	Window();

};

#endif /*__WINDOW_H__*/
