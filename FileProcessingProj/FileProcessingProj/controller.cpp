#include <controller.h>
#include <file.h>
#include <algorithm>


namespace controller
{
	using model::ModelKind;
	using model::ModelManager;
	using model::Member;
	using model::Stock;
	using model::Purchase;


	Member search_member(const ModelManager<Member> &manager, std::string id)
	{
		return search_member_with_id(manager.const_data_list(), id);
	}

	Stock search_stock(const ModelManager<Stock> &manager, std::string id)
	{
		return search_stock_with_id(manager.const_data_list(), id);
	}

	std::vector<Purchase> search_purchase(const ModelManager<Purchase> &manager,
		ModelKind kind, std::string id)
	{
		return search_purchase(manager.const_data_list(), kind, id);
	}


	/*
		Searching in Containers.
	*/

	model::Member search_member_with_id(const std::vector<model::Member>& members,
		std::string id)
	{
		auto iter = std::find(cbegin(members), cend(members), id);

		if (iter == cend(members))
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	model::Stock search_stock_with_id(const std::vector<model::Stock>& stocks,
		std::string id)
	{
		auto iter = std::find(cbegin(stocks), cend(stocks), id);

		if (iter == cend(stocks))
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
		auto iter = std::find(cbegin(purchases), cend(purchases), id);

		if (iter == cend(purchases))
			throw std::exception("Can't find data with given id.");

		return *iter;
	}

	std::vector<model::Purchase> search_purchase_with_member_id(const std::vector<model::Purchase>& purchases,
		std::string member_id)
	{
		std::vector<model::Purchase> v;

		for (auto iter = cbegin(purchases); iter != cend(purchases); ++iter)
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

		for (auto iter = cbegin(purchases); iter != cend(purchases); ++iter)
		{
			if (iter->stock_id() == stock_id)
				v.push_back(*iter);
		}

		if(v.empty())
			throw std::exception("Can't find data with given id.");

		return v;
	}
}