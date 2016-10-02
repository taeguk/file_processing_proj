#include <iostream>
#include <fstream>
#include <vector>
#include "main.h"
#include "datafile.h"
#include "model.h"


int main() 
{

#ifndef MODE
	/*
		정상적인 프로그램 시작.
	*/

	show_member();
	show_stock();
	show_purchase();

#elif MODE == GENERATION_OF_DATA_FILE
	/*
		프로젝트에 필요한 데이터 파일들을 만든다.
	*/

	tool::generate_data_files(tool::MIN_MEMBER_COUNT, 
		tool::MIN_STOCK_COUNT, tool::MIN_PURCHASE_COUNT);

#else
	std::cout << 'Nothing to do...' << std::endl;

#endif
}

void show_member()
{
	std::vector<model::Member> members(10);
	int cnt;
	std::ifstream ifs;

	ifs.open(tool::MEMBER_LIST_FILE_NAME);
	ifs >> cnt;

	for (std::vector<model::Member>::iterator iter = members.begin(); 
		iter != members.end(); ++iter) 
	{
		ifs >> *iter;
		std::cout << *iter;
	}
}

void show_stock()
{
	std::vector<model::Stock> stocks(10);
	int cnt;
	std::ifstream ifs;

	ifs.open(tool::STOCK_LIST_FILE_NAME);
	ifs >> cnt;

	for (std::vector<model::Stock>::iterator iter = stocks.begin();
	iter != stocks.end(); ++iter)
	{
		ifs >> *iter;
		std::cout << *iter;
	}
}

void show_purchase()
{
	std::vector<model::Purchase> purchases(10);
	int cnt;
	std::ifstream ifs;

	ifs.open(tool::PURCHASE_LIST_FILE_NAME);
	ifs >> cnt ;

	for (std::vector<model::Purchase>::iterator iter = purchases.begin();
	iter != purchases.end(); ++iter)
	{
		ifs >> *iter;
		std::cout << *iter;
	}
}