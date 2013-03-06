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

bool MapGen::generate(int amount, int lvl) {
	if(width == 0 || height == 0) {
		LOG("Zly rozmiar mapy");
	  return false;
	}

	if(map == nullptr)
		map = new ElementType[width * height];

	int x, y;
	int pl_x, pl_y;

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
	while(boxAmount--) {
		y = sf::Randomizer::Random(1, height);
		x = sf::Randomizer::Random(1, width);

		tab[y][x] = ElementType::box;
	}

	///gracz
	std::vector< std::pair<int, int> > players;
	players.clear();

	while(amount--) {
		pl_x = sf::Randomizer::Random(1, height);
		pl_y = sf::Randomizer::Random(1, width);

		tab[pl_x][pl_y] = ElementType::characters;
		tab[pl_x - 1][pl_y] = ElementType::empty;
		tab[pl_x][pl_y - 1] = ElementType::empty;
		tab[pl_x + 1][pl_y] = ElementType::empty;
		tab[pl_x][pl_y + 1] = ElementType::empty;

		if(players.size() == 0)
			players.push_back(std::make_pair(pl_x, pl_y));

		else if (pl_x == players[0].first && pl_y == players[0].second) {
			++amount;
		  continue;

		} else {
			tab[players[0].first][players[0].second] = ElementType::characters;
			players.push_back(std::make_pair(pl_x, pl_y));
		}
	}

	/** obramowanie, zeby w bfs nie wyjsc poza tablice **/
	for(x = 0; x < width + 2; ++x) {
		tab[0][x] = ElementType::box;
		tab[height + 1][x] = ElementType::box;
	}

	for(y = 0; y < height + 2; ++y) {
		tab[y][0] = ElementType::box;
		tab[y][width + 1] = ElementType::box;
	}

	/** sprawdzamy, czy mapa jest w porzadku **/
	bool visited[height+2][width+2];
	std::queue <int> q;

	while(!q.empty())
		q.pop();

	availableStone = 0; /// ile kamieni jest osiagalnych - do liczenia prawdopodobienstwa wypadniecia klucza
	emptyField.clear();

	for(y = 0; y < height + 2; ++y)
	  	for(x = 0; x < width + 2; ++x)
	   		visited[y][x] = false;

	q.push(pl_x); q.push(pl_y);
	visited[pl_x][pl_y] = true;

    int available_move = 0;
    int radius = 5;

    while(!q.empty()) {
    	++available_move;

    	int a = q.front(); q.pop();
    	int b = q.front(); q.pop();

	    if(available_move >= radius && tab[a][b] == ElementType::empty)
	    	emptyField.push_back((a-1) * width + (b-1)); //dodaje pola na ktorych potem moga byc wylosowani przeciwnicy

	    if(tab[a][b] == ElementType::stone) ++availableStone;

	    if(tab[a-1][b] != ElementType::box && visited[a-1][b] == false) {
	    	visited[a-1][b] = true;
	    	q.push(a-1); q.push(b);
	    }

	    if(tab[a+1][b] != ElementType::box && visited[a+1][b] == false) {
	    	visited[a+1][b] = true;
	    	q.push(a+1); q.push(b);
	    }

	    if(tab[a][b-1] != ElementType::box && visited[a][b-1] == false) {
	    	visited[a][b-1] = true;
	    	q.push(a); q.push(b-1);
	    }

	    if(tab[a][b+1] != ElementType::box && visited[a][b+1] == false) {
	    	visited[a][b+1] = true;
	    	q.push(a); q.push(b+1);
	    }
    }

	stoneAmount = 0;
	emptyAmount = 0;
	this->boxAmount = 0;

	int mapIndex = 0;

	for (y = 1; y < height + 1 ; ++y) {
		for (x = 1 ; x < width + 1 ; ++x) {
			if (tab[y][x] == ElementType::empty) {
				map[mapIndex++] = ElementType::empty;
				++emptyAmount;

			} else if (tab[y][x] == ElementType::characters) {
				map[mapIndex++] = ElementType::characters;

			} else if (tab[y][x] == ElementType::stone) {
				map[mapIndex++] = ElementType::stone;
				++stoneAmount;

			} else if (tab[y][x] == ElementType::box) {
				map[mapIndex++] = ElementType::box;
				++this->boxAmount;
			}
		}
	}

	bool random[(int)emptyField.size()]; // I don't know

	for(x = 0 ; x < emptyField.size() ; ++x)
		random[x] = false;

	int enemyAmount = sf::Randomizer::Random(10, lvl * emptyField.size() / 25); //tu trzeba ewentualnie zmienic, jak bedzie losowalo za malo - duzo przecinikow
	int bat_or_not = 1; //polowa to bat polowa nie

	if(lvl <= 5) {
		for(x = 0 ; x < enemyAmount ; ++x) {
			int k = sf::Randomizer::Random(0, emptyField.size()-1);
			if(random[k] == true) {
				--x;
				continue;

			} else {
				map[emptyField[k]] = ElementType::bat;
				random[k] = true;
			}
		}

	} else if(lvl <= 10) {
		for(x = 0 ; x < enemyAmount ; ++x) {
			int k = sf::Randomizer::Random(0, emptyField.size()-1);
			if(random[k] == true) {
				--x;
				continue;

			} else {
				if(bat_or_not)
					map[emptyField[k]] = ElementType::bat;

				else
					map[emptyField[k]] = ElementType::zombi;

				random[k] = true;
				bat_or_not = 1 - bat_or_not;
			}
		}

	} else if (lvl <= 15) {
		for(x = 0 ; x < enemyAmount ; ++x) {
			int k = sf::Randomizer::Random(0, emptyField.size()-1);

			if(random[k] == true) {
				--x;
				continue;

			} else {
				if(bat_or_not)
					map[emptyField[k]] = ElementType::bat;

				else
					map[emptyField[k]] = ElementType::zombi;

				if(x % 3 == 0)
					map[emptyField[k]] = ElementType::death;

				random[k] = true;
				bat_or_not = 1 - bat_or_not;
			}
		}

	} else {
        for(x = 0 ; x < enemyAmount ; ++x) {
        	int k = sf::Randomizer::Random(0, emptyField.size()-1);
        	if(random[k] == true) {
        		--x;
        		continue;

        	} else {
        		if(bat_or_not)
        			map[emptyField[k]] = ElementType::death;

        		else
                    map[emptyField[k]] = ElementType::zombi;

        		if(x % 3 == 0)
                    map[emptyField[k]] = ElementType::bat;

        		random[k] = true;
                bat_or_not = 1 - bat_or_not;
            }
        }
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

