#ifndef __CONSTTYPES_H__
#define __CONSTTYPES_H__

#include "../StdAfx.h"

/***********************************************************************************
 ConstInt
 *********************/
class ConstInt {
private:
	int value;

public:
	ConstInt(int defaultValue);
	ConstInt(std::string name, int defaultValue);

	operator int() const;
	int operator()() const;
};

/***********************************************************************************
 ConstNum
 *********************/
/**
 * Wszystko co nie jest int'em a jest liczba
 */
class ConstNum {
private:
	double value;

public:
	ConstNum(double defaultValue);
	ConstNum(std::string name, double defaultValue);

	operator double() const;
	double operator()() const;
};

/***********************************************************************************
 ConstStr
 *********************/
class ConstStr {
private:
	std::string value;

public:
	ConstStr(std::string defaultValue);
	ConstStr(std::string name, std::string defaultValue);

	operator std::string() const;
	std::string operator()() const;
};

#endif /*__CONSTTYPE_H__*/
