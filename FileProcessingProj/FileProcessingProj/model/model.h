#ifndef __MODEL_H__
#define __MODEL_H__

/*
	이 헤더파일은 model namespace내의 모든 header file들을 
	include하는 목적으로서 사용될 수 있습니다.
	ModelManager도 있음.
*/


#include <vector>
#include <model/member.h>
#include <model/stock.h>
#include <model/purchase.h>


namespace model
{
	/*
		Data Model에 관련된 것들을 담고 있는 네임스페이스
	*/

	enum ModelKind 
	{
		MEMBER, STOCK, PURCHASE, INVALID
	};

	/*
	template <class ModelType>
	class ModelManager
	{
	public:
		ModelManager()
		{
		}
		ModelManager(const std::vector<ModelType> data_list)
			m_data_list(data_list)
		{
		}

	private:
		std::vector<ModelType> m_data_list;
	};
	*/
}


#endif