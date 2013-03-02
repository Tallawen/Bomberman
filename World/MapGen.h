#ifndef __MAPGEN_H__
#define __MAPGEN_H__

#include "../StdAfx.h"

class MapGen {
public:
	enum class ElementType {
		empty = 0,
		stone,
		box,
		exit,
		characters
	};

private:
	ElementType *map;

	int width;
	int height;

	int emptyAmount;
	int stoneAmount;
	int boxAmount;
public:
	MapGen();
	MapGen(int _width, int _height);

	~MapGen();

	void setSize(int _width, int _height);

	bool generate(int amount);
	void reset();

	ElementType* getMap();

private:

};

#endif /*__MAPGEN_H__*/
