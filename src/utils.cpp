#include "utils.h"

bool utils::file_exists(const std::string& file) 
{
	std::ifstream temp(file.c_str());

	if(!temp)
		return false;
	return true;
}
