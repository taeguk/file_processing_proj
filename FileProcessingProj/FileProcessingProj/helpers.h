#include <string>
#include <sstream>


/*
	������Ʈ ���������� ������ �� ���� Helper Ŭ����/�Լ����� ����ִ�.
	C++03�� ����ϴ� ������Ʈ�μ�, C++11�� �ٽ� ��� �� �κ��� ���� �����Ͽ� ����Ѵ�.
	����, ���� std���� �̸� �浹�� ��������, 
	helper namespace�� ��ɵ��� �ݵ�� helper::<����� ���> �� ���� 
	namespace�� ����Ͽ� ����ϵ��� �Ѵ�.
*/
namespace helper {
	
	// C++11�� to_string ��ü�뵵.
	template <typename T>
	std::string to_string(T number, int width = 0)
	{
		std::ostringstream ostr;
		if (width > 0)
			ostr.width(width);
		ostr.fill('0');
		ostr << number;
		return ostr.str();
	}
}