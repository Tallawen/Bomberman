#include "ConstTypes.h"

#include "ConfigFile.h"

static ConfigFile& GetConstants() {
    static ConfigFile constants("Data/constants.lua");
  return constants;
}

/***********************************************************************************
 ConstInt
 *********************/
ConstInt::ConstInt(int defaultValue) {
	value = defaultValue;
}

ConstInt::ConstInt(std::string name, int defaultValue) {
    double num;
    if(GetConstants().getNumber(name, num))
    	value = (int)num;

    else
    	value = defaultValue;
}

ConstInt::operator int() const {
  return value;
}

int ConstInt::operator()() const {
  return value;
}

/***********************************************************************************
 ConstNum
 *********************/
ConstNum::ConstNum(double defaultValue) {
	value = defaultValue;
}

ConstNum::ConstNum(std::string name, double defaultValue) {
	if(!GetConstants().getNumber(name, value))
		value = defaultValue;

}

ConstNum::operator double() const {
  return value;
}

double ConstNum::operator()() const {
  return value;
}

/***********************************************************************************
 ConstStr
 *********************/
ConstStr::ConstStr(std::string defaultValue) {
	value = defaultValue;
}

ConstStr::ConstStr(std::string name, std::string defaultValue) {
	if(!GetConstants().getString(name, value))
		value = defaultValue;

}

ConstStr::operator std::string() const {
  return value;
}

std::string ConstStr::operator()() const {
  return value;
}
