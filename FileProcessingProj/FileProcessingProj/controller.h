#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <model/model.h>


/*
	데이터 모델들을 다루고 처리하는데 관련된 것들이 모여있는 namespace
*/
namespace controller
{
	model::Member search_member(std::string id);
	model::Stock search_stock(std::string id);
	model::Purchase search_purchase(std::string kind, std::string id);
}

#endif