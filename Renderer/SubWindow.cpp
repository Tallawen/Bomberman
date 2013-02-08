#include "SubWindow.h"

/***********************************************************************************
 Window :: methods
 *********************/
SubWindow::SubWindow() : height(0), width(0), position(sf::Vector2f(0, 0)), alpha(190), windowColor(sf::Color::Black) {
	windowColor.a = alpha;

	background = nullptr;
}

bool SubWindow::init() {
	if(width == 0 || height == 0) return false;

	if(background != nullptr)
		delete background;

	newBackgroundImg = Window::instance()->getRW()->Capture();
	newBackgroundImg.SetSmooth(false);
	background = new sf::Sprite(newBackgroundImg);

	window = sf::Shape::Rectangle(position.x, position.y, position.x+width, position.y+height, windowColor);

  return true;
}

bool SubWindow::init(unsigned int _width, unsigned int _height) {
	width = _width;
	height = _height;

  return init();
}

bool SubWindow::init(sf::Vector2i dimensions, sf::Vector2i pos) {
	width = dimensions.x;
	height = dimensions.y;

	position.x = pos.x;
	position.y = pos.y;

  return init();
}

void SubWindow::show() {
	bool done = false;

	while(!done) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
				done = true;

			Window::instance()->process(event);
		}

		Window::instance()->getRW()->Clear();

		Window::instance()->getRW()->Draw(*background);
		Window::instance()->getRW()->Draw(window);

		FOREACH(queue, it)
			Window::instance()->getRW()->Draw(*(*it));

		Window::instance()->getRW()->Display();
	}

	close();
}

void SubWindow::close() {
	if(background == nullptr)
		delete background;

	FOREACH(queue, it)
	    delete *it;

	queue.clear();
}

void SubWindow::add(sf::Sprite sprite, sf::Vector2i pos) {
	sprite.SetPosition(pos.x + position.x, pos.y + position.y);

	queue.push_back(new sf::Sprite(sprite));
}

void SubWindow::add(sf::String text, sf::Vector2i pos) {
	text.SetPosition(pos.x + position.x, pos.y + position.y);

	queue.push_back(new sf::String(text));
}
