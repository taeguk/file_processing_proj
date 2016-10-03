#ifndef MODEL_H
#define MODEL_H


#include <string>
#include <iostream>
#include "iobuffer/iobuffer.h"


namespace model {


	/*
		Purchase와 관련된 각종 상수들
	*/
	const int PURCHASE_FIELD_NUM = 4;

	const int PURCHASE_ID_LEN = 16;
	const int PURCHASE_QUANTITY_LEN = 2;


	/*
		상품 구매 내역에 대한 정보를 나타내는 Purchase
	*/
	class Purchase {
	public:
		Purchase();
		Purchase(const std::string& id, const std::string& stock_id,
			const std::string& member_id, int quantity);
		Purchase(const Purchase&);
		Purchase& operator=(const Purchase&);
		bool operator==(const Purchase&) const;
		bool operator!=(const Purchase&) const;

		inline std::string id() const;
		inline std::string stock_id() const;
		inline std::string member_id() const;
		inline int quantity() const;

		friend std::istream& operator>> (std::istream&, Purchase&);
		friend std::ostream& operator<< (std::ostream&, const Purchase&);

		// member functions related to iobuffer.
		int Pack(iobuffer::IOBuffer&) const;
		int Unpack(iobuffer::IOBuffer&);

	private:
		std::string m_id;
		std::string m_stock_id;
		std::string m_member_id;
		int m_quantity;
	};

	std::istream& operator>> (std::istream&, Purchase&);
	std::ostream& operator<< (std::ostream&, const Purchase&);

	std::string Purchase::id() const { return m_id; }
	std::string Purchase::stock_id() const { return m_stock_id; }
	std::string Purchase::member_id() const { return m_member_id; }
	int Purchase::quantity() const { return m_quantity; }
}

#endif