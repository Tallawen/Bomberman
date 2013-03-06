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
		door,
		bat,
		death,
		zombi,
		characters
	};

private:
	ElementType *map;

	int width;
	int height;

	int emptyAmount;
	int stoneAmount;
	int boxAmount;

	int availableStone;

	std::vector<int> emptyField;

public:
	MapGen();
	MapGen(int _width, int _height);

	~MapGen();

	void setSize(int _width, int _height);

	bool generate(int amount, int lvl);
	void reset();

	ElementType* getMap();
	std::vector<int> getEmptyField() { return emptyField; }

private:

};

#endif /*__MAPGEN_H__*/
