#include <iostream>
#include <shopping.h>


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
		std::cout << " 5. EXIT                            " << std::endl;
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
			case 1:
				menu_search();
				break;
			case 2:
				menu_insert();
				break;
			case 3:
				menu_delete();
				break;
			case 4:
				menu_update();
				break;
			case 5:
				exit_flag = true;
				break;
			default:
				std::cout << "Please, input correct number." << std::endl;
			}

			std::cout << std::endl;
			std::cout << "If you wanna continue, please press 'ENTER'...";
			std::cin.get();

			clear_console();
		}
	}

	void menu_search()
	{

	}

	void menu_insert()
	{

	}

	void menu_delete()
	{

	}

	void menu_update()
	{

	}
}
