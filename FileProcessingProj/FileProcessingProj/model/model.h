#ifndef MODEL_H
#define MODEL_H

/*
	이 헤더파일은 model namespace내의 모든 header file들을 
	include하는 목적으로서 사용될 수 있습니다.
	+) ModelManager도 있음.
*/


#include <list>
#include <tuple>
#include <utility>
#include <model/member.h>
#include <model/stock.h>
#include <model/purchase.h>
#include <file.h>
#include <controller.h>


namespace model {

	/*
		Data Model에 관련된 것들을 담고 있는 네임스페이스
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

	private:

		void add_empty_block(std::pair<int, int> empty_block)
		{
			assert(empty_block.second >= 3);

			iobuffer::DelimFieldBuffer buffer('|', iobuffer::MAX_IOBUFFER_SIZE);
			iobuffer::BufferFile buffer_file(buffer);

			buffer_file.Open(file::get_data_file_name<ModelType>().c_str(),
				std::ios::out);

			buffer_file.Reserve(empty_block.first, empty_block.second);

			buffer_file.Close();

		}

		std::pair<int, int> get_avail_empty_block(int record_size)
		{
			for (auto iter = begin(m_empty_block_list); iter != end(m_empty_block_list); ++iter)
			{
				if (iter->second == record_size || 
					iter->second >= record_size + 3) 
				{
					std::pair<int, int> empty_block = *iter;

					if (iter->second >= record_size + 3) 
					{
						decltype(empty_block) remain_block
							(empty_block.first + record_size + 2, empty_block.second - record_size);

						add_empty_block(remain_block);
					}

					m_empty_block_list.erase(iter);

					return empty_block;
				}
			}
			throw std::exception("No available empty block.");
		}

	public:
		/// TODO: r-value reference를 통한 최적화가능. (추후에 고려하기)
		void add(const ModelType &data)
		{
			m_data_list.emplace_back(data);

			auto p_buffer = controller::make_buffer_from_data(data);
			int record_size = p_buffer->SizeOfBuffer();

			try {
				auto empty_block = get_avail_empty_block(record_size);

				controller::insert_data<ModelType>(*p_buffer, empty_block.first);
			}
			catch (std::exception e) {
				// no available empty block.
				controller::insert_data<ModelType>(*p_buffer);
			}
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
			controller::delete_data(data);
			m_data_list.erase(iter);
		}

		/*
		void update(const DataType& prev_data, const DataType& after_data)
		{
			/// TODO: 추후에 exception guarantee 고려하기.
			del(prev_data);
			add(after_data);
		}
		*/
		
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

	model::Member search_member(const model::ModelManager<model::Member>& manager, std::string id);
	model::Stock search_stock(const model::ModelManager<model::Stock>& manager, std::string id);
	std::vector<model::Purchase> search_purchase(const model::ModelManager<model::Purchase>& manager,
		model::ModelKind kind, std::string id);
}

#endif