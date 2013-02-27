#include "MapGen.h"

MapGen::MapGen() {
	map = nullptr;

	width = height = 0;
}

MapGen::MapGen(int _width, int _height) {
	map = nullptr;

	width = _width;
	height = _height;

	LOG("Create MapGen");
}

MapGen::~MapGen() {
	if(map != nullptr)
		delete [] map;

	LOG("Delete MapGen");
}

void MapGen::setSize(int _width, int _height) {
	width = _width;
	height = _height;
}

bool MapGen::generate(int amount) {
	if(width == 0 || height == 0) {
		LOG("Zly rozmiar mapy");

	  return false;
	}

	if(map == nullptr)
		map = new ElementType[width * height];

	int x, y;

	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			map[y * width + x] = ElementType::empty;

			if(sf::Randomizer::Random(0, 1))
				map[y * width + x] = ElementType::stone;
		}
	}

	int boxAmount = sf::Randomizer::Random(int(width * height / 10), int(width * height / 5));

	while(boxAmount--) {
		x = sf::Randomizer::Random(0, width - 1);
		y = sf::Randomizer::Random(0, height - 1);

		map[y * width + x] = ElementType::box;
	}

	int opponentsAmount = sf::Randomizer::Random(2, 10);

	while(opponentsAmount--) {
		x = sf::Randomizer::Random(1, width - 1);
		y = sf::Randomizer::Random(1, height - 1);

		map[y * width + x] = ElementType::exit;
	}

	while(amount--) {
		x = sf::Randomizer::Random(0, width - 1);
		y = sf::Randomizer::Random(0, height - 1);

		map[y * width + x] = ElementType::characters;
	}

  return true;
}

void MapGen::reset() {
	delete [] map;

	map = nullptr;
}

MapGen::ElementType* MapGen::getMap() {
  return map;
}

