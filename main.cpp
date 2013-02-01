#include "StdAfx.h"

#include "Renderer/Window.h"
#include "Renderer/Sprite.h"
#include "Renderer/Animation.h"

#include "World/World.h"
#include "Game.h"

int main() {
	Window::instance()->init(1224, 720, "Bomberman");

	sf::String fps;

	Game game;
	game.startGame(0);

	while(Window::instance()->isOpen()) {

		Window::instance()->getRW()->Clear();

		Window::instance()->getRW()->Display();
	}
}
