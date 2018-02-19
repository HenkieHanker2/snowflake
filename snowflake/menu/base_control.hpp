#pragma once
#include <string>

class control {
protected:
	int x, y;
	std::wstring label;
	std::string var_name;

public:
	virtual void draw( ) = 0;
	virtual void update( ) = 0;
};