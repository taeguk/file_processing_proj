#include <vector>
#include <model/stock.h>
#include <helpers.h>


namespace model {

	using iobuffer::MAX_IOBUFFER_SIZE;


	/*
		Definitions of Stock.
	*/

	Stock::Stock() {}

	Stock::Stock(
		const std::string& id, const std::string& category,
		const std::string& material, int price,
		int stock, const std::string& washing_info,
		const std::string& size
		)
		: m_id(id), m_category(category), m_material(material), m_price(price),
		m_stock(stock), m_washing_info(washing_info), m_size(size)
	{
	}

	Stock::Stock(const Stock& s)
		: m_id(s.m_id), m_category(s.m_category), m_material(s.m_material),
		m_price(s.m_price), m_stock(s.m_stock), m_washing_info(s.m_washing_info),
		m_size(s.m_size)
	{
	}

	Stock& Stock::operator=(const Stock& s)
	{
		this->m_id = s.m_id;
		this->m_category = s.m_category;
		this->m_material = s.m_material;
		this->m_price = s.m_price;
		this->m_stock = s.m_stock;
		this->m_washing_info = s.m_washing_info;
		this->m_size = s.m_size;

		return *this;
	}

	bool Stock::operator==(const Stock& s) const
	{
		return m_id == s.m_id;
	}

	bool Stock::operator!=(const Stock& s) const
	{
		return !(*this == s);
	}

	std::string Stock::formatted_price() const
	{
		std::string formatted_price;

		int first_part = m_price / 1000;
		int second_part = m_price % 1000;

		if (first_part > 0) 
		{
			formatted_price = helper::to_string(first_part) + ','
				+ helper::to_string(second_part, 3);
		}
		else 
		{
			formatted_price = helper::to_string(second_part);
		}

		return formatted_price;
	}

	std::istream & operator>>(std::istream& is, Stock& s)
	{
		std::string line;

		while (std::getline(is, line, '\n')) {
			if (!line.empty())
				break;
		}

		if (line.empty())
		{
			// something is wrong!
			return is;
		}

		std::vector<std::string> tokens = helper::tokenize_string(line, '|');

		if (tokens.size() != STOCK_FIELD_NUM)
		{
			// something is wrong!
			return is;
		}

		s.m_id = tokens[0];
		s.m_category = tokens[1];
		s.m_material = tokens[2];
		s.m_price = helper::to_int(tokens[3], ",");
		s.m_stock = helper::to_int(tokens[4]);
		s.m_washing_info = tokens[5];
		s.m_size = tokens[6];

		return is;
	}

	std::ostream& operator<< (std::ostream& os, const Stock& s)
	{
		const std::string sep = ", ";
		os << s.m_id << sep << s.m_category << sep << s.m_material << sep
			<< s.formatted_price() << sep << s.m_stock << sep << s.m_washing_info << sep
			<< s.m_size << std::endl;

		return os;
	}

	int Stock::Pack(iobuffer::IOBuffer& buffer) const
	{
		int numBytes;

		buffer.Clear();

		numBytes = buffer.Pack(m_id.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_category.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_material.c_str());
		if (numBytes == -1) return FALSE;

		std::string price = formatted_price();
		numBytes = buffer.Pack(price.c_str());
		if (numBytes == -1) return FALSE;

		std::string stock = helper::to_string(m_stock);
		numBytes = buffer.Pack(stock.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_washing_info.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_size.c_str());
		if (numBytes == -1) return FALSE;

		return TRUE;
	}

	int Stock::Unpack(iobuffer::IOBuffer& buffer)
	{
		int numBytes;
		char buf[MAX_IOBUFFER_SIZE];

		numBytes = buffer.Unpack(buf, STOCK_ID_LEN);
		if (numBytes == -1) return FALSE;
		m_id = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, STOCK_CATEGORY_LEN);
		if (numBytes == -1) return FALSE;
		m_category = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_material = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, STOCK_PRICE_LEN);
		if (numBytes == -1) return FALSE;
		std::string price = std::string(buf, numBytes);
		m_price = helper::to_int(price, ",");

		numBytes = buffer.Unpack(buf, STOCK_STOCK_LEN);
		if (numBytes == -1) return FALSE;
		std::string stock = std::string(buf, numBytes);
		m_stock = helper::to_int(stock);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_washing_info = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, STOCK_SIZE_LEN);
		if (numBytes == -1) return FALSE;
		m_size = std::string(buf, numBytes);

		return TRUE;
	}
}