#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <vector>


/*
	������Ʈ ���������� ������ �� ���� Helper Ŭ����/�Լ����� ����ִ�.
	C++03�� ����ϴ� ������Ʈ�μ�, C++11�� �ٽ� ��� �� �κ��� ���� �����Ͽ� ����Ѵ�.
	����, ���� std���� �̸� �浹�� ��������, 
	helper namespace�� ��ɵ��� �ݵ�� helper::<����� ���> �� ���� 
	namespace�� ����Ͽ� ����ϵ��� �Ѵ�.
*/
namespace helper {
	
	// C++11�� to_string ��ü�뵵.
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