#include "SubWindow.h"

#include "Window.h"

/***********************************************************************************
 SubWindow :: methods
 *********************/
SubWindow::SubWindow() {
	width = 0;
	height = 0;

	position = sf::Vector2f(0, 0);

	alpha = 210;
	windowColor = sf::Color::Black;
	windowColor.a = alpha;

	background = nullptr;

	tETime = 0.0f;
	tETimeTmp = 0.0f;
	tEWindowAlpha = 0.0f;
	tESpriteAlpha = 0.0f;
}

SubWindow::~SubWindow() {
	exit();
}

bool SubWindow::init() {
	if(width <= 0 || height <= 0) return false;
	if(position.x < 0 || position.y < 0) return false;

	if(background != nullptr)
		delete background;

	newBackgroundImg = Window::instance()->getRW()->Capture();
	newBackgroundImg.SetSmooth(false);
	background = new sf::Sprite(newBackgroundImg);

	window = sf::Shape::Rectangle(position.x, position.y, position.x + width, position.y + height, windowColor);

  return true;
}

bool SubWindow::init(int _width, int _height) {
	width = _width;
	height = _height;

  return init();
}

bool SubWindow::init(int _width, int _height, int _x, int _y) {
	width = _width;
	height = _height;

	position = sf::Vector2f(_x, _y);

  return init();
}

bool SubWindow::init(sf::Vector2f dimensions, sf::Vector2f _position) {
	width = dimensions.x;
	height = dimensions.y;

	position = _position;

  return init();
}

void SubWindow::setTransitionEffect(float second) {
	if(second <= 0) return;

	tETime = tETimeTmp = second;
	tESpriteAlpha = tEWindowAlpha = 0;

	windowColor.a = tEWindowAlpha;
	window.SetColor(windowColor);

	FOREACH(queue, it)
	    (*it)->SetColor(sf::Color(255, 255, 255, tESpriteAlpha));
}

void SubWindow::transitionEffect(float dt) {
	if(tETimeTmp < 0) return;

	tEWindowAlpha += alpha / tETime * dt;
	tESpriteAlpha += 255 / tETime * dt;

	windowColor.a = tEWindowAlpha;
	window.SetColor(windowColor);

	FOREACH(queue, it)
	    (*it)->SetColor(sf::Color(255, 255, 255, tESpriteAlpha));

	tETimeTmp -= dt;
}

sf::Key::Code SubWindow::show(std::function<void(sf::Event&, sf::Key::Code&, bool&)> keypress) {
	bool done = false;

	sf::Clock clock;
	sf::Event event;
	sf::Key::Code result = sf::Key::Return;

	float dt = 0.0f;

	while(!done) {
		while(Window::instance()->getRW()->GetEvent(event)) {
			keypress(event, result, done);

			Window::instance()->process(event);
		}

		dt = clock.GetElapsedTime();
		clock.Reset();

		transitionEffect(dt);

		Window::instance()->getRW()->Clear();

		Window::instance()->getRW()->Draw(*background);
		Window::instance()->getRW()->Draw(window);

		FOREACH(queue, it)
			Window::instance()->getRW()->Draw(*(*it));

		Window::instance()->getRW()->Display();
	}

	exit();

  return result;
}

void SubWindow::exit() {
	if(background != nullptr) {
		delete background;

		background = nullptr;
	}

	if(queue.empty()) return;

	FOREACH(queue, it)
	    delete *it;

	queue.clear();
}

void SubWindow::add(sf::Sprite sprite, sf::Vector2i pos) {
	if(pos.x + position.x < 0 || pos.y + position.y < 0) return;

	sprite.SetPosition(pos.x + position.x, pos.y + position.y);
	queue.push_back(new sf::Sprite(sprite));
}
