#ifndef MODEL_H
#define MODEL_H

/*
	�� ��������� model namespace���� ��� header file���� 
	include�ϴ� �������μ� ���� �� �ֽ��ϴ�.
	+) ModelManager�� ����.
*/


#include <list>
#include <tuple>
#include <utility>
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
		{
			std::tie(m_data_list, m_empty_block_list) = file::read_data_file<ModelType>();

			std::cout << "-------- Empty Block List Of " << typeid(ModelType).name() << " --------" << std::endl;
			for (auto iter = cbegin(m_empty_block_list); iter != cend(m_empty_block_list); ++iter)
			{
				std::cout << "Empty Block Address = " << iter->first << ", Size = " << iter->second << "." << std::endl;
			}
			std::cin.get();
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
		std::list<std::pair<int, int>> m_empty_block_list;
	};
}

using model::ModelKind;

#endif