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
		return search_data_with_id(manager.const_data_list(), id);
	}

	Stock search_stock(const ModelManager<Stock> &manager, std::string id)
	{
		return search_data_with_id(manager.const_data_list(), id);
	}

	std::vector<Purchase> search_purchase(const ModelManager<Purchase> &manager,
		ModelKind kind, std::string id)
	{
		return search_purchase(manager.const_data_list(), kind, id);
	}
}