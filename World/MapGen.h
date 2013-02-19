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

	uint width;
	uint height;

public:
	MapGen();
	MapGen(int _width, int _height);

	~MapGen();

	void setSize(int _width, int _height);

	bool generate();
	ElementType* getMap();

private:

};

#endif /*__MAPGEN_H__*/
