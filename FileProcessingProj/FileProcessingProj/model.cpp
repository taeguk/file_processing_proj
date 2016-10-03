#include <vector>
#include "model.h"
#include "helpers.h"
#include "iobuffer/recfile.h"


namespace model {


	/*
		Definitions of Member.
	*/

	Member::Member() {}

	Member::Member(
		const std::string& id, const std::string& name,
		const std::string& phone_number, const std::string& address,
		const std::string& birthday, const std::string& email
		)
		: m_id(id), m_name(name), m_phone_number(phone_number),
		m_address(address), m_birthday(birthday), m_email(email)
	{
	}

	Member::Member(const Member& m)
		: m_id(m.m_id), m_name(m.m_name), m_phone_number(m.m_phone_number),
		m_address(m.m_address), m_birthday(m.m_birthday), m_email(m.m_email)
	{
	}

	Member& Member::operator=(const Member& m)
	{
		this->m_id = m.m_id;
		this->m_name = m.m_name;
		this->m_phone_number = m.m_phone_number;
		this->m_address = m.m_address;
		this->m_birthday = m.m_birthday;
		this->m_email = m.m_email;
		return *this;
	}

	bool Member::operator==(const Member& m) const
	{
		return this->m_id == m.m_id;
	}

	bool Member::operator!=(const Member& m) const
	{
		return !(*this == m);
	}

	std::istream & operator>>(std::istream& is, Member& m)
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

		if (tokens.size() != MEMBER_FIELD_NUM)
		{
			// something is wrong!
			return is;
		}
			
		m.m_id = tokens[0];
		m.m_name = tokens[1];
		m.m_phone_number = tokens[2];
		m.m_address = tokens[3];
		m.m_birthday = tokens[4];
		m.m_email = tokens[5];

		return is;
	}

	std::ostream& operator<< (std::ostream& os, const Member& m)
	{
		const std::string sep = ", ";
		os << m.m_id << sep << m.m_name << sep << m.m_phone_number << sep
			<< m.m_address << sep << m.m_birthday << sep << m.m_email << std::endl;

		return os;
	}

	int Member::Pack(iobuffer::IOBuffer& buffer) const
	{
		int numBytes;

		buffer.Clear();

		numBytes = buffer.Pack(m_id.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_name.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_phone_number.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_address.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_birthday.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_email.c_str());
		if (numBytes == -1) return FALSE;

		return TRUE;
	}

	int Member::Unpack(iobuffer::IOBuffer& buffer)
	{
		int numBytes;
		char buf[MAX_IOBUFFER_SIZE];

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_id = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_name = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_phone_number = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_address = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MEMBER_BIRTHDAY_LEN);
		if (numBytes == -1) return FALSE;
		m_birthday = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_email = std::string(buf, numBytes);

		return TRUE;
	}

	
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
			formatted_price = helper::to_string(first_part) + ',';

		formatted_price += helper::to_string(second_part, 3);

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


	/*
		Definitions of Purchase.
	*/

	Purchase::Purchase() {}

	Purchase::Purchase(
		const std::string& id, const std::string& stock_id, 
		const std::string& member_id, int quantity
		)
		: m_id(id), m_stock_id(stock_id),
		m_member_id(member_id), m_quantity(quantity)
	{
	}

	Purchase::Purchase(const Purchase& p)
		: m_id(p.m_id), m_stock_id(p.m_stock_id),
		m_member_id(p.m_member_id), m_quantity(p.m_quantity)
	{
	}

	Purchase& Purchase::operator=(const Purchase& p)
	{
		this->m_id = p.m_id;
		this->m_stock_id = p.m_stock_id;
		this->m_member_id = p.m_member_id;
		this->m_quantity = p.m_quantity;

		return *this;
	}

	bool Purchase::operator==(const Purchase& p) const
	{
		return this->m_id == p.m_id;
	}

	bool Purchase::operator!=(const Purchase& p) const
	{
		return !(*this == p);
	}

	std::istream & operator>>(std::istream& is, Purchase& p)
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

		if (tokens.size() != PURCHASE_FIELD_NUM)
		{
			// something is wrong!
			return is;
		}

		p.m_id = tokens[0];
		p.m_stock_id = tokens[1];
		p.m_member_id = tokens[2];
		p.m_quantity = helper::to_int(tokens[3]);

		return is;
	}

	std::ostream& operator<< (std::ostream& os, const Purchase& p)
	{
		const std::string sep = ", ";
		os << p.m_id << sep << p.m_stock_id << sep
			<< p.m_member_id << sep << p.m_quantity << std::endl;

		return os;
	}

	int Purchase::Pack(iobuffer::IOBuffer& buffer) const
	{
		int numBytes;

		buffer.Clear();

		numBytes = buffer.Pack(m_id.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_stock_id.c_str());
		if (numBytes == -1) return FALSE;

		numBytes = buffer.Pack(m_member_id.c_str());
		if (numBytes == -1) return FALSE;

		std::string quantity = helper::to_string(m_quantity);
		numBytes = buffer.Pack(quantity.c_str());
		if (numBytes == -1) return FALSE;

		return TRUE;
	}

	int Purchase::Unpack(iobuffer::IOBuffer& buffer)
	{
		int numBytes;
		char buf[MAX_IOBUFFER_SIZE];

		numBytes = buffer.Unpack(buf, PURCHASE_ID_LEN);
		if (numBytes == -1) return FALSE;
		m_id = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, STOCK_ID_LEN);
		if (numBytes == -1) return FALSE;
		m_stock_id = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, MAX_IOBUFFER_SIZE);
		if (numBytes == -1) return FALSE;
		m_member_id = std::string(buf, numBytes);

		numBytes = buffer.Unpack(buf, PURCHASE_QUANTITY_LEN);
		if (numBytes == -1) return FALSE;
		std::string quantity = std::string(buf, numBytes);
		m_quantity = helper::to_int(quantity);

		return TRUE;
	}
}