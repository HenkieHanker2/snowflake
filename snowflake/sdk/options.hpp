#pragma once
#include <unordered_map>

class value {
public:
	template <typename t = float>
	t get( ) {
		return ( t ) this->m_value;
	}
	template <typename t = float>
	void set( t in ) {
		this->m_value = ( double ) in;
	}

private:
	double m_value;
};
extern std::unordered_map<std::string, value> options;