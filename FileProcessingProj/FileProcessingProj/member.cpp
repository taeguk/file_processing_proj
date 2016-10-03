#include <vector>
#include "member.h"
#include "helpers.h"


namespace model {

	using iobuffer::MAX_IOBUFFER_SIZE;


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
}