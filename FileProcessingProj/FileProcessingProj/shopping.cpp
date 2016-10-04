#include <iostream>
#include <algorithm>
#include <shopping.h>
#include <helpers.h>
#include <controller.h>


namespace shopping
{
	using model::ModelKind;


	void online_shopping_system()
	{
		prompt();
	}

	void show_menu()
	{
		std::cout << "====================================" << std::endl;
		std::cout << "       Online Shopping System       " << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << "           < Select Menu >          " << std::endl;
		std::cout << " 1. Search                          " << std::endl;
		std::cout << " 2. Insert                          " << std::endl;
		std::cout << " 3. Delete                          " << std::endl;
		std::cout << " 4. Update                          " << std::endl;
		std::cout << " 5. EXIT (Go back to global Menu)   " << std::endl;
		std::cout << "====================================" << std::endl;
	}

	void prompt()
	{
		bool exit_flag = false;

		helper::clear_console();

		while (!exit_flag)
		{
			int sel;
			show_menu();
			std::cout << "Your Select >> ";
			std::cin >> sel;
			std::cin.get();		// for '\n'

			switch (sel)
			{
			case Menu::SEARCH:
				menu_search();
				break;
			case Menu::INSERT:
				menu_insert();
				break;
			case Menu::DELETE:
				menu_delete();
				break;
			case Menu::UPDATE:
				menu_update();
				break;
			case Menu::EXIT:
				exit_flag = true;
				break;
			default:
				std::cout << "Please, input correct number." << std::endl;
			}

			std::cout << std::endl;
			std::cout << "If you wanna continue, please press 'ENTER'...";
			std::cin.get();

			helper::clear_console();
		}
	}

	SubMenu sub_prompt(Menu menu)
	{
		helper::clear_console();

		std::string title;

		switch (menu)
		{
		case Menu::SEARCH:
			title = "   Online Shopping System - SEARCH  ";
			break;
		case Menu::INSERT:
			title = "   Online Shopping System - INSERT  ";
			break;
		case Menu::DELETE:
			title = "   Online Shopping System - DELETE  ";
			break;
		case Menu::UPDATE:
			title = "   Online Shopping System - UPDATE  ";
			break;
		default:
			return SubMenu::INVALID;
		}

		std::cout << "====================================" << std::endl;
		std::cout << title << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << " 1. Member                          " << std::endl;
		std::cout << " 2. Stock                           " << std::endl;
		std::cout << " 3. Purchase                        " << std::endl;
		std::cout << " 4. EXIT                            " << std::endl;
		std::cout << "====================================" << std::endl;

		int sel;
		std::cout << "Your Select >> ";
		std::cin >> sel;
		std::cin.get();		// for '\n'

		switch (sel)
		{
		case SubMenu::MEMBER:
		case SubMenu::STOCK:
		case SubMenu::PURCHASE:
			return static_cast<SubMenu>(sel);
		case SubMenu::SUB_EXIT:
			return SubMenu::SUB_EXIT;
		default:
			return SubMenu::INVALID;
		}
	}

	bool prompt_id(SubMenu sub_menu, ModelKind& kind, std::string& id, bool is_search)
	{
		std::string str_kind;

		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			std::cout << "Input Member ID >> ";
			std::cin >> id;
			kind = ModelKind::MEMBER;
			break;
		case SubMenu::STOCK:
			std::cout << "Input Stock ID >> ";
			std::cin >> id;
			kind = ModelKind::STOCK;
			break;
		case SubMenu::PURCHASE:
			if (is_search) {
				std::cout << "What kind of ID do you want? (Purchase, Member, Stock) >> ";
				std::cin >> str_kind;
				std::transform(str_kind.begin(), str_kind.end(), str_kind.begin(), ::tolower);
				if (str_kind == "purchase")
					kind = ModelKind::PURCHASE;
				else if (str_kind == "member")
					kind = ModelKind::MEMBER;
				else if (str_kind == "stock")
					kind = ModelKind::STOCK;
				else {
					std::cout << str_kind << " is invalid kind!" << std::endl;
					return false;
				}
			}
			else {
				str_kind = "purchase";
				kind = ModelKind::PURCHASE;
			}
			std::cout << "Input " << str_kind << " ID >> ";
			std::cin >> id;
			break;
		default:
			return false;
		}
		
