#include <string>


/*
	 ������Ʈ�� �ʿ��� �������� ��� �ִ�.
	 ������Ʈ�� �������� ���࿡ ������ �ʰ�, �׽�Ʈ����� �����뵵�� ���δ�.
*/
namespace tool {


	/*
		������Ʈ���� �䱸�ϴ� �ּ� ������ ����
	*/
	const int MIN_MEMBER_COUNT = 1000;
	const int MIN_STOCK_COUNT = 1000;
	const int MIN_PURCHASE_COUNT = 10000;


	/*
	������ ������ ���� �̸��� �����ϰ� �ִ� �����
	*/
	const std::string MEMBER_LIST_FILE_NAME = "listOfMember.txt";
	const std::string STOCK_LIST_FILE_NAME = "listOfStock.txt";
	const std::string PURCHASE_LIST_FILE_NAME = "listOfPurchase.txt";


	/*
		������ ���ϵ��� ���Ƿ� �������ִ� �Լ�
	*/
	void generate_data_files(int member_count, int stock_count, int purchase_count);
}