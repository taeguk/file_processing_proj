#ifndef FILE_H
#define FILE_H

#include <string>
#include <algorithm>
#include <cassert>
#include <model/model.h>
#include <iobuffer/delim.h>
#include <iobuffer/recfile.h>


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
		/////// Invalid DataType!!
		assert(false);
	}

	template <>
	std::string get_list_file_name<model::Member>();

	template <>
	std::string get_list_file_name<model::Stock>();

	template <>
	std::string get_list_file_name<model::Purchase>();


	/*
		�� Ÿ������ ���� ������ ���� �̸��� �������� �Լ� ���ø�
	*/
	template <class DataType>
	std::string get_data_file_name()
	{
		/////// Invalid DataType!!
		assert(false);
	}

	template <>
	std::string get_data_file_name<model::Member>();

	template <>
	std::string get_data_file_name<model::Stock>();

	template <>
	std::string get_data_file_name<model::Purchase>();


	/*
		Ư�� �� Ÿ�Կ� �ش��ϴ� ����Ʈ ������ �о��ִ� �Լ� ���ø�
	*/
	template <class DataType>
	std::vector<DataType> read_list_file(int count = -1)
	{
		std::ifstream ifs;
		int data_cnt;

		ifs.open(get_list_file_name<DataType>());
		ifs >> data_cnt;

		if (count == -1)
			count = data_cnt;
		else
			count = std::min(count, data_cnt);

		std::vector<DataType> data_list(count);

		for (std::vector<DataType>::iterator iter = data_list.begin();
		iter != data_list.end(); ++iter)
		{
			ifs >> *iter;
		}

		return data_list;
	}


	/*
		Ư�� �� Ÿ�Կ� �ش��ϴ� �����͵��� �ش��ϴ� ������ ���Ͽ� ���ִ� �Լ� ���ø�
	*/
	template <class DataType>
	void write_data_file(const std::vector<DataType>& data_list)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);

		recode_file.Create(get_data_file_name<DataType>().c_str(),
			std::ios::out | std::ios::trunc);

		for (std::vector<DataType>::const_iterator iter = data_list.begin();
		iter != data_list.end(); ++iter)
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
	std::vector<DataType> read_data_file(int count = -1)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);
		std::vector<DataType> data_list;

		recode_file.Open(get_data_file_name<DataType>().c_str(),
			std::ios::in);

		for (int i = 0; count == -1 || i < count; ++i)
		{
			data_list.push_back(DataType());
			int read_addr;
			if ((read_addr = recode_file.Read(data_list[i])) == -1)
				// may means eof?
				break;
		}

		recode_file.Close();

		return data_list;
	}
}

#endif