#ifndef __SHOPPING_H__
#define __SHOPPING_H__

#include <model/model.h>


/*
	Online Shopping System과 관련된 것들이 모여있는 namespace
*/
namespace shopping
{
	enum Menu {
		SEARCH, INSERT, DELETE, UPDATE, EXIT
	};

	enum SubMenu {
		MEMBER, STOCK, PURCHASE, EXIT, INVALID
	};

	void online_shopping_system();
	void show_menu();
	void prompt();

	SubMenu sub_prompt(Menu menu);
	bool prompt_id(SubMenu sub_menu, std::string& kind, std::string& id);
	void menu_search();
	void menu_insert();
	void menu_delete();
	void menu_update();

}

#endif