#include <cstdlib>
#include "helpers.h"


namespace helper
{
	int to_int(std::string str, const char* skip)
	{
		std::string skipped_str;

		for (int i = 0; i < str.length(); ++i) 
		{
			bool is_skip = false;
			const char* cur_skip = skip;

			while (*cur_skip)
			{
				if (*cur_skip == str[i]) 
				{
					is_skip = true;
					break;
				}
				++cur_skip;
			}

			if (!is_skip)
				skipped_str += str[i];
		}

		return atoi(skipped_str.c_str());
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