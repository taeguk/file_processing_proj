#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <vector>


/*
	프로젝트 전반적으로 도움을 줄 만한 Helper 클래스/함수들을 담고있다.
	C++03을 사용하는 프로젝트로서, C++11의 핵심 기능 몇 부분을 직접 구현하여 사용한다.
	따라서, 추후 std와의 이름 충돌을 막기위해, 
	helper namespace의 기능들은 반드시 helper::<사용할 기능> 과 같이 
	namespace를 명시하여 사용하도록 한다.
*/
namespace helper {
	
	// C++11의 to_string 대체용도.
	template <class T>
	std::string to_string(T number, int width = 0)
	{
		std::ostringstream ostr;
		if (width > 0)
			ostr.width(width);
		ostr.fill('0');
		ostr << number;
		return ostr.str();
	}

	int to_int(std::string str, const char* skip = "");
	std::vector<std::string> tokenize_string(std::string str, char denim);
	void clear_console();
}

#endif