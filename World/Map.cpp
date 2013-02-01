#include "Map.h"

/***********************************************************************************
 Map :: methods
 *********************/
Map::~Map() {
	if(board != NULL)
		delete [] board;
}

void Map::loadMap(unsigned int id) {
	if(mapFile.find(id) == mapFile.end()) {
		LOG("Mapa o id:  nie istnieje");
	  return;
	}

	std::fstream in(mapFile.at(id).c_str());

	if(!in.is_open()) {
		LOG("Plik: " + mapFile.at(id) + " nie istnieje");
	  return;
	}

	in >> width >> height;

	if(board != NULL)
		delete [] board;

	board = new unsigned int[width*height];


	for(unsigned int i = 0; i < height; ++i) {
		for(unsigned int j = 0; j < width; ++j) {
			in >> board[i*width+j];
		}
	}

	loadId = id;
}

void Map::loadMap(std::string title) {
	if(mapFileId.find(title) == mapFileId.end()) {
		LOG("Mapa o tytula: " + title + " nie istnieje");
	  return;
	}

	loadMap(mapFileId.at(title));
}

void Map::insertMap(std::string title, std::string filename) {
	if(mapFileId.find(title) != mapFileId.end()) {
		LOG("Mapa o tytule: " + title + " juz istnieje");
	  return;
	}

	unsigned int id = mapFile.end()->first;
	mapFile.insert(std::make_pair(id, filename));
	mapFileId.insert(std::make_pair(title, id));
}

int Map::getId(std::string title) {
	if(mapFileId.find(title) == mapFileId.end()) {
		LOG("Mapa o tytule: " + title + " nie istnieje");
	  return -1;
	}

  return mapFileId.at(title);
}