		std::cin.get();
		return true;
	}

	bool prompt_reg(SubMenu sub_menu, std::string& reg_info, bool is_update)
	{
		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			std::cout << "<< Input Member Info >>" << std::endl;
			if (is_update) {
				std::cout << "* Without ID Please.. *" << std::endl;
				std::cout << "Example) name_471|01788738298|address_54|20020821|username_0@sogang.ac.kr" << std::endl;
			}
			else
				std::cout << "Example) member_id_0|name_471|01788738298|address_54|20020821|username_0@sogang.ac.kr" << std::endl;
			break;
		case SubMenu::STOCK:
			std::cout << "<< Input Stock Info >>" << std::endl;
			if (is_update) {
				std::cout << "* Without ID Please.. *" << std::endl;
				std::cout << "Example) Shirts|Diamond|16,308|4175|Dry Cleaning|XL" << std::endl;
			}
			else
				std::cout << "Example) 000000000000|Shirts|Diamond|16,308|4175|Dry Cleaning|XL" << std::endl;
			break;
		case SubMenu::PURCHASE:
			std::cout << "<< Input Purchase Info >>" << std::endl;
			if (is_update) {
				std::cout << "* Without ID Please.. *" << std::endl;
				std::cout << "Example) 000000015300|member_id_426|57" << std::endl;
			}
			else
				std::cout << "Example) 0000000000000000|000000015300|member_id_426|57" << std::endl;
			break;
		default:
			return false;
		}

		std::cin >> reg_info;
		std::cin.get();
		return true;
	}

	void menu_search()
	{
		SubMenu sub_menu = sub_prompt(Menu::SEARCH);
		ModelKind kind;
		std::string id;

		if (!prompt_id(sub_menu, kind, id, true))
			return;

		try {
			switch (sub_menu)
			{
			case SubMenu::MEMBER:
			{
				model::Member member = controller::search_member(id);
				std::cout << member;
			}
			break;
			case SubMenu::STOCK:
			{
				model::Stock stock = controller::search_stock(id);
				std::cout << stock;
			}
			break;
			case SubMenu::PURCHASE:
			{
				std::vector<model::Purchase> purchases = controller::search_purchase(kind, id);
				for (std::vector<model::Purchase>::iterator iter = purchases.begin();
				iter != purchases.end(); ++iter)
					std::cout << *iter;
			}
			break;
			default:
				return;
			}
		}
		catch (std::exception ex) {
			std::cout << "Invalid ID!!!" << std::endl;
		}
	}

	void menu_insert()
	{
		SubMenu sub_menu = sub_prompt(Menu::INSERT);
		std::string reg_info;

		if (!prompt_reg(sub_menu, reg_info))
			return;

		std::istringstream ss(reg_info);

		switch (sub_menu)
		{
		case SubMenu::MEMBER:
		{
			model::Member member;
			ss >> member;
			try {
				controller::search_member(member.id());
			}
			catch (std::exception ex) {
				std::cout << "Duplicate!" << std::endl;
				return;
			}
			controller::insert_data(member);
		}
			break;
		case SubMenu::STOCK:
		{
			model::Stock stock;
			ss >> stock;
			try {
				controller::search_stock(stock.id());
			}
			catch (std::exception ex) {
				std::cout << "Duplicate!" << std::endl;
				return;
			}
			controller::insert_data(stock);
		}
			break;
		case SubMenu::PURCHASE:
		{
			model::Purchase purchase;
			ss >> purchase;
			try {
				controller::search_purchase(ModelKind::PURCHASE, purchase.id());
			}
			catch (std::exception ex) {
				std::cout << "Duplicate!" << std::endl;
				return;
			}
			try {
				controller::search_member(purchase.member_id());
				controller::search_stock(purchase.stock_id());
			}
			catch (std::exception ex) {
				std::cout << "Foreign Key ERROR!" << std::endl;
				return;
			}
			controller::insert_data(purchase);
		}
			break;
		default:
			return;
		}
	}

	void menu_delete()
	{
		SubMenu sub_menu = sub_prompt(Menu::DELETE);
		ModelKind kind;
		std::string id;

		if (!prompt_id(sub_menu, kind, id))
			return;

		try {
			switch (sub_menu)
			{
			case SubMenu::MEMBER:
			{
				model::Member member = controller::search_member(id);
				try {
					std::vector<model::Purchase> purchases = controller::search_purchase(ModelKind::MEMBER, id);
					for (std::vector<model::Purchase>::iterator iter = purchases.begin();
					iter != purchases.end(); ++iter) {
						std::cout << "DELETE PURCHASE : " << *iter << std::endl;
						controller::delete_data(*iter);
					}
				}
				catch (std::exception ex) {
					// pass
				}
				controller::delete_data(member);
				std::cout << member;
			}
			break;
			case SubMenu::STOCK:
			{
				model::Stock stock = controller::search_stock(id);
				try {
					std::vector<model::Purchase> purchases = controller::search_purchase(ModelKind::STOCK, id);
					for (std::vector<model::Purchase>::iterator iter = purchases.begin();
					iter != purchases.end(); ++iter) {
						std::cout << "DELETE PURCHASE : " << *iter << std::endl;
						controller::delete_data(*iter);
					}
				}
				catch (std::exception ex) {
					// pass
				}
				controller::delete_data(stock);
				std::cout << stock;
			}
			break;
			case SubMenu::PURCHASE:
			{
				std::vector<model::Purchase> purchases = controller::search_purchase(kind, id);
				controller::delete_data(purchases[0]);
				std::cout << purchases[0];
			}
			break;
			default:
				return;
			}
		}
		catch (std::exception ex) {
			std::cout << "Invalid ID!!!" << std::endl;
		}
	}

	void menu_update()
	{
		std::string id, pk;
		SubMenu sub_menu = sub_prompt(Menu::UPDATE);
		{
			ModelKind kind;

			if (!prompt_id(sub_menu, kind, id))
				return;

			try {
				switch (sub_menu)
				{
				case SubMenu::MEMBER:
				{
					model::Member member = controller::search_member(id);
					controller::delete_data(member);
					std::cout << member;
					pk = member.id();
				}
				break;
				case SubMenu::STOCK:
				{
					model::Stock stock = controller::search_stock(id);
					controller::delete_data(stock);
					std::cout << stock;
					pk = stock.id();
				}
				break;
				case SubMenu::PURCHASE:
				{
					std::vector<model::Purchase> purchases = controller::search_purchase(kind, id);
					controller::delete_data(purchases[0]);
					std::cout << purchases[0];
					pk = purchases[0].id();
				}
				break;
				default:
					return;
				}
			}
			catch (std::exception ex) {
				std::cout << "Invalid ID!!!" << std::endl;
				return;
			}
		}
		{
			std::string reg_info;

			if (!prompt_reg(sub_menu, reg_info, true))
				return;

			reg_info = pk + '|' + reg_info;

			std::istringstream ss(reg_info);

			switch (sub_menu)
			{
			case SubMenu::MEMBER:
			{
				model::Member member;
				ss >> member;
				controller::insert_data(member);
			}
			break;
			case SubMenu::STOCK:
			{
				model::Stock stock;
				ss >> stock;
				controller::insert_data(stock);
			}
			break;
			case SubMenu::PURCHASE:
			{
				model::Purchase purchase;
				ss >> purchase;
				controller::insert_data(purchase);
			}
			break;
			default:
				return;
			}
		}
	}
}
