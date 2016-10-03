#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include "file.h"


//#define MODE GENERATION_OF_DATA_FILE


template <class DataType>
void show_list_file(int count = -1)
{
	std::vector<DataType> data_list = file::read_list_file<DataType>(count);

	for (std::vector<DataType>::iterator iter = data_list.begin();
	iter != data_list.end(); ++iter)
	{
		std::cout << *iter;
	}
}

void show_member();
void show_stock();
void show_purchase();

void member_test();
void stock_test();
void purchase_test();

#endif