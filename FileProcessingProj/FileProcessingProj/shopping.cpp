#include <iostream>
#include <algorithm>
#include <shopping.h>
#include <helpers.h>
#include <controller.h>


namespace shopping
{
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
		std::cout << title;
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
		case SubMenu::EXIT:
			return SubMenu::EXIT;
		default:
			return SubMenu::INVALID;
		}
	}

	bool prompt_id(SubMenu sub_menu, std::string& kind, std::string& id)
	{
		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			std::cout << "Input Member ID >> ";
			std::cin >> id;
			kind = "member";
			break;
		case SubMenu::STOCK:
			std::cout << "Input Stock ID >> ";
			std::cin >> id;
			kind = "stock";
			break;
		case SubMenu::PURCHASE:
			std::cout << "What kind of ID do you want? (Purchase, Member, Stock) >> ";
			std::cin >> kind;
			std::transform(kind.begin(), kind.end(), kind.begin(), ::tolower);
			if (kind != "member" && kind != "stock" && kind != "purchase") {
				std::cout << kind << " is invalid kind!" << std::endl;
				return false;
			}
			std::cout << "Input " << kind << " ID >> ";
			std::cin >> id;
			break;
		default:
			return false;
		}
		
		return true;
	}

	void menu_search()
	{
		SubMenu sub_menu = sub_prompt(Menu::SEARCH);
		std::string kind, id;

		if (!prompt_id(sub_menu, kind, id))
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
				model::Purchase purchase = controller::search_purchase(kind, id);
				std::cout << purchase;
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
		SubMenu sub_menu = sub_prompt(Menu::SEARCH);
		std::string kind, id;

		if (!prompt_id(sub_menu, kind, id))
			return;

		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			break;
		case SubMenu::STOCK:
			break;
		case SubMenu::PURCHASE:
			break;
		default:
			return;
		}
	}

	void menu_delete()
	{
		SubMenu sub_menu = sub_prompt(Menu::SEARCH);
		std::string kind, id;

		if (!prompt_id(sub_menu, kind, id))
			return;

		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			break;
		case SubMenu::STOCK:
			break;
		case SubMenu::PURCHASE:
			break;
		default:
			return;
		}
	}

	void menu_update()
	{
		SubMenu sub_menu = sub_prompt(Menu::SEARCH);
		std::string kind, id;

		if (!prompt_id(sub_menu, kind, id))
			return;

		switch (sub_menu)
		{
		case SubMenu::MEMBER:
			break;
		case SubMenu::STOCK:
			break;
		case SubMenu::PURCHASE:
			break;
		default:
			return;
		}
	}
}
