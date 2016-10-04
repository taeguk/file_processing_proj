#ifndef __MODEL_H__
#define __MODEL_H__

/*
	�� ��������� model namespace���� ��� header file���� 
	include�ϴ� �������μ� ���� �� �ֽ��ϴ�.
	ModelManager�� ����.
*/


#include <vector>
#include <model/member.h>
#include <model/stock.h>
#include <model/purchase.h>


namespace model
{
	/*
		Data Model�� ���õ� �͵��� ��� �ִ� ���ӽ����̽�
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