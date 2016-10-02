#include <cstdlib>
#include "helpers.h"


namespace helper
{
	int to_int(std::string str)
	{
		return atoi(str.c_str());
	}

	std::vector<std::string> tokenize_string(std::string str, char denim)
	{
		std::stringstream ss(str);
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(ss, token, denim)) {
			tokens.push_back(token);
		}

		return tokens;
	}
}