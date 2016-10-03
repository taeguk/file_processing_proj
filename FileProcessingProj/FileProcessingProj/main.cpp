#include "main.h"


int main() 
{

#ifndef MODE
	/*
		�������� ���α׷� ����.
	*/

	show_member();
	show_stock();
	show_purchase();

	std::cout << "*************************" << std::endl;

	member_test();
	stock_test();
	purchase_test();

#elif MODE == GENERATION_OF_DATA_FILE
	/*
		������Ʈ�� �ʿ��� ������ ���ϵ��� �����.
	*/

	tool::generate_data_files(tool::MIN_MEMBER_COUNT, 
		tool::MIN_STOCK_COUNT, tool::MIN_PURCHASE_COUNT);

#else
	std::cout << 'Nothing to do...' << std::endl;

#endif
}

void show_member()
{
	show_list_file<model::Member>(10);
}

void show_stock()
{
	show_list_file<model::Stock>(10);
}

void show_purchase()
{
	show_list_file<model::Purchase>(10);
}

void member_test()
{
	std::vector<model::Member> members = file::read_list_file<model::Member>();
	file::write_data_file(members);
	std::vector<model::Member> members_for_test = file::read_data_file<model::Member>(10);
	
	for (std::vector<model::Member>::iterator iter = members_for_test.begin();
	iter != members_for_test.end(); ++iter)
	{
		std::cout << *iter;
	}
}

void stock_test()
{
	std::vector<model::Stock> stocks = file::read_list_file<model::Stock>();
	file::write_data_file(stocks);
	std::vector<model::Stock> stocks_for_test = file::read_data_file<model::Stock>(10);

	for (std::vector<model::Stock>::iterator iter = stocks_for_test.begin();
	iter != stocks_for_test.end(); ++iter)
	{
		std::cout << *iter;
	}
}

void purchase_test()
{
	std::vector<model::Purchase> purchases = file::read_list_file<model::Purchase>();
	file::write_data_file(purchases);
	std::vector<model::Purchase> purchases_for_test = file::read_data_file<model::Purchase>(10);

	for (std::vector<model::Purchase>::iterator iter = purchases_for_test.begin();
	iter != purchases_for_test.end(); ++iter)
	{
		std::cout << *iter;
	}
}