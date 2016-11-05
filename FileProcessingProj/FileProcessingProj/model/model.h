#ifndef MODEL_H
#define MODEL_H

/*
	�� ��������� model namespace���� ��� header file���� 
	include�ϴ� �������μ� ���� �� �ֽ��ϴ�.
	+) ModelManager�� ����.
*/


#include <list>
#include <model/member.h>
#include <model/stock.h>
#include <model/purchase.h>
#include <file.h>


namespace model {

	/*
		Data Model�� ���õ� �͵��� ��� �ִ� ���ӽ����̽�
	*/

	enum class ModelKind 
	{
		MEMBER, STOCK, PURCHASE, INVALID
	};

	
	template <typename ModelType>
	class ModelManager
	{
	public:
		ModelManager()
			: m_data_list(file::read_data_file<ModelType>())
		{
		}

		ModelManager(const std::list<ModelType>& data_list)
			: m_data_list(data_list)
		{
		}

		const auto& const_data_list() const
		{
			return m_data_list;
		}

		void add(const ModelType &data)
		{
			m_data_list.emplace_back(data);
		}

		void del(const ModelType &data)
		{
			auto iter = std::find_if(begin(m_data_list), end(m_data_list), 
				[&data](const auto& el) {
				return el.id() == data.id();
			});
			if (iter == end(m_data_list))
			{
				// exception handling.
				std::cout << "EXCEPTION in ModelManager::del()." << std::endl;
				return;
			}
			m_data_list.erase(iter);
		}
		
		/*
		inline const auto& operator const std::vector<ModelType>& () const
		{
			return m_data_list;
		}
		*/

	private:
		std::list<ModelType> m_data_list;
	};
}

using model::ModelKind;

#endif