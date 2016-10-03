#include <cstdlib>
#include "helpers.h"


namespace helper
{
	int to_int(std::string str, const char* skip)
	{
		while (*skip)
		{
			char skip_ch = *skip;
			std::size_t idx;
			while ((idx = str.find(skip_ch)) != std::string::npos)
				str.erase(idx);
			++skip;
		}

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