#ifndef __STDAFX_H__
#define __STDAFX_H__

/***********************************************************************************
 STD
 *********************/

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <cmath>


#include <cassert>

/***********************************************************************************
 STL
 *********************/

#include <vector>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <typeinfo>
#include <limits>

#include <algorithm>

/***********************************************************************************
 SFML
 *********************/

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/***********************************************************************************
 Third party
 *********************/

#include "Macro.h"
//#include "Srt.h"
//#include "Function.h"

/***********************************************************************************
 Typedefs
 *********************/

typedef unsigned    int              uint;
typedef signed      int              sint;

typedef             sf::Vector2f     vec2;

/***********************************************************************************
 Using namespace
 *********************/

using std::string;
using std::wstring;

#endif /*__STDAFX_H__*/
