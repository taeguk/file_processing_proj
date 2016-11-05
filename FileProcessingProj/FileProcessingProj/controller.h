#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <model/model.h>
#include <file.h>


/*
	데이터 모델들을 다루고 처리하는데 관련된 것들이 모여있는 namespace
*/
namespace controller {

	model::Member search_member(const model::ModelManager<model::Member>& manager, std::string id);
	model::Stock search_stock(const model::ModelManager<model::Stock>& manager, std::string id);
	std::vector<model::Purchase> search_purchase(const model::ModelManager<model::Purchase>& manager,
		model::ModelKind kind, std::string id);


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
	std::vector<model::Purchase> search_purchase(const Container& purchases,
		ModelKind kind, std::string id)
	{
		switch (kind)
		{
		case ModelKind::MEMBER:
			return search_purchase_with_member_id(purchases, id);
		case ModelKind::STOCK:
			return search_purchase_with_stock_id(purchases, id);
		case ModelKind::PURCHASE:
		{
			std::vector<model::Purchase> v;
			v.emplace_back(search_data_with_id(purchases, id));
			return v;
		}
		default:
			throw std::exception("Invalid model kind.");
		}
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

	template <class DataType>
	void insert_data(const DataType& data)
	{
		iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
		iobuffer::RecordFile<DataType> recode_file(buffer);

		recode_file.Open(file::get_data_file_name<DataType>().c_str(),
			std::ios::out);

		recode_file.Append(data);
		recode_file.Close();
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

	template <class DataType>
	void update_data(const DataType& prev_data, const DataType& after_data)
	{
		delele_data(prev_data);
		insert_data(after_data);
	}
}

#endif