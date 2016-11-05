#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <file.h>


//#define MODE GENERATION_OF_DATA_FILE


template <class DataType>
void show_list_file(int count = -1)
{
	auto data_list = file::read_list_file<DataType>(count);

	for (auto iter = begin(data_list); iter != end(data_list); ++iter)
		std::cout << *iter;
}

void show_menu();
void prompt();

void show_member();
void show_stock();
void show_purchase();

void member_test();
void stock_test();
void purchase_test();

#endif