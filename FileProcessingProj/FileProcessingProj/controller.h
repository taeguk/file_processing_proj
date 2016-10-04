#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <model/model.h>


/*
	������ �𵨵��� �ٷ�� ó���ϴµ� ���õ� �͵��� ���ִ� namespace
*/
namespace controller
{
	model::Member search_member(std::string id);
	model::Stock search_stock(std::string id);
	model::Purchase search_purchase(std::string kind, std::string id);
}

#endif