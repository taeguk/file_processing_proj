#ifndef __MEMBER_H__
#define __MEMBER_H__


#include <string>
#include <iostream>
#include "iobuffer/iobuffer.h"


namespace model {


	/*
		Member와 관련된 각종 상수들
	*/
	const int MEMBER_FIELD_NUM = 6;

	const int MEMBER_BIRTHDAY_LEN = 8;


	/*
		회원 정보를 나타내는 클래스 Member
	*/
	class Member {
	public:
		Member();
		Member(const std::string& id, const std::string& name,
			const std::string& phone_number, const std::string& address,
			const std::string& birthday, const std::string& email);
		Member(const Member&);
		Member& operator=(const Member&);
		bool operator==(const Member&) const;
		bool operator!=(const Member&) const;

		inline std::string id() const;
		inline std::string name() const;
		inline std::string phone_number() const;
		inline std::string address() const;
		inline std::string birthday() const;
		inline std::string email() const;

		friend std::istream& operator>> (std::istream&, Member&);
		friend std::ostream& operator<< (std::ostream&, const Member&);

		// member functions related to iobuffer.
		int Pack(iobuffer::IOBuffer&) const;
		int Unpack(iobuffer::IOBuffer&);

	private:
		std::string m_id;
		std::string m_name;
		std::string m_phone_number;
		std::string m_address;
		std::string m_birthday;
		std::string m_email;
	};

	std::istream& operator>> (std::istream&, Member&);
	std::ostream& operator<< (std::ostream&, const Member&);

	std::string Member::id() const { return m_id; }
	std::string Member::name() const { return m_name; }
	std::string Member::phone_number() const { return m_phone_number; }
	std::string Member::address() const { return m_address; }
	std::string Member::birthday() const { return m_birthday; }
	std::string Member::email() const { return m_email; }
}


#endif