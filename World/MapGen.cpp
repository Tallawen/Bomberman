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
	if(map != nullptr) {
		delete [] map;

		map = nullptr;
	}

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
/*
	ElementType tab[height + 2][width + 2];
	for(y = 0; y < height + 2; ++y) {
		for(x = 0; x < width + 2; ++x) {
			tab[y][x] = ElementType::empty;

			if(sf::Randomizer::Random(0, 1)) {
				tab[y][x] = ElementType::stone;
				++stoneAmount;
			} else
				++emptyAmount;
		}
	}

	const int MAX_BOX = height * width * 0.3;
	const int MIN_BOX = height * width * 0.1;

	int boxAmount = this->boxAmount = sf::Randomizer::Random(MIN_BOX, MAX_BOX);

	while (boxAmount--) {
		y = sf::Randomizer::Random(1, height);
		x = sf::Randomizer::Random(1, width);

		tab[y][x] = ElementType::box;
	}

	///gracz
	std::vector< std::pair<int, int> > players;
	players.clear();

	while(amount--) {
		x = sf::Randomizer::Random(1,height);
		y = sf::Randomizer::Random(1,width);

		tab[x][y] = 9;
	    tab[x - 1][y] = 0;
	    tab[x][y - 1] = 0;
	    tab[x + 1][y] = 0;
	    tab[x][y + 1] = 0;

	    if(players.size() == 0)
	    	players.push_back(std::make_pair(x,y));

	    else if (x == players[0].first && y == players[0].second) {
	    	++amount;
	    	continue;
	    } else {
	    	tab[players[0].first][players[0].second] = 9;
	    	players.push_back(std::make_pair(x, y));
	    }
	}

	/** obramowanie, zeby w bfs nie wyjsc poza tablice **/
	/*for(x = 0; x < width + 2; ++x) {
		tab[0][x] = INT_MAX;
		tab[height + 1][x] = INT_MAX;
	}

	for(y = 0; y < height + 2; ++y) {
		tab[y][0] = INT_MAX;
		tab[y][width + 1] = INT_MAX;
	}

	/** sprawdzamy, czy mapa jest w porzadku **/
/*	bool visited[height+2][width+2];
	std::queue <int> q;

	while(!q.empty())
		q.pop();

	int availableStone = 0; /// ile kamieni jest osiagalnych - do liczenia prawdopodobienstwa wypadniecia klucza

	for(y = 0; y < height + 2; ++y)
		for(x = 0; x < width + 2; ++x)
			visited[y][x] = false;

	q.push(x); q.push(y);
	visited[x][y] = true;

	int available_move = 0;
	int radius = 5;
	while (!q.empty()) {
		++available_move;
		int a = q.front(); q.pop();
		int b = q.front(); q.pop();
		if (available_move >= radius && tab[a][b] == 0) {
			temp_enemy.push_back(a * width + b); //dodaje pola na ktorych potem moga byc wylosowani przeciwnicy
			}
		f (tab[a][b] == 7) ++available_stone;
		if (tab[a-1][b] != 8 && visited[a-1][b] == false) {
			visited[a-1][b] = true;
			q.push(a-1); q.push(b);
		}
		if (tab[a+1][b] != 8 && visited[a+1][b] == false) {
			visited[a+1][b] = true;
			q.push(a+1); q.push(b);
		}
		if (tab[a][b-1] != 8 && visited[a][b-1] == false) {
			visited[a][b-1] = true;
			q.push(a); q.push(b-1);
		}
		if (tab[a][b+1] != 8 && visited[a][b+1] == false) {
			visited[a][b+1] = true;

			q.push(a); q.push(b+1);
		}
	}












*/

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

