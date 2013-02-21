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
		delete map;

	LOG("Delete MapGen");
}

void MapGen::setSize(int _width, int _height) {
	width = _width;
	height = _height;
}

bool MapGen::generate() {
	if(width == 0 || height == 0) {
		LOG("Zly rozmiar mapy");

	  return false;
	}

	if(map == nullptr)
		map = new ElementType[width * height];

	std::cerr << width << ", " << height << std::endl;

	uint x, y;

	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x) {
			map[y * width + x] = ElementType::empty;

			if(sf::Randomizer::Random(0, 1))
				map[y * width + x] = ElementType::stone;
		}
	}

	LOG(1);

	uint boxAmount = sf::Randomizer::Random(int(width * height / 10), int(width * height / 5));

	LOG(2);

	while(boxAmount--) {
		x = sf::Randomizer::Random(0, width);
		y = sf::Randomizer::Random(0, height);

		map[y * width + x] = ElementType::box;
	}


	boxAmount = 6;

		LOG(2);

		while(boxAmount--) {
			x = sf::Randomizer::Random(1, width);
			y = sf::Randomizer::Random(1, height);

			map[y * width + x] = ElementType::exit;
		}


		LOG(3);

			x = sf::Randomizer::Random(0, width);
			y = sf::Randomizer::Random(0, height);
			map[y * width + x] = ElementType::characters;


	LOG(4);

	map[5 * width + 15] = ElementType::exit;
	map[5 * width + 16] = ElementType::empty;
	map[5 * width + 14] = ElementType::empty;
	map[5 * width + 13] = ElementType::empty;
	map[4 * width + 15] = ElementType::empty;
	map[6 * width + 15] = ElementType::empty;


  return true;
}

MapGen::ElementType* MapGen::getMap() {
  return map;
}

