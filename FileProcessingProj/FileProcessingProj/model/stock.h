#ifndef __STOCK_H__
#define __STOCK_H__


#include <string>
#include <iostream>
#include <iobuffer/iobuffer.h>


namespace model {


	/*
		Stock과 관련된 각종 상수들
	*/
	const int STOCK_FIELD_NUM = 7;

	const int STOCK_ID_LEN = 12;
	const int STOCK_CATEGORY_LEN = 8;
	const int STOCK_PRICE_LEN = 6;
	const int STOCK_STOCK_LEN = 4;
	const int STOCK_SIZE_LEN = 2;


	/*
		재고 상품에 대한 정보를 나타내는 나타내는 Stock
	*/
	class Stock {
	public:
		Stock();
		Stock(const std::string& id, const std::string& category,
			const std::string& material, int price,
			int stock, const std::string& washing_info,
			const std::string& size);
		Stock(const Stock&);
		Stock& operator=(const Stock&);
		bool operator==(const Stock&) const;
		bool operator!=(const Stock&) const;

		inline std::string id() const;
		inline std::string category() const;
		inline std::string material() const;
		inline int price() const;
		std::string formatted_price() const;
		inline int stock() const;
		inline std::string washing_info() const;
		inline std::string size() const;

		friend std::istream& operator>> (std::istream&, Stock&);
		friend std::ostream& operator<< (std::ostream&, const Stock&);

		// member functions related to iobuffer.
		int Pack(iobuffer::IOBuffer&) const;
		int Unpack(iobuffer::IOBuffer&);

	private:
		std::string m_id;
		std::string m_category;
		std::string m_material;
		int m_price;
		int m_stock;
		std::string m_washing_info;
		std::string m_size;
	};

	std::istream& operator>> (std::istream&, Stock&);
	std::ostream& operator<< (std::ostream&, const Stock&);

	std::string Stock::id() const { return m_id; }
	std::string Stock::category() const { return m_category; }
	std::string Stock::material() const { return m_material; }
	int Stock::price() const { return m_price; }
	int Stock::stock() const { return m_stock; }
	std::string Stock::washing_info() const { return m_washing_info; }
	std::string Stock::size() const { return m_size; }
}

#endif