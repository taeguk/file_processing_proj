#ifndef FILE_H
#define FILE_H

#include <string>
#include <algorithm>
#include <cassert>
#include <list>
#include <utility>
#include <type_traits>
#include <model/model.h>
#include <iobuffer/delim.h>
#include <iobuffer/recfile.h>
#include <experimental/filesystem>


/*
	���ϰ� ���õ� �͵��� ����ִ� ���ӽ����̽�
*/
namespace file {


	/*
		������Ʈ���� �䱸�ϴ� �ּ� ������ ����
	*/
	const int MIN_MEMBER_COUNT = 1000;
	const int MIN_STOCK_COUNT = 1000;
	const int MIN_PURCHASE_COUNT = 10000;


	/*
		����Ʈ/������ ���� �̸��� �����ϰ� �ִ� �����
	*/
	const std::string MEMBER_LIST_FILE_NAME = "listOfMember.txt";
	const std::string STOCK_LIST_FILE_NAME = "listOfStock.txt";
	const std::string PURCHASE_LIST_FILE_NAME = "listOfPurchase.txt";

	const std::string MEMBER_DATA_FILE_NAME = "fileOfMember.dat";
	const std::string STOCK_DATA_FILE_NAME = "fileOfStock.dat";
	const std::string PURCHASE_DATA_FILE_NAME = "fileOfPurchase.dat";


	/*
		����Ʈ ���ϵ��� ���Ƿ� �������ִ� �Լ�
	*/
	void generate_list_files(int member_count, int stock_count, int purchase_count);


	/* 
		�� Ÿ������ ���� ����Ʈ ���� �̸��� �������� �Լ� ���ø� 
	*/
	template <class DataType>
	std::string get_list_file_name()
	{
		if (std::is_same<DataType, model::Member>::value)
			return MEMBER_LIST_FILE_NAME;
		else if (std::is_same<DataType, model::Stock>::value)
			return STOCK_LIST_FILE_NAME;
		else if (std::is_same<DataType, model::Purchase>::value)
			return PURCHASE_LIST_FILE_NAME;
	}


	/*
		�� Ÿ������ ���� ������ ���� �̸��� �������� �Լ� ���ø�
	*/
	template <class DataType>
	std::string get_data_file_name()
	{
		if (std::is_same<DataType, model::Member>::value)
			return MEMBER_DATA_FILE_NAME;
		else if (std::is_same<DataType, model::Stock>::value)
			return STOCK_DATA_FILE_NAME;
		else if (std::is_same<DataType, model::Purchase>::value)
			return PURCHASE_DATA_FILE_NAME;
	}


	/*
		Ư�� �� Ÿ�Կ� �ش��ϴ� ����Ʈ ������ �о��ִ� �Լ� ���ø�
	*/
	template <class DataType>
	std::list<DataType> read_list_file(int count = -1)
	{
		std::ifstream ifs;
		int data_cnt;

		ifs.open(get_list_file_name<DataType>());
		ifs >> data_cnt;

		if (count == -1)
			count = data_cnt;
		else
			count = std::min(count, data_cnt);

		std::list<DataType> data_list(count);

		for (auto iter = begin(data_list); iter != end(data_list); ++iter)
		{
			try {
				ifs >> *iter;
			}
			catch (std::exception ex) {
				std::cout << ex.what() << std::endl;
			}
		}

		return data_list;
	}


	/*
		Ư�� �� Ÿ�Կ� �ش��ϴ� �����͵��� �ش��ϴ� ������ ���Ͽ� ���ִ� �Լ� ���ø�
	*/
	template <class DataType>
	void write_data_file(const std::list<DataType>& data_list)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);

		recode_file.Create(get_data_file_name<DataType>().c_str(),
			std::ios::out | std::ios::trunc);

		for (auto iter = cbegin(data_list); iter != cend(data_list); ++iter)
		{
			int recaddr;
			if ((recaddr = recode_file.Write(*iter)) == -1) {
				std::cout << "Write Error!" << std::endl;
			}
		}

		recode_file.Close();
	}


	/*
		Ư�� �� Ÿ�Կ� �ش��ϴ� ������ ������ �о��ִ� �Լ� ���ø�
	*/
	template <class DataType>
	std::pair<std::list<DataType>, std::list<std::pair<int, int>> > 
		read_data_file(int count = -1)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);
		std::list<DataType> data_list;
		std::list<std::pair<int,int>> empty_block_list;
		
		bool empty_block_flag = false;
		int empty_block_addr;

		recode_file.Open(get_data_file_name<DataType>().c_str(),
			std::ios::in);

		for (int i = 0; count == -1 || i < count; ++i)
		{
			if(!empty_block_flag) data_list.emplace_back();
			int read_addr;
			if ((read_addr = recode_file.Read(data_list.back())) == -1)
				// may means eof?
				break;
			if (read_addr >= 0) 
			{
				if (empty_block_flag)  // end of empty block
				{
					int empty_block_size = read_addr - empty_block_addr - 2; // -2 for record_size.
					empty_block_list.emplace_back(empty_block_addr, empty_block_size);
				}
				data_list.back().recaddr = read_addr;
				empty_block_flag = false;
			}
			else  // empty block
			{
				if (!empty_block_flag)  // start of empty block
				{
					empty_block_flag = true;
					empty_block_addr = -read_addr - 2;
				}
			}
		}

		recode_file.Close();

		// truncate file size.
		if (empty_block_flag) {
			namespace fs = std::experimental::filesystem;
			fs::resize_file(get_data_file_name<DataType>(), empty_block_addr);
		}

		return std::make_pair(data_list, empty_block_list);
	}
}

#endif