#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <memory>
#include <model/member.h>
#include <model/stock.h>
#include <model/purchase.h>
#include <file.h>


/*
	데이터 모델들을 다루고 처리하는데 관련된 것들이 모여있는 namespace
*/
namespace controller {

	/*
		Searching in Containers.
	*/

	template <class Container>
	auto search_data_with_id(const Container& data_container, std::string id)
	{
		auto iter = std::find(cbegin(data_container), cend(data_container), id);

		if (iter == cend(data_container))
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	template <class Container>
	std::vector<model::Purchase> search_purchase_with_member_id(const Container& purchases,
		std::string member_id)
	{
		std::vector<model::Purchase> v;

		for (auto iter = cbegin(purchases); iter != cend(purchases); ++iter)
		{
			if (iter->member_id() == member_id)
				v.emplace_back(*iter);
		}

		if (v.empty())
			throw std::exception("Can't find data with given id.");

		return v;
	}

	template <class Container>
	std::vector<model::Purchase> search_purchase_with_stock_id(const Container& purchases,
		std::string stock_id)
	{
		std::vector<model::Purchase> v;

		for (auto iter = cbegin(purchases); iter != cend(purchases); ++iter)
		{
			if (iter->stock_id() == stock_id)
				v.emplace_back(*iter);
		}

		if (v.empty())
			throw std::exception("Can't find data with given id.");

		return v;
	}


	/* Insert, Delete, Update to FILE. */

	/*
	template <class DataType>
	void insert_data(const DataType& data, int recaddr = -1)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);

		recode_file.Open(file::get_data_file_name<DataType>().c_str(),
			std::ios::out);

		if (recaddr == -1)
			recode_file.Append(data);
		else
			recode_file.Write(data, recaddr);
		recode_file.Close();
	}
	*/

	template <class DataType>
	void insert_data(iobuffer::IOBuffer& buffer, int recaddr = -1)
	{
		iobuffer::BufferFile buffer_file(buffer);

		buffer_file.Open(file::get_data_file_name<DataType>().c_str(),
			std::ios::out);

		if (recaddr == -1)
			buffer_file.Append();
		else
			buffer_file.Write(recaddr);
		buffer_file.Close();
	}

	template <class DataType>
	std::shared_ptr<iobuffer::IOBuffer> make_buffer_from_data(const DataType& data)
	{
		auto p_buffer = std::make_shared<iobuffer::DelimFieldBuffer>('|', iobuffer::MAX_IOBUFFER_SIZE);
		data.Pack(*p_buffer);
		return p_buffer;
	}

	template <class DataType>
	void delete_data(const DataType& data)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);

		recode_file.Open(file::get_data_file_name<DataType>().c_str(),
			std::ios::out);

		recode_file.Delete(data.recaddr);
		recode_file.Close();
	}
}

#endif