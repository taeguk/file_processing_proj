#include <cstdlib>
#include <main.h>
#include <helpers.h>
#include <shopping.h>


int main() 
{

#ifndef MODE
	/*
		정상적인 프로그램 시작.
	*/

	prompt();

#elif MODE == GENERATION_OF_DATA_FILE
	/*
		프로젝트에 필요한 데이터 파일들을 만든다.
	*/

	file::generate_list_files(file::MIN_MEMBER_COUNT,
		file::MIN_STOCK_COUNT, file::MIN_PURCHASE_COUNT);

#else
	std::cout << 'Nothing to do...' << std::endl;

#endif
}

void show_menu()
{
	std::cout << "====================================" << std::endl;
	std::cout << "     File Processing Project #1     " << std::endl;
	std::cout << "                     made by taeguk " << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "           < Select Menu >          " << std::endl;
	std::cout << " 1. showMember                      " << std::endl;
	std::cout << " 2. showStock                       " << std::endl;
	std::cout << " 3. showPurchase                    " << std::endl;
	std::cout << " 4. MemberTest                      " << std::endl;
	std::cout << " 5. StockTest                       " << std::endl;
	std::cout << " 6. PurchaseTest                    " << std::endl;
	std::cout << " 7. OnlineShoppingSystem            " << std::endl;
	std::cout << " 8. EXIT                            " << std::endl;
	std::cout << "====================================" << std::endl;
}

void prompt()
{
	bool exit_flag = false;

	while (!exit_flag)
	{
		int sel;
		show_menu();
		std::cout << "Your Select >> ";
		std::cin >> sel;
		std::cin.get();		// for '\n'

		switch (sel)
		{
		case 1:
			show_member();
			break;
		case 2:
			show_stock();
			break;
		case 3:
			show_purchase();
			break;
		case 4:
			member_test();
			break;
		case 5:
			stock_test();
			break;
		case 6:
			purchase_test();
			break;
		case 7:
		{
			shopping::OnlineShoppingSystem oss;
			oss.run();
		}
			break;
		case 8:
			exit_flag = true;
			break;
		default:
			std::cout << "Please, input correct number." << std::endl;
		}

		std::cout << std::endl;
		std::cout << "If you wanna continue, please press 'ENTER'...";
		std::cin.get();

		helper::clear_console();
	}
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
	auto members = file::read_list_file<model::Member>();
	file::write_data_file(members);
	auto members_for_test = file::read_data_file<model::Member>(10).first;
	
	for (auto iter = begin(members_for_test); iter != end(members_for_test); ++iter)
		std::cout << *iter;
}

void stock_test()
{
	auto stocks = file::read_list_file<model::Stock>();
	file::write_data_file(stocks);
	auto stocks_for_test = file::read_data_file<model::Stock>(10).first;

	for (auto iter = begin(stocks_for_test); iter != end(stocks_for_test); ++iter)
		std::cout << *iter;
}

void purchase_test()
{
	auto purchases = file::read_list_file<model::Purchase>();
	file::write_data_file(purchases);
	auto purchases_for_test = file::read_data_file<model::Purchase>(10).first;

	for (auto iter = begin(purchases_for_test); iter != end(purchases_for_test); ++iter)
		std::cout << *iter;
}