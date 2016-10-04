#include <vector>
#include <model/purchase.h>
#include <model/stock.h>
#include <helpers.h>



namespace model {

	using iobuffer::MAX_IOBUFFER_SIZE;


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
		m_member_id(p.m_member_id), m_quantity(p.m_quantity),
		recaddr(p.recaddr)
	{
	}

	Purchase& Purchase::operator=(const Purchase& p)
	{
		this->m_id = p.m_id;
		this->m_stock_id = p.m_stock_id;
		this->m_member_id = p.m_member_id;
		this->m_quantity = p.m_quantity;
		this->recaddr = p.recaddr;

		return *this;
	}

	bool Purchase::operator==(const Purchase& p) const
	{
		return m_id == p.m_id;
	}

	bool Purchase::operator==(const std::string& id) const
	{
		return m_id == id;
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
			throw std::exception("Invalid input.");
		}

		std::vector<std::string> tokens = helper::tokenize_string(line, '|');

		if (tokens.size() != PURCHASE_FIELD_NUM)
		{
			// something is wrong!
			throw std::exception("Invalid input.");
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