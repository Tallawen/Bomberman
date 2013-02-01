#ifndef __MAP_H__
#define __MAP_H__

#include "../StdAfx.h"

class Map {
public:

private:
	std::map<int, std::string> mapFile;
	std::map<std::string, unsigned int> mapFileId;
	typedef std::map<std::string, std::string>::iterator mapFileIterator;

	int loadId;
	unsigned int width;
	unsigned int height;

	unsigned int *board;

public:
	Map() : loadId(-1), width(0), height(0), board(NULL) { }
	~Map();

	void loadMap(unsigned int id);
	void loadMap(std::string title);

	unsigned int* getMap() { return board; }

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }

	int getId(std::string title);
	int getMapId() const { return loadId; }

	void insertMap(std::string title, std::string filename);

private:

};

#endif /*__MAP_H__*/
