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
Window::Window() : height(0), width(0), bpp(0), icon(NULL), position(sf::Vector2f(0, 0)), style(0) {

}

Window::~Window() {

}

bool Window::init() {
	if(width == 0 || height == 0 || bpp == 0) return false;

	app.Create(sf::VideoMode(width, height, bpp), title, style);
	if(!app.IsOpened()) return false;
  return true;
}

bool Window::init(unsigned int _width, unsigned int _height, std::string _title, unsigned int _style, unsigned int _bpp) {
	width = _width;
	height = _height;
	bpp = _bpp;
	title = _title;
	style = _style;
	icon = NULL;
	position = sf::Vector2f(0, 0);

  return init();
}

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

bool Window::close() {
	if(!isOpen()) return true;

	app.Close();
  return !isOpen();
}

void Window::setPosition(const sf::Vector2f &newPos) {
	position = newPos;

	app.SetPosition(newPos.x, newPos.y);
}

void Window::setPosition(const float &x, const float &y) {
	position = sf::Vector2f(x, y);

	app.SetPosition(x, y);
}

void Window::process(sf::Event &event) {
	static sf::Vector2i mouseCoordinates = sf::Vector2i(0, 0);

	if(event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Button::Left)
		mouseCoordinates = sf::Vector2i(event.MouseButton.X, event.MouseButton.Y);

	if(app.GetInput().IsMouseButtonDown(sf::Mouse::Left))
		setPosition(position.x + (app.GetInput().GetMouseX() - mouseCoordinates.x), position.y + app.GetInput().GetMouseY() - mouseCoordinates.y);
}

void Window::drawAabb(const Aabb &box, sf::Color color) {
	if(showAabb) {
		sf::Shape boxA = sf::Shape::Rectangle(box.getULVertexX(), box.getULVertexY(), box.getLRVertexX(), box.getLRVertexY(), sf::Color(0, 0, 0, 0), 1.0f, color);
		app.Draw(boxA);
	}
}
