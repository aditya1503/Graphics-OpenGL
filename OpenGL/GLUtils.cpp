#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GLUtils.h"

void MsgAssert(bool assertion, const std::string &msg)
{
	if (!assertion)
	{
		std::cerr << msg << std::endl;
		system("pause");
		exit(1);
	}
}

std::string LoadFileAsString(const std::string &fname)
{
	std::ifstream ifs(fname);
	std::stringstream sstr;

	MsgAssert(ifs.is_open(), std::string("Unable to load shader file: ") + fname);

	sstr << ifs.rdbuf();

	return sstr.str();
}
