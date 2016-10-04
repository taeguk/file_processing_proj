#ifndef __SHOPPING_H__
#define __SHOPPING_H__

#include <model/model.h>


/*
	Online Shopping System과 관련된 것들이 모여있는 namespace
*/
namespace shopping
{
	enum Menu {
		SEARCH = 1, INSERT = 2, DELETE = 3, UPDATE = 4, EXIT = 5
	};

	enum SubMenu {
		MEMBER = 1, STOCK = 2, PURCHASE = 3, SUB_EXIT = 4, INVALID
	};

	void online_shopping_system();
	void show_menu();
	void prompt();

	SubMenu sub_prompt(Menu menu);
	bool prompt_id(SubMenu sub_menu, model::ModelKind& kind, std::string& id, bool is_search = false);
	bool prompt_reg(SubMenu sub_menu, std::string& reg_info, bool is_update = false);
	void menu_search();
	void menu_insert();
	void menu_delete();
	void menu_update();

}

#endif