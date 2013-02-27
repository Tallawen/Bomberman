#include "Window.h"

/***********************************************************************************
 Window :: singleton
 *********************/
Window* Window::_instance = 0;

Window* Window::instance() {
	if(_instance == 0)
		_instance = new Window;

  return _instance;
}

/***********************************************************************************
 Window :: methods
 *********************/
Window::Window() : desktopWidth(sf::VideoMode::GetDesktopMode().Width), desktopHeight(sf::VideoMode::GetDesktopMode().Height) {
	height = 0;
    width = 0;

    bpp = 0;
    style = 0;
    title = "";
    icon = nullptr;

    position = sf::Vector2i(0, 0);

    showHitbox=false;
}

Window::~Window() {

}

bool Window::init() {
	if(width <= 0 || height <= 0 || bpp <= 0) return false;

	position.x = (desktopWidth  - width)  / 2;
	position.y = (desktopHeight - height) / 2;

	app.Create(sf::VideoMode(width, height, bpp), title, style);
	setPosition(position);

	if(!app.IsOpened()) return false;
  return true;
}


bool Window::init(unsigned int _width, unsigned int _height, std::string _title, unsigned int _style, unsigned int _bpp) {
	width = _width;
	height = _height;

	bpp = _bpp;
	style = _style;
	title = _title;
	icon = nullptr;

	position = sf::Vector2i(0, 0);

  return init();
}

/*
bool Window::onFullscreen() {
	if(style & sf::Style::Fullscreen) return true;

	style |= sf::Style::Fullscreen;

	if(!close()) return false;
  return init();
}


bool Window::offFullscreen() {
	if(!(style & sf::Style::Fullscreen)) return true;

	style ^= sf::Style::Fullscreen;

	if(!close()) return false;
  return init();
}
*/

bool Window::close() {
	if(!isOpen()) return true;

	app.Close();
  return !isOpen();
}


void Window::setPosition(const sf::Vector2i &newPosition) {
	position = newPosition;

	app.SetPosition(position.x, position.y);
}



void Window::process(sf::Event &event) {
	static sf::Vector2i mouseCoordinates = sf::Vector2i(0, 0);

	if(event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Button::Left)
		mouseCoordinates = sf::Vector2i(event.MouseButton.X, event.MouseButton.Y);

	if(app.GetInput().IsMouseButtonDown(sf::Mouse::Left))
		setPosition(position.x + (app.GetInput().GetMouseX() - mouseCoordinates.x), position.y + app.GetInput().GetMouseY() - mouseCoordinates.y);
}


void Window::drawHitbox(const Hitbox &box, sf::Color color) {
	if(showHitbox) {
		sf::Shape boxA = sf::Shape::Rectangle (
				box.getMinX() + 1, box.getMinY() + 1, box.getMaxX() - 1, box.getMaxY() - 1,
				sf::Color(0, 0, 0, 0), 1.0f, color);
		app.Draw(boxA);

		sf::String min;
		sf::String max;

		min.SetPosition(box.getMin());
		max.SetPosition(box.getMax());

		min.SetColor(sf::Color::White);
		max.SetColor(sf::Color::White);

		min.SetSize(10);
		max.SetSize(10);

		std::ostringstream minXSS;
		std::ostringstream minYSS;
		std::ostringstream maxXSS;
		std::ostringstream maxYSS;

		minXSS << box.getMinX();
		minYSS << box.getMinY();

		maxXSS << box.getMaxX();
		maxYSS << box.getMaxY();

		min.SetText("(" + minXSS.str() + ", " + minYSS.str() + ")");
		max.SetText("(" + maxXSS.str() + ", " + maxYSS.str() + ")");

		app.Draw(min);
		app.Draw(max);

	}
}
