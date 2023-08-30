#include "dbPin.h"

dbPin::operator std::string() const 
{
	std::string text;
	text += "dbPin_" + std::to_string(_index) + "_" + _name ;
	return text;	
}


