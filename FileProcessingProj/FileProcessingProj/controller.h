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


	model::Member search_member_with_id(const std::vector<model::Member>& members,
		std::string id);
	model::Stock search_stock_with_id(const std::vector<model::Stock>& stocks,
		std::string id);

	std::vector<model::Purchase> search_purchase(const std::vector<model::Purchase>& purchases,
		model::ModelKind kind, std::string id);
	model::Purchase search_purchase_with_id(const std::vector<model::Purchase>& purchases,
		std::string id);
	std::vector<model::Purchase> search_purchase_with_member_id(const std::vector<model::Purchase>& purchases,
		std::string member_id);
	std::vector<model::Purchase> search_purchase_with_stock_id(const std::vector<model::Purchase>& purchases,
		std::string stock_id);


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