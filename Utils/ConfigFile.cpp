#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string filename) {
	luaState = lua_open();
	luaL_openlibs(luaState);

	if(luaL_dofile(luaState, filename.c_str()) != 0)
		LOG("Cannot compile" + filename);
}

ConfigFile::~ConfigFile() {
	lua_close(luaState);
}

bool ConfigFile::pushVar(std::string name) {
	 uint found = name.find('.');
	if(found == std::string::npos)
		return false;

	std::string buff = name.substr(0, found);

	int index = LUA_GLOBALSINDEX;

	for(int i = 0; i < 2; ++i) {

		if(index != -1 || lua_istable(luaState, -1)) { // -1 w lua_istable oznacza wierzcholek stosu
			lua_getfield(luaState, index, buff.c_str()); // dodaje elemet na stos tablicy

			if(index == -1)
				lua_remove(luaState, -2); // usun ze stosu nadrzedna tablice

		} else {
			lua_remove(luaState, -1); // przywroc poprzedni stan stosu
		  return false;
		}

		index = -1;

		buff = name.substr(found + 1, name.size() - found);
	}
  return true;
}

bool ConfigFile::getNumber(std::string name, double &number) {
	if(!pushVar(name))
		return false;

	if(lua_isnumber(luaState, -1))
		number = lua_tonumber(luaState, -1);

	else {
		lua_remove(luaState, -1);
	  return false;
	}

	lua_remove(luaState, -1);

  return true;
}

bool ConfigFile::getString(std::string name, std::string &str) {
	if(!pushVar(name))
		return false;

	const char *out = lua_tostring(luaState, -1);

	if(out != 0)
		str.assign(out);

	else {
		lua_remove(luaState, -1);
	  return false;
	}

	lua_remove(luaState, -1);

  return true;
}
