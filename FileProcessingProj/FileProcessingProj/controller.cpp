#include <controller.h>
#include <file.h>
#include <algorithm>


namespace controller
{
	using model::ModelKind;

	template <class ModelType>
	bool find_given_id(ModelType data, std::string id)
	{
		return data.id() == id;
	}

	model::Member search_member(std::string id)
	{
		std::vector<model::Member> members = file::read_data_file<model::Member>();

		return search_member_with_id(members, id);
	}

	model::Stock search_stock(std::string id)
	{
		std::vector<model::Stock> stocks = file::read_data_file<model::Stock>();

		return search_stock_with_id(stocks, id);
	}

	std::vector<model::Purchase> search_purchase(ModelKind kind, std::string id)
	{
		std::vector<model::Purchase> purchases = file::read_data_file<model::Purchase>();

		return search_purchase(purchases, kind, id);
	}
	

	/*
		Searching in Containers.
	*/

	model::Member search_member_with_id(const std::vector<model::Member>& members,
		std::string id)
	{
		std::vector<model::Member>::const_iterator iter =
			std::find(members.begin(), members.end(), id);

		if (iter == members.end())
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	model::Stock search_stock_with_id(const std::vector<model::Stock>& stocks,
		std::string id)
	{
		std::vector<model::Stock>::const_iterator iter =
			std::find(stocks.begin(), stocks.end(), id);

		if (iter == stocks.end())
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	std::vector<model::Purchase> search_purchase(const std::vector<model::Purchase>& purchases,
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
			v.push_back(search_purchase_with_id(purchases, id));
			return v;
		}
		default:
			throw std::exception("Invalid model kind.");
		}
	}

	model::Purchase search_purchase_with_id(const std::vector<model::Purchase>& purchases,
		std::string id)
	{
		std::vector<model::Purchase>::const_iterator iter =
			std::find(purchases.begin(), purchases.end(), id);

		if (iter == purchases.end())
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	std::vector<model::Purchase> search_purchase_with_member_id(const std::vector<model::Purchase>& purchases,
		std::string member_id)
	{
		std::vector<model::Purchase> v;

		for (std::vector<model::Purchase>::const_iterator iter = purchases.begin();
		iter != purchases.end(); ++iter)
		{
			if (iter->member_id() == member_id)
				v.push_back(*iter);
		}

		if (v.empty())
			throw std::exception("Can't find data with given id.");

		return v;
	}

	std::vector<model::Purchase> search_purchase_with_stock_id(const std::vector<model::Purchase>& purchases,
		std::string stock_id)
	{
		std::vector<model::Purchase> v;

		for (std::vector<model::Purchase>::const_iterator iter = purchases.begin();
		iter != purchases.end(); ++iter)
		{
			if (iter->stock_id() == stock_id)
				v.push_back(*iter);
		}

		if(v.empty())
			throw std::exception("Can't find data with given id.");

		return v;
	}
}