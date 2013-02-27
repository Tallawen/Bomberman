#ifndef __CONFIGFILE_H__
#define __CONFIGFILE_H__

#include "../StdAfx.h"

class ConfigFile {
private:
	lua_State *luaState;

public:
	ConfigFile(std::string filename);
	~ConfigFile();

	bool getNumber(std::string name, double &number);
	bool getString(std::string name, std::string &str);

private:
	bool pushVar(std::string name);

};

#endif /*__CONFIGFILE_H__*/
